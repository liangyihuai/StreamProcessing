#pragma once

#include "EventCaptureSpec.h"
#include "SpecParser.h"

//现在暂时不支持字段的类型，暂时统一表示为string类型
class EventCaptureSpecParser: public SpecParser {
public:
	/*static list<EventCaptureSpec*> parseAllEventCaptureSpec(const list<string> allCQSpecs) {
		list<EventCaptureSpec*> result;
		list<string> cqSpec;
		for (string line : allCQSpecs) {
			line = Utils::toLower(Utils::trim(line));
			if (line.size() == 0 || line[0] == '#') continue;

			cqSpec.push_back(line);
			if (line.find("then") == 0) {
				EventCaptureSpec* spec = parseOneEventCaptureSpec(cqSpec);
				result.push_back(spec);
				cqSpec.clear();
			}
		}
		return result;
	}*/

	/*
	If distance < 20
	From airplane
	Window type=, len=, sliding=
	Then WideAreaDefenceTarget
	*/
	static EventCaptureSpec* parseOneEventCaptureSpec(list<string> oneCQSpec) {
		EventCaptureSpec * result = nullptr;
		Predicate* condition = nullptr;
		string inputStream;
		string streamSource;

		for (string s : oneCQSpec) {
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
			Utils::deleteAllMark(value, " ");

			if ("if" == clause) {
				vector<Predicate*> preVec = parseMultiExpression(value);
				condition = preVec[0];
			}
			else if ("from" == clause) {
				inputStream = value;
			}
			else if ("window" == clause) {

			}
			else if ("then" == clause) {
				string outputStreamName = value;

				result = new EventCaptureSpec();
				result->setInputStream(inputStream);
				result->setOutputStream(outputStreamName);
				result->setCondition(condition);
				return result;
			}
			else {
				std::cout << "undefined CQ spec term";
				throw "undefined CQ spec term";
			}
		}
		return nullptr;
	}
};