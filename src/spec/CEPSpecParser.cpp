#include "../stdafx.h"
#include <string>
#include "CEPSpecParser.h"
#include "../op/OperatorRegister.h"
#include "../expression/LessThanOpPreDouble.h"
#include "../expression/GreatThanOpPreDouble.h"

//list<CEPSpec*> CEPSpecParser::parseAllCEPSpec(const list<string> allCEPSpecs) {
//	list<CEPSpec*> result;
//	list<string> cqSpec;
//	for (string line : allCEPSpecs) {
//		line = Utils::toLower(Utils::trim(line));
//		if (line.size() == 0 || line[0] == '#') continue;
//
//		cqSpec.push_back(line);
//		if (line.find("then") == 0) {
//			CEPSpec* spec = parseOneCEPSpec(cqSpec);
//			result.push_back(spec);
//			cqSpec.clear();
//		}
//	}
//	return result;
//}

CEPSpec* CEPSpecParser::parseOneCEPSpec(list<string> oneCEPSpec) {
	CEPSpec * result = new CEPSpec();
	//Predicate* condition = nullptr;
	//vector<string> outputStreamVec;

	int winLen = -1;
	int winSliding = -1;

	for (string s : oneCEPSpec) {
		s = Utils::toLower(Utils::trim(s));
		if (s.size() == 0 || s[0] == '#') continue;

		size_t index = s.find_first_of(" ", 0);
		if (index < 0) {
			std::cout << "no clause";
			throw runtime_error("no clause");
		}

		string clause = s.substr(0, index);
		string value = s.substr(index + 1, s.size() - index - 1);
		Utils::deleteAllMark(value, " ");

		if ("if" == clause) {
			parseMultiExpression(value, result);
		}
		else if ("from" == clause) {
			vector<string> inputStreams = Utils::split(value, ",");
			result->setInputStreams(inputStreams);
		}
		else if ("window" == clause) {
			vector<string> pieces = Utils::split(value, ",");
			for (string piece : pieces) {
				vector<string> key_value = Utils::split(piece, "=");
				if (key_value[0] == "length") {
					stringstream ss;
					ss << key_value[1];
					ss >> winLen;
				}
				else if (key_value[0] == "sliding") {
					stringstream ss;
					ss << key_value[1];
					ss >> winSliding;
				}
			}
			if (winLen > 0 && winSliding < 0) winSliding = winLen;
		}
		else if ("then" == clause) {
			string outputStringName = value;

			result->setOutputStreamName(outputStringName);
			result->setWinLen(winLen);
			result->setWinSliding(winSliding);

			return result;
		}
		else {
			std::cout << "undefined CQ spec term";
			throw "undefined CQ spec term";
		}
	}
	return nullptr;
}

//And, it is a predicate.
bool contain_CEP(const vector<And*>& preList, string streamName) {
	for (And* pre : preList) {
		if (pre->streamName == streamName) return true;
	}
	return false;
}

And* getPredicateByStreamName_CEP(const vector<And*>& preList, string streamName) {
	for (And* pre : preList) {
		if (pre->streamName == streamName) return pre;
	}
	cout << "there is no such stream name: " << streamName << endl;
	throw "";
}

void CEPSpecParser::parseMultiExpression(string expStr, CEPSpec *cepSpec) {
	vector<And*> predicateListResult;
	And* andPredicate = nullptr;

	vector<string> expressionList = Utils::split(expStr, "&");
	if (expressionList.size() > 0) {
		for (string expression : expressionList) {
			int index;
			if ((index = expression.find("exist")) == 0) {
				parseExistOpExpression(expression, cepSpec);
			}
			else {
				string stream;
				string fieldName;
				string mid;
				string right;
				splitExpression(expression, stream, fieldName, mid, right);
				if (!contain_CEP(predicateListResult, stream)) {
					andPredicate = new And();
					andPredicate->streamName = stream;
					predicateListResult.push_back(andPredicate);
				}else {
					andPredicate = getPredicateByStreamName_CEP(predicateListResult, stream);
				}

				int index1 = fieldName.find("(");
				int index2 = fieldName.find(")");
				if ((index1 > -1 && index2 > -1)) {
					cout << "error: currently in IF clause, no other operator except Exist()";
					throw "";
				}else {
					andPredicate->addChild(parseValueExpression(fieldName, mid, right));
				}
			}
		}
		vector<Predicate*> vec;
		for (Predicate* p : predicateListResult) {
			vec.push_back(p);
		}
		cepSpec->setPredicates(vec);
	}
}

void CEPSpecParser::parseExistOpExpression(string expStr, CEPSpec * cepSpec) {
	if (!cepSpec) {
		std::cout << "nullpointer CEP spec";
		throw runtime_error("");
	}

	int index = 0;

	if ((index = expStr.find("exist")) != 0) {
		std::cout << "not the operator existOp()";
		throw runtime_error("");
	}

	vector<string> parameters;
	int index1 = expStr.find("(");
	int index2 = expStr.find(")");
	if (index1 >= 0 && index2 > 0) {
		string opName = expStr.substr(0, index1);

		string paramsStr = expStr.substr(index1 + 1, index2 - index1 - 1);

		ExistOp* eo = new ExistOp(paramsStr);
		cepSpec->addExistOpPredicate(eo, paramsStr);
	}
	else {
		std::cout << "illegal spec";
		throw runtime_error("");
	}
}

bool CEPSpecParser::splitExpression(const string expression, string& stream, string & fieldName, string &mid, string & right) {
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
		stream = left.substr(0, index);
		fieldName = left.substr(index + 1, left.size() - index - 1);
	}
	else {
		fieldName = left;
	}
	return true;
}

Predicate * CEPSpecParser::parseValueExpression(string name, string mid, string value) {
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
	std::cout << "undefined expression, name=" << name << ", mid=" << mid << ", value=" << value;
	throw "undefined expression";
}


Predicate * CEPSpecParser::parseExpressionWithOperator(string expression) {

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

	//Operator<double> *doubleOp = dynamic_cast<Operator<double>*>(op);

	string value = right;

	Predicate * pre = nullptr;
	stringstream ss;
	float f = 0.0;
	ss << value;
	ss >> f;
	if (mid == ">=") {
		pre = new GreatThanOpPreDouble(op, f);
	}
	else if (mid == ">") {
		pre = new GreatThanOpPreDouble(op, f);
	}
	else if (mid == "<=") {
		pre = new LessThanOpPreDouble(op, f);
	}
	else if (mid == "<") {
		pre = new LessThanOpPreDouble(op, f);
	}
	std::cout << "undefined expression";
	throw "undefined expression";
}