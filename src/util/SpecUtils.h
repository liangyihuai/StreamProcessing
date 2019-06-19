#pragma once

#include <string>
#include <list>
#include "Utils.h"

using namespace std;

class SpecUtils {
public:
	//one rule contains multiple strings, get input stream name from "From" clause.
	static list<string> getInputStream(list<string> one_rule_strs) {
		list<string> result;
		int index = -1;
		for (string line : one_rule_strs) {
			line = Utils::toLower(line);
			if ((index = line.find("from")) > -1) {
				vector<string> sp = Utils::split(line, ",");
				if (sp.size() == 0) {
					std::cout << "illegal rule spec, it is : " << line;
					throw runtime_error("");
				}
				for (int i = 1; i < sp.size(); i++) {
					result.push_back(sp[i]);
				}
				return result;
			}
		}
		std::cout << "illegal rule spec. Inside the rule, there is no \"from\" clause.it is : ";
		for (string line : one_rule_strs) {
			std::cout << line << "\r\n";
		}
		throw runtime_error("");
	}

	static list<string> getInputStream(vector<string> one_rule_strs) {
		list<string> result;
		int index = -1;
		for (string line : one_rule_strs) {
			line = Utils::toLower(line);
			if ((index = line.find("from")) > -1) {
				line = line.substr(index+5, line.size());
				vector<string> sp = Utils::split(line, ",");
				
				for (int i = 0; i < sp.size(); i++) {
					result.push_back(Utils::trim(sp[i]));
				}
				return result;
			}
		}
		std::cout << "illegal rule spec. Inside the rule, there is no \"from\" clause.it is : ";
		for (string line : one_rule_strs) {
			std::cout << line << "\r\n";
		}
		throw runtime_error("");
	}

};