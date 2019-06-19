//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_CONDITION_H
#define CONTINUOUSPROCESSING_CONDITION_H

#include <map>
#include <iostream>
#include "predicate.h"
#include "../common/Event.h"
#include <vector>

using namespace std;

class Condition {
private:
    //store attribute name and associated query expression.
    Predicate * predicate;

    //the event to check the query condition.
    EventPtr currentEvent;

public:
    Condition() {}

    Condition(Predicate * pre) :predicate(pre) {}

    void setPredicate(Predicate * predicate) {
		if (!predicate) {
			std::cout << "the expression is null";
			throw "the expression is null";
		}

        this->predicate = predicate;
    }

    void setCurrEvent(EventPtr currentEvent) {
        this->currentEvent = currentEvent;
    }

    //result the result of this query condition, true or false.
    bool check() {
        return predicate->check(currentEvent);
    }

    bool check(EventPtr event) {
        setCurrEvent(event);
        return check();
    }

	vector<Predicate*> getAllPredicate() {
		return *(predicate->getChildren());
	}
};


#endif //CONTINUOUSPROCESSING_CONDITION_H
