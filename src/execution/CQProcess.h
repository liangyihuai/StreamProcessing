//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_CQPROCESS_H
#define CONTINUOUSPROCESSING_CQPROCESS_H


#include "../common/Event.h"
#include "Process.h"
#include <vector>
#include "../expression/Condition.h"
#include "../op/inter/Operator.h"
#include "../expression/OperatorPredicate.h"
#include <unordered_map>
#include <queue>
#include <set>
#include "ExecuteScheduler.h"

//the ResultListener return DerivedEventPtr.
class CQProcess : public Process{
	friend class ExecuteScheduler;
public:
	CQProcess(vector<string> inputStreamNames, string outputStreamName);
	~CQProcess();

	//---------------------------
	//implemented methods
	//-------------------------
	bool process(int timeSlice)override;
	//string outputStreamNameOfProcess, the output stream name connected to this process unit.
	void addOutputQueue(queue<EventPtr> *outputQueue, string outputStreamNameOfProcess)override;
	vector<string> getInputStreamNames()override;
	vector<queue<EventPtr>*> getInputQueues()override;
	string getOutputStreamName()override;
	set<string> getConnectedOutputNameSet()override;
	
	//Process unit B connects to A downstream. It means that the input of B is from A.
	bool removeOutputQueueAndNameFromA(string outputNameOfProcessUnitB) override;

	bool removeAllDownStreamQueuesAndNames() override;
    
	//--------------------------------
	//other
	//---------------------------------
    void addPredicate(Predicate * pre);
	void setPredicates(vector<Predicate*> preList);
    void setOutputStreamName(string name);
	void setInputStreamNames(vector<string> names);
    void setWindows(vector<Window*> win);
	vector<Predicate*> getPredicates();
	void addEventToQueue(EventPtr e, queue<EventPtr>& q);
	void triggerResult();

private:
	vector<string> inputStreamNames;
	vector<Window*> windowList;

	//the result name of stream after processing
	string outputStreamName;
	vector<queue<EventPtr>*> inputQueues;
	//the input queue of other processing units.
	vector<queue<EventPtr>*> inputQueueSetOfDownstreamProcessUnit;
	//the output names of process that connects to this process unit.
	vector<string> outputNameSetOfDownstreamProcessUnit;
	// all stateless operatorPredicates and simple predicates share one queue reader.
	vector<Predicate*> predicates;
	

};
#endif //CONTINUOUSPROCESSING_CQPROCESS_H
