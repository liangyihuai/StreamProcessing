#pragma once

#include "Process.h"
#include <vector>
#include <list>
#include "CQIndex.h"

class ProcessRegisterForCQIndex {
public:
	static Process * getProcess(int index);

	static list<Process*> getProcess(vector<int64_t> indexes);

	static void addProcess(Process*);

	static bool deleteProcess(int index);

	static bool deleteProcess(Process*);

	//find the relations between CQ process units. 
	//create an index corresponding with one CQProcess object, and fill the index with conditions.
	//Initialize the field of "processIndexMap".
	static void buildIndexGraph(unordered_map<string, Process*> processMap, int minConnection, int dimension_index);

	//if exist, return number >= 0, else return -1;
	static int getId(Process*);

	//check if the process is indexed.
	static bool isIndexed(Process* pro);

	static CQIndex* getIndexByProcess(Process * pro);

private:
	static vector<Process*> processVector;
	static unordered_map<Process*, CQIndex*> processIndexMap;

	//the processes that are built with CQ index. 
	//able to use index to find out the matching CQs for its output events.
	static unordered_set<Process*> indexedProcessSet;

};


