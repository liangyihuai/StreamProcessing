#pragma once

#include "../expression/Predicate.h"
#include "../common/Event.h"
#include "../execution/Process.h"
#include <list>

//Index interface
class CQIndex {
public:
	//
	virtual void buildIndex(Predicate*, int64_t regionId) = 0;

	virtual list<Process*> filter(EventPtr) = 0;

};

