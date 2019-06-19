#ifndef CONTINUOUSPROCESSING_EVENTCAPTURE_H
#define CONTINUOUSPROCESSING_EVENTCAPTURE_H


#include "../expression/Condition.h"
#include "result/ResultListener.h"
#include "Process.h"
#include <queue>
#include <set>


class EventCapture: public Process{
public:
	EventCapture(string _outputStreamName);
	~EventCapture();

	//---------------------------
	//implemented methods
	//---------------------------
	bool process(int timeSlice = 100)override;

	vector<string> getInputStreamNames()override;

	vector<queue<EventPtr>*> getInputQueues()override;

	string getOutputStreamName()override;

	//string outputStreamNameOfProcess, the output stream name connected to this process unit.
	void addOutputQueue(queue<EventPtr>* inputQueueOfDownstreamProcessUnit, string outputNameOfDownstreamProcessUnit)override;

	set<string> getConnectedOutputNameSet()override;

	//Process unit B connects to A downstream. It means that the input of B is from A.
	bool removeOutputQueueAndNameFromA(string outputNameOfProcessUnitB) override;

	bool removeAllDownStreamQueuesAndNames()override;

	//--------------------------
	//other methods
	//---------------------------
	void setCondition(Condition condition);
	void setInputStreamName(string name);
	void setOutputStreamName(string name);
	queue<EventPtr>* getInputQueue();

private:
	queue<EventPtr>* inputQueue;

	//the input queue of other processing unit, so this class should not maintain deallocate it memory
	vector<queue<EventPtr>*> inputQueueSetOfDownstreamProcessUnit;

	//the output names of process that connects to this process unit.
	vector<string> outputNameSetOfDownstreamProcessUnit;

	Condition condition;
	string inputStreamName;
	string outputStreamName;
};

#endif //CONTINUOUSPROCESSING_EVENTCAPTURE_H