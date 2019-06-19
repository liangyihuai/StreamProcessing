#include "../stdafx.h"
#include "Process.h"

Process::~Process() {
	for (vector<string>* v : operatorParamaters) {
		delete v;
		v = nullptr;
	}
}