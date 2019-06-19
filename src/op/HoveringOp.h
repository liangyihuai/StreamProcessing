#pragma once

#include <vector>
#include "inter/Operator.h"

class HoveringOp :public Operator {
private:
	int windowLen;
	vector<list<EventPtr>*> windowList;
	
	float min_speed;

	float target_lon;
	float target_lat;

private:
	void refresh(list<EventPtr>* win);

public:

	HoveringOp(float targetLon, float targetLat, float minSpeed, int window_len );

	~HoveringOp();

	ResultPtr result(EventPtr event) override;
};