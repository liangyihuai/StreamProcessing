//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_LESSTHANFLOAT_H
#define CONTINUOUSPROCESSING_LESSTHANFLOAT_H


#include "Predicate.h"
#include "../common/Event.h"

class LessThanFloat: public Predicate {
private:
    float value;
    string fieldName;
    string stream;
public:
    LessThanFloat(float value, string fieldName, string streamName="") {
        this->value = value;
        this->fieldName = fieldName;
        this->stream = streamName;
    }

    bool check(EventPtr e) {
        return check("", e);
    }

    bool check(string stream, EventPtr& e){
        if(this->stream != stream) return false;
        return e->getFloat(fieldName) < value;
    }

	string getFieldName() {
		return this->fieldName;
	}

	float getPredicateValue() {
		return this->value;
	}

    vector<Predicate*>* getChildren() { return nullptr; };
    void setChildren(vector<Predicate*>* children) {};
    string getTreeObjectName() { return nullptr; };
    void setTreeObjectName(string objectName) {};
};

#endif //CONTINUOUSPROCESSING_LESSTHANFLOAT_H
