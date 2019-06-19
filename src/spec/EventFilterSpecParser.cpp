#include "../stdafx.h"
#include "EventFilterSpecParser.h"

//list<EventFilterSpec*> EventFilterParser::parseAllEventFilterSpec(const list<string> allCQSpecs) {
//	list<EventFilterSpec*> result;
//	list<string> specStrVec;
//	for (string line : allCQSpecs) {
//		line = Utils::toLower(Utils::trim(line));
//		if (line.size() == 0 || line[0] == '#') continue;
//
//		specStrVec.push_back(line);
//		if (line.find("then") == 0) {
//			result.push_back(parseOneEventFilterSpec(specStrVec));
//			specStrVec.clear();
//		}
//	}
//	return result;
//}

EventFilterSpec* EventFilterParser::parseOneEventFilterSpec(list<string> specStr) {
	EventFilterSpec * eventfilterSpec = new EventFilterSpec();

	for (string s : specStr) {
		s = Utils::toLower(Utils::trim(s));
		if (s.size() == 0 || s[0] == '#') continue;

		if (s.size() == 0) continue;
		size_t index = s.find_first_of(" ", 0);
		if (index < 0) {
			std::cout << "no clause";
			throw runtime_error("no clause");
		}

		string clause = s.substr(0, index);
		string value = s.substr(index + 1, s.size() - index - 1);
		//Utils::deleteAllMark(value, " ");

		if ("if" == clause) {
			vector<string> expList = Utils::split(value, "&");

			for (string exp : expList) {
				exp = Utils::trim(exp);
				int index = exp.find("(");
				string opName = exp.substr(0, index);
				string field = exp.substr(index + 1, exp.size() - index - 2);
				if (opName == "not duplicate") {
					eventfilterSpec->setNotDuplicateField(field);
				}
				else if (opName == "not unusual") {
					eventfilterSpec->addNotUnusualField(field);
				}
			}
		}
		else if ("from" == clause) {
			eventfilterSpec->setInputStream(value);
		}
		else if ("then" == clause) {
			eventfilterSpec->setOutputStream(value);
		}
		else {
			std::cout << "undefined CQ spec term";
			throw "undefined CQ spec term";
		}
	}
	return eventfilterSpec;
}