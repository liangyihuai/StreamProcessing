#pragma once

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include "../spec/EventFilterSpec.h"
#include "../spec/EventCaptureSpec.h"
#include "../spec/CQSpec.h"
#include "../spec/CEPSpec.h"
#include <vector>
#include "Utils.h"
#include "../spec/CQSpec.h"
#include <list>

using namespace std;

//A tool class to read input spec text.
class FileReaderUtils {

public:
	static list<string> readFile(string file) {
		ifstream infile;
		infile.open(file.data());
		if (!infile.is_open()) {
			std::cout << "can not open the file";
			throw "";
		}
		string s;
		list<string> lines;

		bool isStarted = false;
		while (getline(infile, s)) {
			s = Utils::trim(s);
			if (s == "start") {
				isStarted = true;
				continue;
			}
			if (s == "end") break;
			if (isStarted)lines.push_back(s);
		}
		return lines;
	}
};

