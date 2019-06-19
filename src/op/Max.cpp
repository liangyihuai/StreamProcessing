//
// Created by USER on 12/5/2018.
//
#include "../stdafx.h"
#include "Max.h"


ResultPtr Max::result(EventPtr event) {
	throw runtime_error("");
}

ResultPtr Max::resultMultEvents(list<EventPtr> *eventList, bool isReset) {
	float tempMax = -99999;
	float t = 0.0f;
	for (EventPtr e : *eventList) {
		t = e->getFloat(attr);
		if (tempMax < t) tempMax = t;
	}
	if (!isReset) {
		if (max < tempMax) {
			max = tempMax;
		}
		else {
			tempMax = max;
		}
	}
	return ResultPtr(new DoubleResult(tempMax));
}
