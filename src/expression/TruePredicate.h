//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_TRUEPREDICATE_H
#define CONTINUOUSPROCESSING_TRUEPREDICATE_H

#include "Predicate.h"
#include "../common/Event.h"

class TruePredicate : public Predicate {
public:
    TruePredicate() {
    }

    bool check(EventPtr e) {
        return true;
    }

    vector<Predicate*>* getChildren() { return nullptr; };
    void setChildren(vector<Predicate*>* children) {};
    string getTreeObjectName() { return nullptr; };
    void setTreeObjectName(string objectName) {};
    bool check(string stream, EventPtr& e){return true;};
};

#endif //CONTINUOUSPROCESSING_TRUEPREDICATE_H
