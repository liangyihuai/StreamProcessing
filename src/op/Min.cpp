//
// Created by USER on 12/5/2018.
//
#include "../stdafx.h"
#include "Min.h"

ResultPtr Min::result(EventPtr event) {
	throw runtime_error("");
}

ResultPtr Min::resultMultEvents(list<EventPtr> *eventList, bool isReset) {
	float tempMin = 99999;
	float t = 0.0f;
	for (EventPtr e : *eventList) {
		t = e->getFloat(attr);
		if (tempMin > t) tempMin = t;
	}
	if (!isReset) {
		if (min > tempMin) {
			min = tempMin;
		}
		else {
			tempMin = min;
		}
	}
	return ResultPtr(new DoubleResult(tempMin));
}
