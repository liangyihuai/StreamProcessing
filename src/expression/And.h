//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_AND_H
#define CONTINUOUSPROCESSING_AND_H

#include "Predicate.h"
#include "PredicateBase.h"

class And: public PredicateBase {

public:
    And() {}

    And(Predicate* inner) {
        addChild(inner);
    }

    And * AND(Predicate * pre) {
        addChild(pre);
        return this;
    }

    bool check(EventPtr e) {
        for (Predicate * pre : *getChildren()) {
            if (!pre->check(e))
				return false;
        }
        return true;
    }

    bool check(string stream, EventPtr& e){
		std::cout << "function \"check\" is not implemented";
        throw runtime_error("");
    }
};

#endif //CONTINUOUSPROCESSING_AND_H
