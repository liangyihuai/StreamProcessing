#pragma once

#include "inter/AggregateOperator.h"

class Count : public AggregateOperator {
private:
    long count = 0;
   
public:
    Count() {}
	~Count() {};

    ResultPtr result(EventPtr event) override;
    ResultPtr resultMultEvents(list<EventPtr> *eventList, bool isReset)override;
};

