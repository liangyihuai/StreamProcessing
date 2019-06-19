#pragma once

#include "../execution/Process.h"

//interface of spec
//a spec stands for the processing specifications or rules input by uses,
//telling the system what to do.
class Spec {
public:
	//create a Process instance from the current spec.
	virtual Process * instance() = 0;
};