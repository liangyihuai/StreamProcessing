#pragma once

#include "../../common/Event.h"
#include "../inter/StatefulOperator.h"
#include "../../expression/Predicate.h"

class Window{
public:
	//evict those events that are expired.
	virtual void refresh() = 0;

	virtual void reevaluate(double& result) = 0;
	virtual void reevaluate(long& result) = 0;
	virtual void reevaluate(bool& result) = 0;

	virtual bool checkAllEvents(Predicate& pre) = 0;

	//add an event to the back side of the window (queue)
	virtual bool push_back(EventPtr e) = 0;

	//return the event in the front of the window
	virtual EventPtr front() = 0;

	//check whether the window is empty or not
	virtual bool empty() = 0;

	//
    virtual int size() = 0;

	//clone the window, including the events insides it.
    virtual Window* clone() = 0;

	virtual void setStatefulOperator(StatefulOperator* op) = 0;

	virtual int getWinLen() = 0;

	virtual int getWinSliding() = 0;
};

