#pragma once

#include <unordered_map>
#include "EventProcess.h"
#include "EventCapture.h"
#include "CQProcess.h"
#include "CEPProcess.h"
#include "Process.h"
#include "TopoGraph.h"
#include "ProcessRegister.h"
#include <queue>

//将Process对象和它的最近的结果出发时间关联起来
struct Process_TriggerTime {
	Process* process = nullptr;
	long long triggerTime = -1; // current time plus triggerLen;
	int triggerLen = -1; //time length to trigger, for example 1000ms

	Process_TriggerTime() {}

	Process_TriggerTime(Process* p, int triggerLen) {
		this->process = p;
		this->triggerLen = triggerLen;
	}

	~Process_TriggerTime() {
	}
};

struct cmp {
	bool operator()(Process_TriggerTime* a, Process_TriggerTime* b) {
		return a->triggerTime > b->triggerTime;
	}
};

/*
维护一个输入队列不为空的cp队列，循环消费cp中输入队列中的数据，直到cp队列为空。
1. 在输入队列不为空的时候，将相应的队列加入cp队列中.
2. 不断从cp队列头部弹出一个cp，消费cp的输入队列timeSlice个数据或者队列为空。如果消费了timeSlice个数据之后，该队列不为空，
就将其添加到cp队列的尾部。如果该cp有多个输入队列，只要有一个队列为空，就不将该cp加入cp队列中。
*/
class ExecuteScheduler {
	friend class CQProcess;
	friend class CEPProcess;
public:
	static void initialize();
	static void runProcessQueue();
	static void buildGraph();
	static void rebuildGraph();

	//构建优先级队列,让最先需要触发输出结果的process在堆的顶部
	static void buildTriggerTimePriorityQueue();
private:

	//currently it is only for CQProcess.
	static priority_queue<Process_TriggerTime*, vector<Process_TriggerTime*>, cmp > cq_pq;

	static priority_queue<Process_TriggerTime*, vector<Process_TriggerTime*>, cmp > cep_pq;

	static mutex mutexOfCQPriorityQueue;//mutex lock among threads

	static mutex mutexOfCEPPriorityQueue;//mutex lock among threads
};


