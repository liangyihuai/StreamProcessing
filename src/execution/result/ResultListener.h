//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_RESULTLISTENER_H
#define CONTINUOUSPROCESSING_RESULTLISTENER_H

#include "Result.h"


class ResultListener {
public:
	virtual void update(const ResultPtr& result) = 0;
};

#endif //CONTINUOUSPROCESSING_RESULTLISTENER_H