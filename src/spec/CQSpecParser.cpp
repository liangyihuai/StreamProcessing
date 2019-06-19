#include "../stdafx.h"
#include "CQSpecParser.h"

//list<CQSpec*> CQSpecParser::parseAllCQSpec(const list<string> allCQSpecs) {
//	list<CQSpec*> result;
//	list<string> cqSpec;
//	for (string line : allCQSpecs) {
//		line = Utils::toLower(Utils::trim(line));
//		if (line.size() == 0 || line[0] == '#') continue;
//
//		cqSpec.push_back(line);
//		if (line.find("then") == 0) {
//			CQSpec* spec = parseOneCQSpec(cqSpec);
//			result.push_back(spec);
//			cqSpec.clear();
//		}
//	}
//	return result;
//}

/*
If distance < 20, condition2, condition3
From airplane
Window length=, sliding=
Then WideAreaDefenceTarget, attr1, attr2
*/
CQSpec* CQSpecParser::parseOneCQSpec(list<string> oneCQSpec) {
	CQSpec * result = nullptr;
	vector<Predicate*> conditionList;
	vector<string> inputStreams;
	string streamSource;
	int win_len = -1;
	int win_sliding = -1;
	string distinctField;

	for (string s : oneCQSpec) {
		s = Utils::toLower(Utils::trim(s));
		if (s.size() == 0 || s[0] == '#') continue;

		size_t index = s.find_first_of(" ", 0);
		if (index < 0) {
			std::cout << "no clause";
			throw runtime_error("");
		}

		string clause = s.substr(0, index);
		string value = s.substr(index + 1, s.size() - index - 1);
		Utils::deleteAllMark(value, " ");

		if ("if" == clause) {
			conditionList = parseMultiExpression(value);
		}else if ("from" == clause) {
			inputStreams = Utils::split(value, ",");
		}else if ("window" == clause) {//Window length=, sliding=
			vector<string> pieces = Utils::split(value, ",");
			for (string piece : pieces) {
				vector<string> key_value = Utils::split(piece, "=");
				if (key_value[0] == "length") {
					stringstream ss;
					ss << key_value[1];
					ss >> win_len;
				}else if (key_value[0] == "sliding") {
					stringstream ss;
					ss << key_value[1];
					ss >> win_sliding;
				}
				else if (key_value[0] == "distinct") {
					distinctField = key_value[1];
				}
			}
			if (win_len > 0 && win_sliding < 0) win_sliding = win_len;
		}else if ("then" == clause) {
			result = new CQSpec();

			//parse THEN clause
			vector<string> splits = Utils::split(value, ",", "(", ")");
			string outputStreamName = splits[0];//get output stream name
			result->setOutputStream(outputStreamName);
			for (int i = 1; i < splits.size(); i++) {
				string attr = splits[i];
				if (attr.find('=') != string::npos) {//For example, THEN SevereThreat, threatLevel=severe
					vector<string> key_value = Utils::split(attr, "=");//提取出等号两边的内容
					result->newAttrNames.push_back(key_value[0]);
					result->newAttrValues.push_back(key_value[1]);
				}else if (attr.find('(') > 0 && attr.find(')') > 0) {//For example, THEN SevereThreat, count(*)
					int index = attr.find('(');
					result->operatorNames.push_back(attr.substr(0, index));//提取出方法名
					vector<string> params = Utils::split(attr.substr(index+1, attr.length()-2-index), ",");
					vector<string>* v = new vector<string>();
					for (string s : params) 
						v->push_back(s);
					result->operatorParams.push_back(v);
				}
			}
			result->setInputStreams(inputStreams);
			result->setPredicates(conditionList);
			if (win_len > 0) {
				result->setWindowlen(win_len);
				result->setWindowSliding(win_sliding);
			}
			return result;
		}
		else {
			std::cout << "undefined CQ spec term";
			throw "";
		}
	}
	return nullptr;
}