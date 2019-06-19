//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_EQUALSTRING_H
#define CONTINUOUSPROCESSING_EQUALSTRING_H

#include "Predicate.h"

class EqualString : public Predicate {
private:
    string value;
    string fieldName;
    string stream;
public:

    EqualString(const string value, const string fieldName, const string stream="") : value(value),
                                fieldName(fieldName), stream(stream) {}

    bool check(EventPtr e) {
        return check("", e);
    }

    bool check(string stream, EventPtr& e){
        if(this->stream != stream) return false;
        return e->getString(fieldName) == value;
    }

	string getFieldName() {
		return this->fieldName;
	}

	string getPredicateValue() {
		return this->value;
	}

    vector<Predicate*>* getChildren() { return nullptr; };
    void setChildren(vector<Predicate*>* children) {};
    string getTreeObjectName() { return nullptr; };
    void setTreeObjectName(string objectName) {};
};
#endif //CONTINUOUSPROCESSING_EQUALSTRING_H
