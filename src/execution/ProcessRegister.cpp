#include "../stdafx.h"
#include "ProcessRegister.h"

std::recursive_mutex ProcessRegister::mutexOfProcessRegister;

EventProcess * ProcessRegister::eventProcess;

set<Process*> ProcessRegister::processSet;

//output stream name -> process
std::unordered_map<string, Process*> ProcessRegister::processMap;

set<CEPProcess*> ProcessRegister::cepSet;
vector<Process*> ProcessRegister::eventCaptureVec;
vector<Process*> ProcessRegister::cqVec;

void ProcessRegister::addProcess(Process* pro) {
	try {
 		std::lock_guard<std::recursive_mutex> lg(mutexOfProcessRegister);//mutex lock
		if (processSet.find(pro) != processSet.end()) 
			return;//existing
		processSet.insert(pro);

		processMap[pro->getOutputStreamName()] = pro;
		if (dynamic_cast<CEPProcess*>(pro)) {
			cepSet.insert(dynamic_cast<CEPProcess*>(pro));
		}
		else if (dynamic_cast<CQProcess*>(pro)) {
			cqVec.push_back(pro);
		}
		else if (dynamic_cast<EventCapture*>(pro)) {
			eventCaptureVec.push_back(pro);
		}
	}
	catch (runtime_error e) {
		string msg = e.what();
		std::cout << "[exception caught]:" << msg << "\n";
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
}

void ProcessRegister::registerEventFilter(EventProcess* ep) {
	try {
		std::lock_guard<std::recursive_mutex> lg(ProcessRegister::mutexOfProcessRegister);//mutex lock
		eventProcess = ep;
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
}

void ProcessRegister::removeProcess(string outputStreamName) {
	try {
		std::lock_guard<std::recursive_mutex> lg(ProcessRegister::mutexOfProcessRegister);//mutex lock
		Process * pro = processMap[outputStreamName];
		if (dynamic_cast<CEPProcess*>(pro)) {
			cepSet.erase(dynamic_cast<CEPProcess*>(pro));
		}
		else if (dynamic_cast<CQProcess*>(pro)) {
			for (auto iter = cqVec.begin(); iter != cqVec.end(); iter++) {
				if (*iter == pro) {
					cqVec.erase(iter);
					break;
				}
			}
		}
		else if (dynamic_cast<EventCapture*>(pro)) {
			for (auto iter = eventCaptureVec.begin(); iter != eventCaptureVec.end(); iter++) {
				if (*iter == pro) {
					eventCaptureVec.erase(iter);
					break;
				}
			}
		}
		processSet.erase(pro);
		processMap.erase(outputStreamName);
		delete pro;
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
}

Process* ProcessRegister::getProcess(string outputStreamName) {
	try {
		std::lock_guard<std::recursive_mutex> lg(ProcessRegister::mutexOfProcessRegister);//mutex lock
		return processMap[outputStreamName];
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
}

set<Process*> ProcessRegister::allProcess() {
	return processSet;
}

EventProcess * ProcessRegister::getProcessOfEventFiltering() {
	try {
		std::lock_guard<std::recursive_mutex> lg(ProcessRegister::mutexOfProcessRegister);//mutex lock
		return eventProcess;
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
}

bool ProcessRegister::isExist(Process* pro) {
	try {
		std::lock_guard<std::recursive_mutex> lg(ProcessRegister::mutexOfProcessRegister);//mutex lock
		return pro != nullptr && processSet.find(pro) != processSet.end();
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
	return false;
}

set<CEPProcess*> ProcessRegister::getCEPs() {
	return cepSet;
}

vector<Process*>& ProcessRegister::getAllEventCapture() {
	return eventCaptureVec;
}

vector<Process*>& ProcessRegister::getAllCQ() {
	return cqVec;
}