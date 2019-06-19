//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_GREATEREQUALTHANFLOAT_H
#define CONTINUOUSPROCESSING_GREATEREQUALTHANFLOAT_H
#include <iostream>
#include "Predicate.h"
#include "../common/Event.h"


class GreaterEqualThanInt : public Predicate {
private:
    int value;
    string fieldName;
    string stream;
public:
	GreaterEqualThanInt(int value, string fieldName, string streamName="") {
        this->value = value;
        this->fieldName = fieldName;
        this->stream = streamName;
    }

    bool check(EventPtr e) {
        return check("", e);
    }

    bool check(string stream, EventPtr& e){
        if(this->stream != stream) return false;
        return e->getInt(fieldName) >= value;
    }

	string getFieldName() {
		return this->fieldName;
	}

	int getPredicateValue() {
		return this->value;
	}

    vector<Predicate*>* getChildren() { return nullptr; };
    void setChildren(vector<Predicate*>* children) {};
    string getTreeObjectName() { return nullptr; };
    void setTreeObjectName(string objectName) {};
};
#endif //CONTINUOUSPROCESSING_GREATEREQUALTHANFLOAT_H
