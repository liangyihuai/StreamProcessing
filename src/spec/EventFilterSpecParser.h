#pragma once

#include "../stdafx.h"

#include "../expression/Condition.h"
#include "EventFilterSpec.h"
#include "EventFilterSpec.h"
#include "../execution/EventCapture.h"
#include "CEPSpec.h"
#include "../op/OperatorRegister.h"
#include "../expression/BoolOpPredicate.h"
#include "../expression/GreatThanOpPreDouble.h"
#include "../expression/LessThanOpPreDouble.h"
#include "../expression/Predicate.h"

/*
//Sample: 
	If not duplicate(id) & not unusual(iff) & not unusual(speed)
	From rawData
	Then targetData
*/
class EventFilterParser {
public:
	//static list<EventFilterSpec*> parseAllEventFilterSpec(const list<string> allCQSpecs);

	static EventFilterSpec* parseOneEventFilterSpec(list<string> specStr);
};

