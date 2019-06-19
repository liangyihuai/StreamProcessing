//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_SUM_H
#define CONTINUOUSPROCESSING_SUM_H


#include "win/Window.h"
#include "../execution/result/DoubleResult.h"
#include "inter/AggregateOperator.h"

class Sum: public AggregateOperator{
private:
    double sum = 0.0;
    string attrName;

public:
    Sum(string attrName):attrName(attrName) {}


    ResultPtr result(EventPtr event);

    ResultPtr resultMultEvents(list<EventPtr> *eventList, bool isReset);

    StatefulOperator* clone();

    ~Sum() {}
};

#endif //CONTINUOUSPROCESSING_SUM_H
