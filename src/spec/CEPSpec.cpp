#include "../stdafx.h"
#include "CEPSpec.h"
#include "../execution/result/CEPPrintResultListener.h"
#include "../execution/CEPProcess.h"

CEPSpec::CEPSpec() {
	sinkType = SinkType::PRINT_OUT;//the default sink type is print out.
}

Predicate* getPredicateByStreamName_CEPSpec(vector<Predicate*> predicateList, string streamName) {
	for (Predicate* pre : predicateList) {
		if (pre->streamName == streamName) return pre;
	}
	return nullptr;
}

CEPProcess * CEPSpec::instance() {
	CEPProcess* cep = new CEPProcess(inputStreams, outputStreamName);

	//set sliding windows with Exist() operator.
	vector<Window*> windowList;
	for (string inputStreamName : inputStreams) {//生成这么多的win和existOp是不合理的，需要修改
		NaiveTimeSlidingWindow* win = new NaiveTimeSlidingWindow(winLen);
		win->setTimeSliding(winSliding);
		ExistOp* existOp = new ExistOp(inputStreamName);//operator
		win->setStatefulOperator(existOp);
		windowList.push_back(win);//vector
	}
	cep->setWindows(windowList);

	//set output type
	if (sinkType == SinkType::PRINT_OUT) {
		cep->setResultListener(new CEPPrintResultListener());
	}
	else if (sinkType == SinkType::SAVE_FILE) {
		std::cout << "have not implemented file saving";
		throw runtime_error("");
	}

	////////////start to set predicate/////////////
	vector<Predicate*> predicatesResult;
	for (string inputStream : inputStreams) {
		Predicate* pre = getPredicateByStreamName_CEPSpec(predicates, inputStream);
		if (pre != nullptr) {
			predicatesResult.push_back(pre);
		}else {
			Predicate* newPre = new TruePredicate();
			newPre->streamName = inputStream;
			predicatesResult.push_back(newPre);
		}
	}
	cep->setPredicates(predicatesResult);
	///////////end to set predicate////////////////

 	return cep;
}

void CEPSpec::setOutputStreamName(string name) {
	outputStreamName = name;
}

void CEPSpec::addExistOpPredicate(ExistOp * pre, string stream) {
	existOpPredicateList.push_back(pre);
	inputStreams.push_back(stream);
}

string CEPSpec::getOutputStreamName() {
	return this->outputStreamName;
}

void CEPSpec::addPredicate(Predicate* pre) {
	this->predicates.push_back(pre);
}

void CEPSpec::setPredicates(vector<Predicate*> preList) {
	this->predicates = preList;
}

void CEPSpec::setInputStreams(vector<string> inputStreams) {
	this->inputStreams = inputStreams;
}

void CEPSpec::setWinLen(int winLen) {
	this->winLen = winLen;
}

void CEPSpec::setWinSliding(int sliding) {
	this->winSliding = sliding;
}