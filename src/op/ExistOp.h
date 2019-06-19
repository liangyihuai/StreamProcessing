#ifndef CONTINUOUSPROCESSING_EXISTOP_H
#define CONTINUOUSPROCESSING_EXISTOP_H

#include "inter/StatefulOperator.h"
#include "../util/Utils.h"
#include <list>
#include "../op/win/Window.h"
#include "../execution/result/BoolResult.h"
#include "../op/win/NaiveTimeSlidingWindow.h"

class ExistOp: public StatefulOperator{

public:
	ExistOp(string _streamName);

	ResultPtr resultMultEvents(list<EventPtr> *eventList, bool isReset)override;

	//this is overrided function. to get rusults. In this class, the parameter is nullptr.
	ResultPtr result(EventPtr event) override;
	
	
private:
	string streamName;
};

#endif //CONTINUOUSPROCESSING_EXISTOP_H

