//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_PREDICATE_H
#define CONTINUOUSPROCESSING_PREDICATE_H

#include <iostream>
#include <vector>
#include "../common/Event.h"

using namespace std;

class Predicate {
public:
	string streamName;

    virtual vector<Predicate*>* getChildren() = 0;

    virtual void setChildren(vector<Predicate*>* children) = 0;

    virtual string getTreeObjectName() = 0;

    virtual void setTreeObjectName(string objectName) = 0;

    virtual bool check(EventPtr e) = 0;

    virtual bool check(string stream, EventPtr& e) = 0;
};


#endif //CONTINUOUSPROCESSING_PREDICATE_H
