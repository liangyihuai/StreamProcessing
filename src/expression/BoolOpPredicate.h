#pragma once

#include "OperatorPredicate.h"
#include "../op/inter/Operator.h"

class BoolOpPredicate: public OperatorPredicate{
private:
	Operator * op;
public:

	BoolOpPredicate(Operator * o) {
		this->op = o;
	}

	bool check(EventPtr e) {
		ResultPtr result = op->result(e);
		return result->getResultBool();
	}
};