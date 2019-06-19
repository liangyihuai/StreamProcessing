#include "../stdafx.h"

#include "CEPProcess.h"
#include "result/MultEventResult.h"
#include "../op/ExistOp.h"
#include "result/ResultListener.h"

CEPProcess::CEPProcess(vector<string> inputStreamNames, string outputStreamName) {
	this->outputStreamName = outputStreamName;
	this->inputStreamNames = inputStreamNames;
	int inputStreamNum = inputStreamNames.size();
	inputQueues = new vector<queue<EventPtr>*>();
	for (string inputStreamName: inputStreamNames) {
		inputQueues->push_back(new queue<EventPtr>());//initialize input queues
	}
}

bool CEPProcess::process(int timeSlice){
	Window *input_queue_win = nullptr;

	for (int i = 0; i < inputQueues->size(); i++) {
		int timeSlice_i = timeSlice;
		queue<EventPtr> * q = (*inputQueues)[i];
		while (!q->empty() && timeSlice_i > 0) {
			try {
				Predicate* pre = predicates[i];
				if (pre->check(q->front())) {//check query condition before buffering the event.
					input_queue_win = windowList[i];
					input_queue_win->push_back(q->front());
				}
			}catch (std::logic_error& e) {
				std::cout << "[exception caught]\n";
			}
			q->pop();
			timeSlice_i--;

			result();//trigger output results
		}
	}
	return true;
}


//this function is called by function "process".
void CEPProcess::result() {
	if (!ExecuteScheduler::cep_pq.empty()) {
		try {
			std::lock_guard<mutex> lg(ExecuteScheduler::mutexOfCEPPriorityQueue);
			while (ExecuteScheduler::cep_pq.top()->triggerTime <= Utils::getTime()) {
				Process_TriggerTime* ptt = ExecuteScheduler::cep_pq.top();
				CEPProcess* cep = (CEPProcess*)dynamic_cast<CEPProcess*>(ptt->process);
				int satisfiedCount = 0;
				for (int i = 0; i < cep->windowList.size(); i++) {//for each input stream
					bool result = false;
					if (cep->windowList.size() <= i || cep->windowList[i] == nullptr) {
						std::cout << "The operator ExistOp is nullptr, index is " << i << ", outputStreamName is " << outputStreamName;
						throw runtime_error("");
					}
					try {
						//std::lock_guard<mutex> lg(CEPProcess::mutexOfCEPResult);//mutex lock
						bool resultOfExistOp = false;
						cep->windowList[i]->reevaluate(resultOfExistOp);
						if (resultOfExistOp) { satisfiedCount++; }
					}
					catch (std::logic_error& e) {
						std::cout << "[exception caught]\n";
					}
				}
				if (satisfiedCount == cep->windowList.size()) {
					if (cep->resultListener) {
						MultEventResult* result = new MultEventResult();
						result->addDeriveEventPtr(cep->outputStreamName);

						cep->resultListener->update(ResultPtr(result));
					}
				}

				if (ptt->triggerLen <= 0) throw "the trigger length of current process <= 0.";

				ExecuteScheduler::cep_pq.pop();
				ptt->triggerTime = Utils::getTime() + ptt->triggerLen;
				ExecuteScheduler::cep_pq.push(ptt);
			}
		}
		catch (std::logic_error& e) {
			std::cout << "[exception caught]\n";
		}
	}
}

vector<string> CEPProcess::getInputStreamNames() {
	return inputStreamNames;
}

vector<queue<EventPtr>*> CEPProcess::getInputQueues() {
	return *inputQueues;
}

string CEPProcess::getOutputStreamName() {
	return outputStreamName;
}

void CEPProcess::addOutputQueue(queue<EventPtr>* outputQueue, string outputStreamNameOfProcess) {
	std::cout << "not implemented method addOutputQueue";
	throw runtime_error("");
}

set<string> CEPProcess::getConnectedOutputNameSet() {
	std::cout << "not implemented method getConnectedOutputNameSet";
	throw runtime_error("");
}

bool CEPProcess::removeOutputQueueAndNameFromA(string outputNameOfProcessUnitB) {
	return true;
}

bool CEPProcess::removeAllDownStreamQueuesAndNames() {
	return true;
}


void CEPProcess::setInputStreamNames(vector<string> names) {
	this->inputStreamNames = names;
}

void CEPProcess::setResultListener(ResultListener* listener){
    this->resultListener = listener;
}

CEPProcess::~CEPProcess(){
    delete resultListener; resultListener = nullptr;
	for (int i = 0; i < inputQueues->size(); i++) {
		delete (*inputQueues)[i];
		(*inputQueues)[i] = nullptr;
	}
	delete inputQueues;
	inputQueues = nullptr;

	for (Window* win : windowList) {
		delete win;
		win = nullptr;
	}
}

void CEPProcess::setPredicates(vector<Predicate*> preList) {
	this->predicates = preList;
}

void CEPProcess::setWindows(vector<Window*> windowList) {
	this->windowList = windowList;
}