#include "../stdafx.h"

#include "ApproachingOP.h"
#include "../execution/result/BoolResult.h"

ApproachingOP::ApproachingOP(int min_step, float min_speed, float lon, float lat) {
	this->minStep = min_step;
	this->minSpeed = min_speed;
	this->lon = lon;
	this->lat = lat;

	for (int i = 0; i < Utils::movingObject_id_total_numble; i++) {
		forwardSteps.push_back(new list<bool>());
		lon_previous_steps.push_back(-1);
		lat_previous_steps.push_back(-1);
	}
}

bool ApproachingOP::moving_forwards(EventPtr event) {
	int objectId = event->getInt("objid");
	  
	if (lon_previous_steps[objectId] < 0) return false;

	float previous_lon = lon_previous_steps[objectId];
	float previous_lat = lat_previous_steps[objectId];

	float curr_lon = event->getFloat("lon");
	float curr_lat = event->getFloat("lat");

	if (pow(curr_lon - lon, 2) + pow(curr_lat - lat, 2) < pow(previous_lon - lon, 2) + pow(previous_lat - lat, 2)) {
		return true;
	}
	return false;
}

ResultPtr ApproachingOP::result(EventPtr event) {
	int objectId = event->getInt("objid");

	lon = event->getFloat("lon");
	lat = event->getFloat("lat");

	if (event->getFloat("speed") < minSpeed) {
		this->forwardSteps[objectId]->push_back(false);
		lon_previous_steps[objectId] = lon;
		lat_previous_steps[objectId] = lat;

		return ResultPtr(new BoolResult(false));
	}else if (moving_forwards(event)) {
		lon_previous_steps[objectId] = event->getFloat("lon");
		lat_previous_steps[objectId] = event->getFloat("lat");
		
		forwardSteps[objectId]->push_back(true);

		while (forwardSteps[objectId]->size() > minStep) {
			forwardSteps[objectId]->pop_front();
		}

		bool result = true;
		for (bool b : *forwardSteps[objectId]) {
			if (!b) result = false;
			break;
		}
		if (result == true && forwardSteps[objectId]->size() >= minStep) {
			return ResultPtr(new BoolResult(true));
		}
		else {
			return ResultPtr(new BoolResult(false));
		}
		
	}else {//not move forwards to the target location.
		if (lon_previous_steps[objectId] > 0) {//not the first step
			this->forwardSteps[objectId]->push_back(false);
		}
		else {
			this->forwardSteps[objectId]->push_back(true);
		}
		lon_previous_steps[objectId] = lon;
		lat_previous_steps[objectId] = lat;
		
		return ResultPtr(new BoolResult(false));
	}
}