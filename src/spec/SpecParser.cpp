#include "../stdafx.h"
#include "SpecParser.h"
#include "..//expression/EqualBool.h"

//And, it is a predicate.
bool contain(const vector<And*>& preList, string streamName) {
	for (And* pre : preList) {
		if (pre->streamName == streamName) return true;
	}
	return false;
}

And* getPredicateByStreamName(const vector<And*>& preList, string streamName) {
	for (And* pre : preList) {
		if (pre->streamName == streamName) return pre;
	}
	cout << "there is no such stream name: " << streamName << endl;
	throw "";
}

vector<Predicate*> SpecParser::parseMultiExpression(string expStr) {
	vector<And*> predicateListResult;

	And * andPredicate = nullptr;
	vector<string> expressionList = Utils::split(expStr, "&");
	if (expressionList.size() > 0) {
		for (string expression : expressionList) {
			string stream;
			string fieldName;
			string mid;
			string right;
			splitExpression(expression, stream, fieldName, mid, right);
			if (!contain(predicateListResult, stream)) {
				andPredicate = new And();
				predicateListResult.push_back(andPredicate);
			}else {
				andPredicate = getPredicateByStreamName(predicateListResult, stream);
			}
			int index1 = fieldName.find("(");
			int index2 = fieldName.find(")");
			if ((index1 > -1 && index2 > -1) /*|| OperatorRegister::isOperator(fieldName)*/) {
				andPredicate->addChild(parseExpressionWithOperator(expression));
			}else {
				andPredicate->addChild(parseValueExpression(fieldName, mid, right));
			}
		}
	}
	vector<Predicate*> vec;
	for (Predicate* p : predicateListResult) {
		vec.push_back(p);
	}
	return vec;
}

//format is: "streamName.field mid right", for example: "plane.speed > 12"
//It could be "streamName.operatorName() > 12", or
//"operatorName(streamName.fieldName) > 12"
bool SpecParser::splitExpression(const string expression, string& stream, string & fieldName, string &mid, string & right) {
	int index = -1;
	string left;
	if ((index = expression.find(">=")) != -1) {
		left = expression.substr(0, index);
		right = expression.substr(index + 2, expression.size() - index - 2);
		mid = ">=";
	}
	else if ((index = expression.find(">")) != -1) {
		left = expression.substr(0, index);
		right = expression.substr(index + 1, expression.size() - index - 1);
		mid = ">";
	}
	else if ((index = expression.find("<=")) != -1) {
		left = expression.substr(0, index);
		right = expression.substr(index + 2, expression.size() - index - 2);
		mid = "<=";
	}
	else if ((index = expression.find("<")) != -1) {
		left = expression.substr(0, index);
		right = expression.substr(index + 1, expression.size() - index - 1);
		mid = "<";
	}
	else if ((index = expression.find("==")) != -1) {
		left = expression.substr(0, index);
		right = expression.substr(index + 2, expression.size() - index - 2);
		mid = "==";
	}
	else if ((index = expression.find("=")) != -1) {
		left = expression.substr(0, index);
		right = expression.substr(index + 1, expression.size() - index - 1);
		mid = "=";
	}
	else {
		std::cout << "no expression predicate";
		throw runtime_error("");
	}
	if ((index = left.find(".")) != -1) {

		int index2 = left.find("(");
		if (index2 == -1) {
			stream = left.substr(0, index);
			fieldName = left.substr(index + 1, left.size() - index - 1);
		}
		else if (index < index2) {
			stream = left.substr(0, index);
			fieldName = left.substr(index + 1, left.size() - index - 1);
		}
		else {
			fieldName = left;
		}

	}
	else {
		fieldName = left;
	}
	return true;
}

Predicate * SpecParser::parseValueExpression(string name, string mid, string value) {
	int index = -1;
	if (mid == "==" || mid == "=") {
		return new EqualString(value, name);
	}
	else {
		stringstream ss;
		float f = 0.0;
		ss << value;
		ss >> f;
		if (mid == ">=") {
			return new GreaterThanFloat(f, name);
		}
		else if (mid == ">") {
			return new GreaterThanFloat(f, name);
		}
		else if (mid == "<=") {
			return new LessThanFloat(f, name);
		}
		else if (mid == "<") {
			return new LessThanFloat(f, name);
		}
	}
	std::cout << "undefined expression";
	throw "";
}

//parse the expression with operator
//1. parse and generate operator
//2. parse and generate predicate object
Predicate * SpecParser::parseExpressionWithOperator(string expression) {

	vector<string> parameters;

	string stream;
	string opName;
	string mid;
	string right;
	splitExpression(expression, stream, opName, mid, right);

	int index1 = opName.find("(");

	if (index1 >= 0) {
		string tempName = opName.substr(0, index1);
		int index2 = opName.find(")");
		string paramsStr = opName.substr(index1 + 1, index2 - index1 - 1);
		vector<string> params = Utils::split(paramsStr, ",");

		for (string param : params) {
			parameters.push_back(param);
		}
		opName = tempName;
	}
	Operator * op = OperatorRegister::getInstance(opName, parameters);
	//Operator * doubleOp = dynamic_cast<Operator<double>*>(op);
	string value = right;

	if (value == "true") {
		return new EqualBool(op, true);
	}else if (value == "false") {
		return new EqualBool(op, false);
	}

	stringstream ss;
	float f = 0.0;
	ss << value;
	ss >> f;
	if (mid == ">=") {
		return new GreatThanOpPreDouble(op, f);
	}
	else if (mid == ">") {
		return new GreatThanOpPreDouble(op, f);
	}
	else if (mid == "<=") {
		return new LessThanOpPreDouble(op, f);
	}
	else if (mid == "<") {
		return new LessThanOpPreDouble(op, f);
	}
	std::cout << "undefined expression";
	throw "undefined expression";
}