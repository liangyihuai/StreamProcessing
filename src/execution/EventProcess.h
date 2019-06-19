#ifndef CONTINUOUSPROCESSING_EVENTPROCESS_H
#define CONTINUOUSPROCESSING_EVENTPROCESS_H

#include <iostream>
#include <unordered_set>
#include <queue>
#include <list>
#include "../common/Event.h"
#include <set>
#include <mutex>

using namespace std;

class EventProcess{
private:
	//name of input stream
	string inputStream;

	//name of output stream
	string outputStreamName;

	set<queue<EventPtr>*> outputQueueSet;

    unordered_set<string> set;//for deduplication
    list<EventPtr> queueForDeduplication;//for deduplication
    string deduplicationField;//the field name that make deduplication
    int deduplicateBufferSize;
    list<string> unusualFieldNames;
public:
	//a mutex lock between event filter processing and event capture processing.
	//目前所有的event filter只有一个锁，以后应该改进，使得每一个queue有一个单独的互斥锁
	static mutex mutexOfEventFiler;
	
public:
	EventProcess(int deduplicateBufferSize = 10);
	~EventProcess();

	void addOutputQueue(queue<EventPtr>* q);

	void setDeduplicationField(string field);

	void addUnusualName(string name);

    //filter the incoming events based on the "deduplicatedFiled" and "unusualFieldNames" setup.
	void process(EventPtr e);

	void setInputStream(string name);

	void setOutputStreamName(string name);

	string getOutputStreamName();

private:
    //if the actual event number is greater than deduplicateBufferSize, remove the old event
	void removeOldEvent();

	bool isDuplicated(EventPtr e);

	bool isUnusual(EventPtr e, string field);
};
#endif //CONTINUOUSPROCESSING_EVENTPROCESS_H
