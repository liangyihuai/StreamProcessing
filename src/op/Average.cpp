//
// Created by USER on 12/5/2018.
//

#include "../stdafx.h"
#include "Average.h"

ResultPtr Average::result(EventPtr event) {
	cout << "not implemented." << endl;
	throw runtime_error("");
}

ResultPtr Average::resultMultEvents(list<EventPtr> *eventList, bool isReset) {
	double tempSum = 0.0;
	int tempCount = 0;
	for (EventPtr e : *eventList) {
		tempSum += e->getFloat(attrName);
		tempCount++;
	}
	if (!isReset) {
		this->sum += tempSum;
		this->count += tempCount;
	}else {
		this->sum = tempSum;
		this->count = tempCount;
	}
	if (count < 1) {
		return ResultPtr(new DoubleResult(0.0));
	}else
		return ResultPtr(new DoubleResult((double)(sum / count)));
}
