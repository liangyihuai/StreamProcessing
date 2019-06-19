//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_MIN_H
#define CONTINUOUSPROCESSING_MIN_H

#include "../execution/result/Result.h"
#include "../common/Event.h"
#include "inter/StatefulOperator.h"
#include "../execution/result/DoubleResult.h"

class Min : public StatefulOperator {
    float min = 99999;
    string attr;
public:
    Min(string attrName) :attr(attrName) {}
    ~Min() { }

    //override
    ResultPtr result(EventPtr event);
    //override
    ResultPtr resultMultEvents(list<EventPtr> *eventList, bool isReset);
};

#endif //CONTINUOUSPROCESSING_MIN_H
