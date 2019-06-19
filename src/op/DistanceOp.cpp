//
// Created by USER on 12/6/2018.
//
#include "../stdafx.h"
#include "DistanceOp.h"

ResultPtr DistanceOp::result(EventPtr event) {
	float x = event->getFloat(nameX);
	float y = event->getFloat(nameY);
	float result = sqrtf(powf(x - fixedPointX, 2) + powf(y - fixedPointY, 2));

	return ResultPtr(new DoubleResult(result));
}