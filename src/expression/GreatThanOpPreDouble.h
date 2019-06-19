//
// Created by USER on 12/6/2018.
//

#ifndef CONTINUOUSPROCESSING_OPGREATHANDOUBLE_H
#define CONTINUOUSPROCESSING_OPGREATHANDOUBLE_H

#include "OperatorPredicate.h"
#include "../op/inter/Operator.h"
#include "../op/inter/StatefulOperator.h"


class GreatThanOpPreDouble: public OperatorPredicate{
private:
    Operator *op;
    double value;
public:

    GreatThanOpPreDouble(Operator * o, double value){
        this->op = o;
		this->value = value;
    }

    bool check(EventPtr e){
        ResultPtr result = op->result(e);
        return result->getResultBool() > value;
    }

};

#endif //CONTINUOUSPROCESSING_OPGREATHANDOUBLE_H
