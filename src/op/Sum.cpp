//
// Created by USER on 12/5/2018.
//
#include "../stdafx.h"
#include "Sum.h"

ResultPtr Sum::result(EventPtr event) {
	throw runtime_error("");
}


ResultPtr Sum::resultMultEvents(list<EventPtr> *eventList, bool isReset) {
	double tempSum = 0.0;
	if (!isReset) tempSum = this->sum;

	for (EventPtr e : *eventList) {
		tempSum += e->getFloat(attrName);
	}
	if (!isReset) this->sum = tempSum;

	return ResultPtr(new DoubleResult(tempSum));
}