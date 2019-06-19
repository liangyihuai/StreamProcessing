//
// Created by USER on 12/6/2018.
//

#ifndef CONTINUOUSPROCESSING_DISTANCEOP_H
#define CONTINUOUSPROCESSING_DISTANCEOP_H

#include "inter/Operator.h"

//DoubleResult
class DistanceOp : public Operator{
private:
	string nameX;
	string nameY;
	float fixedPointX;
	float fixedPointY;
public:
	DistanceOp(string _nameX, string _nameY, float fixedPointX, float fixedPointY) {
		this->nameX = _nameX;
		this->nameY = _nameY;
		this->fixedPointX = fixedPointX;
		this->fixedPointY = fixedPointY;
	}

	ResultPtr result(EventPtr event);
};


#endif //CONTINUOUSPROCESSING_DISTANCEOP_H
