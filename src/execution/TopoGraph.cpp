#include "../stdafx.h"

#include "TopoGraph.h"

EventProcess *TopoGraph::eventProcess = nullptr;

std::unordered_map<string, Process*> TopoGraph::processMap;

void TopoGraph::setEventFilter(EventProcess* ep) {
	eventProcess = ep;
}

void TopoGraph::removeProcessFromGraph(string outputStreamName) {
	if (eventProcess 
		&& eventProcess->getOutputStreamName() == outputStreamName) {//Event Filtering
		eventProcess = nullptr;
		return;
	}
	if (processMap.find(outputStreamName) == processMap.end()) return; // not exists

	//1. get input stream names
	//2. delete the output steram name of B in A based on the input stream names in B.
	Process* proB = processMap[outputStreamName];
	vector<string> inputNamesInB = proB->getInputStreamNames();
	for (string inputNameInB : inputNamesInB) {
		Process* proA = processMap[inputNameInB];
		proA->removeOutputQueueAndNameFromA(outputStreamName);
	}

	delete proB;
	processMap.erase(outputStreamName);
}

void TopoGraph::addProcessUnitToGraph(Process* processB) {
	if (eventProcess == nullptr) 
		throw "the process of Event Filter is null, please set it up first.";
	if (!processB) return; // nullptr
	if (processMap.find(processB->getOutputStreamName()) != processMap.end()) 
		return; // element existing

	//debug
	string on = processB->getOutputStreamName();

	processMap[processB->getOutputStreamName()] = processB;

	vector<string> inputNamesOfB = processB->getInputStreamNames();
	vector<queue<EventPtr>*> inputQueuesOfB = processB->getInputQueues();
	for (int i = 0; i < inputNamesOfB.size(); i++) {
		addProcessUnitToGraph(inputNamesOfB[i], inputQueuesOfB[i], processB-> getOutputStreamName());
	}
}

void TopoGraph::addProcessUnitToGraph(string inputNameOfB, 
			queue<EventPtr> * inputQueueOfB, string outputNameOfB) {
	if (eventProcess && eventProcess->getOutputStreamName() == inputNameOfB) {//Event Filtering
		eventProcess->addOutputQueue(inputQueueOfB);
	}
	else {//Event Capture, CQ, CEP
		for (auto iter = processMap.begin(); iter != processMap.end(); iter++) {
			Process * pro = iter->second;
			string outputNameOfA = pro->getOutputStreamName();
			if (outputNameOfA == inputNameOfB) {
				//inputQueueOfDownstreamProcessUnit, outputNameOfDownstreamProcessUnit
				pro->addOutputQueue(inputQueueOfB, outputNameOfB);
			}
		}
	}
}

void TopoGraph::clear() {
	eventProcess = nullptr;
	processMap.clear();
}