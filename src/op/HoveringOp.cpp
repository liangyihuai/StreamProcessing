#include "../stdafx.h"

#include "HoveringOp.h"

HoveringOp::HoveringOp(float targetLon, float targetLat, float minSpeed, int window_len) {
	this->target_lon = targetLon;
	this->target_lat = targetLat;
	this->min_speed = minSpeed;
	this->windowLen = window_len;

	for (int i = 0; i < Utils::movingObject_id_total_numble; i++) {
		windowList.push_back(new list<EventPtr>());
	}
}

ResultPtr HoveringOp::result(EventPtr event) {
	float speed = event->getFloat("speed");
	int objId = event->getInt("objid");

	windowList[objId]->push_back(event);

	//the first event of the obj.
	if (windowList[objId]->size() == 1 && speed < min_speed) {
		windowList[objId]->push_back(event);
		return ResultPtr(new BoolResult(true));
	}
	else{//the average speed of the object is less than min_speed
		double sum = 0.0;
		for (EventPtr e : *windowList[objId]) {
			sum += e->getFloat("speed");
		}
		float ave = sum / windowList[objId]->size();
		if (ave < min_speed)
			return ResultPtr(new BoolResult(true));
	}
	
	refresh(windowList[objId]);
	list<EventPtr>* win = windowList[objId];
	if(win->size() < 3) return ResultPtr(new BoolResult(false));

	auto iter = win->begin(); //reverse iterator
	EventPtr e1 = *iter;
	iter++;
	EventPtr e2 = *iter;
	iter++;

	float distance1 = pow(e1->getFloat("lon") - target_lon, 2) + pow(e1->getFloat("lat") - target_lat, 2);
	float distance2 = pow(e2->getFloat("lon") - target_lon, 2) + pow(e2->getFloat("lat") - target_lat, 2);
	float direction1 = distance2 - distance1;
	while (iter != win->end()) {
		e1 = e2;
		e2 = *iter;
		distance1 = pow(e1->getFloat("lon") - target_lon, 2) + pow(e1->getFloat("lat") - target_lat, 2);
		distance2 = pow(e2->getFloat("lon") - target_lon, 2) + pow(e2->getFloat("lat") - target_lat, 2);
		float direction2 = distance2 - distance1;
		if ((direction1 > 0 && direction2 < 0) || (direction1 < 0 && direction2 > 0)) {
			return ResultPtr(new BoolResult(true));
		}
		iter++;
	}
	return ResultPtr(new BoolResult(false));
}

void HoveringOp::refresh(list<EventPtr>* win) {
	while (win->front()->getTime() + windowLen < Utils::getTime()) {
		win->pop_front();
	}
}

HoveringOp::~HoveringOp() {
	for (list<EventPtr>* li : windowList) {
		li->clear();
		delete li;
		li = nullptr;
	}
}