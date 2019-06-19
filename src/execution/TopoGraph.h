#pragma once

#include <queue>
#include "../execution/EventProcess.h"
#include "../execution/Process.h"
#include <unordered_map>
#include "../execution/CEPProcess.h"
#include <set>

/*
This class is to build topo computation graph for processing units, 
including Event Filtering, Event Capture, CQ and CEP. 
*/
class TopoGraph {
public:
	static void addProcessUnitToGraph(Process* pro);
	static void removeProcessFromGraph(string outputStreamName);
	static void setEventFilter(EventProcess* ep);
	//make eventProcess==nullptr, and clear processMap.
	static void clear();
private:
	static void addProcessUnitToGraph(string inputStreamNameOfB, queue<EventPtr> * inputQueueOfB, string outputNameOfB);

private:
	static EventProcess *eventProcess;
	//output stream name -> process
	static std::unordered_map<string, Process*> processMap;
};
