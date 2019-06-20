#pragma once

#include <iostream>
#include <vector>
#include <list>
#include "../util/Utils.h"
#include "../spec/EventFilterSpecParser.h"
#include "../spec/EventCaptureSpecParser.h"
#include "../spec/CQSpecParser.h"
#include "../spec/CEPSpecParser.h"
#include "../spec/EventFilterSpec.h"
#include "../spec/EventCaptureSpec.h"
#include"../spec/CQSpec.h"
#include "../spec/CEPSpec.h"
#include "../execution/ProcessRegister.h"
#include "../spec/SpecRegister.h"

using namespace std;

class RuleRegisterUtils {
public:
	//Change CString to string type
	static void specProcessWithCString(CString ruleSpec, string& specLines_out) {
		//parse event capture rules
		specLines_out = CW2A(ruleSpec.GetString());
	}

	//CLow case; Change multiple lines of string to list<string>
	static void specPreprocess(const string ruleSpec, list<string>& specLines_out) {
		vector<string> lines = Utils::split(ruleSpec, "\r\n");
		list<string>lines_list;
		for (string line : lines) {
			line = Utils::trim(line);
			if (line.length() == 0) continue;
			lines_list.push_back(line);
		}
		specLines_out = lines_list;
	}

	static void registerEventFilter(string ruleSpec) {
		list<string> specLines;
		specPreprocess(ruleSpec, specLines);

		EventFilterSpec* eventFilterSpec = EventFilterParser::parseOneEventFilterSpec(specLines);
		EventProcess* ec = eventFilterSpec->instance();
		ProcessRegister::registerEventFilter(ec);
	}

	static void registerEventCapture(string ruleSpec) {
		list<string> specLines;
		specPreprocess(ruleSpec, specLines);
		EventCaptureSpec* spec = EventCaptureSpecParser::parseOneEventCaptureSpec(specLines);
		EventCapture* ec = spec->instance();
		ProcessRegister::addProcess(ec);
		//store rule specification
		SpecRegister::register_event_capture_rule(spec->getOutputStream(), ruleSpec);
	}

	static void registerCQ(string ruleSpec) {
		list<string> specLines;
		specPreprocess(ruleSpec, specLines);
		CQSpec* cqSpec = CQSpecParser::parseOneCQSpec(specLines);
		CQProcess* cq = cqSpec->instance();
		ProcessRegister::addProcess(cq);
		//store rule specification
		SpecRegister::register_cq_rule(cqSpec->getOutputStreamName(), ruleSpec);
	}

	static void registerCEP(string ruleSpec) {
		list<string> specLines;
		specPreprocess(ruleSpec, specLines);
		CEPSpec* cepSpec = CEPSpecParser::parseOneCEPSpec(specLines);
		CEPProcess* cep = cepSpec->instance();
		ProcessRegister::addProcess(cep);
		//store rule specifications
		SpecRegister::register_cep_rule(cepSpec->getOutputStreamName(), ruleSpec);
	}

};

