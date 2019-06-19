#include "../stdafx.h"
#include "EventCapture.h"
#include "../cqindex/ProcessRegisterForCQIndex.h"

EventCapture::EventCapture(string _outputStreamName) {
	inputQueue = new queue<EventPtr>();
	this->outputStreamName = _outputStreamName;
}

vector<string> EventCapture::getInputStreamNames() {
	vector<string> result;
	result.push_back(inputStreamName);
	return result;
}

vector<queue<EventPtr>*> EventCapture::getInputQueues() {
	vector<queue<EventPtr>*> result;
	result.push_back(inputQueue);
	return result;
}

string EventCapture::getOutputStreamName() {
	return outputStreamName;
}

void EventCapture::addOutputQueue(queue<EventPtr>* inputQueueOfDownstreamProcessUnit, string outputNameOfDownstreamProcessUnit) {
	inputQueueSetOfDownstreamProcessUnit.push_back(inputQueueOfDownstreamProcessUnit);
	outputNameSetOfDownstreamProcessUnit.push_back(outputNameOfDownstreamProcessUnit);
}

EventCapture::~EventCapture() {
	while (inputQueue != nullptr && !inputQueue->empty()) {
		inputQueue->pop();
	}
	delete inputQueue; 
	inputQueue = nullptr;
	//delete outputQueue;
}

bool EventCapture::process(int timeSlice) {
	EventPtr e = nullptr;
	while (!inputQueue->empty() && timeSlice > 0) {
		try {
			lock_guard<mutex> lg(EventProcess::mutexOfEventFiler);//mutex threat
			e = inputQueue->front();
			inputQueue->pop();
		}catch (std::logic_error& e) {
			std::cout << "[exception caught]\n";
		}
		if (condition.check(e)) {
			//cout << "EC[" << outputStreamName << "] " << *e << endl;
			for (queue<EventPtr>* q : inputQueueSetOfDownstreamProcessUnit) {
				q->push(e);
			}
		}
		timeSlice--;
	}
	if (!inputQueue->empty()) return false;
	return true;
}

queue<EventPtr>* EventCapture::getInputQueue() {
	return this->inputQueue;
}

void EventCapture::setCondition(Condition condition) {
	this->condition = condition;
}

void EventCapture::setInputStreamName(string name) {
	this->inputStreamName = name;
}

void EventCapture::setOutputStreamName(string name) {
	this->outputStreamName = name;
}

set<string> EventCapture::getConnectedOutputNameSet() {
	set<string> s;
	for (string name : outputNameSetOfDownstreamProcessUnit) {
		s.insert(name);
	}
	return s;
}

bool EventCapture::removeOutputQueueAndNameFromA(string outputNameOfProcessUnitB) {
	for (int i = 0; i < outputNameSetOfDownstreamProcessUnit.size(); i++) {
		if (outputNameSetOfDownstreamProcessUnit[i] == outputNameOfProcessUnitB) {
			delete inputQueueSetOfDownstreamProcessUnit[i];

			int j = i + 1;
			for (; j < outputNameSetOfDownstreamProcessUnit.size(); j++) {//move reaward one step.
				outputNameSetOfDownstreamProcessUnit[j - 1] = outputNameSetOfDownstreamProcessUnit[j];
				inputQueueSetOfDownstreamProcessUnit[j - 1] = inputQueueSetOfDownstreamProcessUnit[j];
			}
			outputNameSetOfDownstreamProcessUnit.pop_back();
			inputQueueSetOfDownstreamProcessUnit.pop_back();
			return true;
		}
	}
	return false;
}

bool EventCapture::removeAllDownStreamQueuesAndNames() {
	inputQueueSetOfDownstreamProcessUnit.clear();
	outputNameSetOfDownstreamProcessUnit.clear();
	return true;
}