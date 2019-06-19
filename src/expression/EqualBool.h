#pragma once

#include "OperatorPredicate.h"
#include "../op/inter/Operator.h"
#include "../op/inter/StatefulOperator.h"


class EqualBool : public OperatorPredicate {
private:
	Operator* op;
	bool value;

public:

	EqualBool(Operator* op, bool value) {
		this->op = op;
		this->value = value;
	}

	bool check(EventPtr e) {
		ResultPtr result = op->result(e);
		return result->getResultBool() == value;
	}

	~EqualBool() {
		delete op;
		op = nullptr;
	}
};
