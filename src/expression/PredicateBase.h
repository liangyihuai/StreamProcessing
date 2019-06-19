//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_PREDICATEBASE_H
#define CONTINUOUSPROCESSING_PREDICATEBASE_H
#include "predicate.h"
#include <string>
class PredicateBase : public Predicate{
private:
    string treeObjectName;
    vector<Predicate*> *children;
public:
    PredicateBase() {
        this->children = new vector<Predicate*>();
    }

    string getTreeObjectName() {
        return treeObjectName;
    }

    void setTreeObjectName(string name) {
        this->treeObjectName = name;
    }

    vector<Predicate*>* getChildren() {
        return children;
    }

    void addChild(Predicate* expression) {
        children->push_back(expression);
    }

    void setChildren(vector<Predicate*>* children) {
        this->children = children;
    }

    ~PredicateBase() {
        delete children;
    }
};
#endif //CONTINUOUSPROCESSING_PREDICATEBASE_H
