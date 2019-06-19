#pragma once

#include "Operator.h"
#include <list>
#include "../win/Window.h"


class StatefulOperator :public Operator{
public:
    virtual ResultPtr resultMultEvents(list<EventPtr> *eventList, bool isReset) = 0;

   // virtual void setWindow(Window<T> * win) = 0;
};