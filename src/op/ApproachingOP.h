#pragma once

#include <vector>
#include "inter/Operator.h"

/*
1. observing step >= minStep
2. current speec > minSpeed
3. the moving object is moving forwards within the latest minStep.
*/
class ApproachingOP : public Operator {
private:

	vector<float> lon_previous_steps;
	vector<float> lat_previous_steps;

	vector<list<bool>*> forwardSteps;

	/*Configuration fields*/
	int minStep;
	float minSpeed;
	float lon;
	float lat;

private:

	//whether the moving object of current event is moving forward to the target location.
	bool moving_forwards(EventPtr currEvent);

public:

	ApproachingOP(int min_step, float min_speed, float lon, float lat);

	ResultPtr result(EventPtr event) override;

};