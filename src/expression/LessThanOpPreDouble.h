#pragma once


#include "OperatorPredicate.h"
#include "../op/inter/Operator.h"

class LessThanOpPreDouble: public OperatorPredicate{
private:
    Operator * op;
    double value;
public:

    LessThanOpPreDouble(Operator * o, double value){
        this->op = o;
		this->value = value;
    }

    bool check(EventPtr e){
        ResultPtr result = op->result(e);
        return result->getResultDouble() < value;
    }
};

