#include "../stdafx.h"
#include "CQSpec.h"
#include "../execution/CQProcess.h"
#include "../op/win/NaiveTimeDistinctSlidingWindow.h"


Predicate* getPredicateByStreamName(vector<Predicate*> predicateList, string streamName) {
	if (predicateList.size() == 1)//if there is only one predicate in the list.
		return predicateList[0];

	for (Predicate* pre : predicateList) {
		if (pre->streamName == streamName) return pre;
	}
	return nullptr;
}

CQProcess * CQSpec::instance() {
	CQProcess* cq = new CQProcess(inputStreams, outputStream);
	if (winLen > 0) {
		vector<Window*> windowList;
		for (int i = 0; i < inputStreams.size(); i++) {//这里一概生成这么多个win，是有问题的。
													//应该只生成必要的win
			NaiveTimeSlidingWindow* nWin = nullptr;
			if (distinctField.length() > 0) {
				nWin = new NaiveTimeSlidingWindow(winLen);
			}else {
				NaiveTimeDistinctSlidingWindow* distinctWin = new NaiveTimeDistinctSlidingWindow(winLen);
				distinctWin->setDistinctField(distinctField);
				nWin = distinctWin;
			}
			nWin->setTimeSliding(winSliding);
			windowList.push_back(nWin);
			
			for (string opName : operatorNames) {
				if (opName == "count") {
					Operator * op = OperatorRegister::getInstance("count", vector<string>());
					StatefulOperator* countOp =(StatefulOperator*)dynamic_cast<StatefulOperator*>(op);
					nWin->setStatefulOperator(countOp);
				}
				else {
					cout << "Not implemented the stateful operator for a sliding window, name is " << opName << endl;
					throw "";
				}
			}
		}
		cq->setWindows(windowList);
	}
	cq->newAttrNames = newAttrNames;
	cq->newAttrValues = newAttrValues;
	cq->operatorNames = operatorNames;
	cq->operatorParamaters = operatorParams;
	cq->setOutputStreamName(outputStream);

	////////////start to set predicate/////////////
	vector<Predicate*> predicatesResult;
	for (string inputStream : inputStreams) {
		Predicate* pre = getPredicateByStreamName(predicateList, inputStream);
		if (pre != nullptr) {
			predicatesResult.push_back(pre);
		}else {
			Predicate* newPre = new TruePredicate();
			newPre->streamName = inputStream;
			predicatesResult.push_back(newPre);
		}
	}
	cq->setPredicates(predicatesResult);
	///////////end to set predicate////////////////

 	return cq;
}

void CQSpec::setInputStreams(vector<string> names) {
	this->inputStreams = names;
}

void CQSpec::setOutputStream(string name) {
	this->outputStream = name;
}

void CQSpec::setPredicates(vector<Predicate*> preList) {
	this->predicateList = preList;
}

void CQSpec::setWindowlen(int len) {
	this->winLen = len;
}

void CQSpec::setWindowSliding(int sliding) {
	this->winSliding = sliding;
}

string CQSpec::getOutputStreamName() {
	return this->outputStream;
}