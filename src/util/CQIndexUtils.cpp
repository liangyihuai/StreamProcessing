#include "../stdafx.h"

#include "CQIndexUtils.h"
#include "../expression/GreaterThanFloat.h"
#include "../expression/GreaterEqualThanInt.h"
#include "../expression/EqualString.h"
#include "../expression/LessThanFloat.h"


string CQIndexUtils::sortedFieldNames[] = { "iff", "electromagnetic", "speed", "elevation", "dir", "lon", "lat" };

vector<cqindex::PredicateDecomposition> CQIndexUtils::decomposeCondition(Predicate* con) {
	vector<cqindex::PredicateDecomposition> result;

	vector<Predicate*> *predicateList = con->getChildren();

	for (Predicate* pre : *predicateList) {
		if (EqualString* es = dynamic_cast<EqualString*>(pre)) {
			cqindex::PredicateDecomposition predicateDecomposition;
			predicateDecomposition.fieldName = es->getFieldName();
			predicateDecomposition.strValue = es->getPredicateValue();
			predicateDecomposition.isStringEqual = true;
			result.push_back(predicateDecomposition);
		}else if (GreaterThanFloat* gtf = dynamic_cast<GreaterThanFloat*>(pre)) {
			cqindex::PredicateDecomposition * predicateDecomposition = new cqindex::PredicateDecomposition();
			bool exist = false;
			for (int i = 0; i < result.size(); i++) {
				if (result[i].fieldName == gtf->getFieldName()) {
					exist = true;
					predicateDecomposition = &result[i];
				}
			}
			string fieldName = gtf->getFieldName();
			double value = gtf->getPredicateValue();

			predicateDecomposition->fieldName = fieldName;
			predicateDecomposition->leftValue = value;
			predicateDecomposition->existLeftValue = true;
			if (!exist) 
				result.push_back(*predicateDecomposition);
		}else if (GreaterEqualThanInt* geti = dynamic_cast<GreaterEqualThanInt*>(pre)) {
			cqindex::PredicateDecomposition predicateDecomposition;
			bool exist = false;
			for (int i = 0; i < result.size(); i++) {
				if (result[i].fieldName == geti->getFieldName()) {
					exist = true;
					predicateDecomposition = result[i];
				}
			}
			predicateDecomposition.fieldName = geti->getFieldName();
			predicateDecomposition.leftValue = geti->getPredicateValue();
			predicateDecomposition.existLeftValue = true;
			if (!exist)
				result.push_back(predicateDecomposition);
		}else if (LessThanFloat* ltf = dynamic_cast<LessThanFloat*>(pre)) {
			cqindex::PredicateDecomposition predicateDecomposition;
			bool exist = false;
			for (int i = 0; i < result.size(); i++) {
				if (result[i].fieldName == ltf->getFieldName()) {
					exist = true;
					predicateDecomposition = result[i];
				}
			}
			predicateDecomposition.fieldName = ltf->getFieldName();
			predicateDecomposition.rightValue = ltf->getPredicateValue();
			predicateDecomposition.existRightValue = true;
			if (!exist) {
				result.push_back(predicateDecomposition);
			}
		}
	}

	//debug
	return result;
}

vector<cqindex::PredicateDecomposition> CQIndexUtils::sortFields(vector<cqindex::PredicateDecomposition> pdVec) {
	vector<cqindex::PredicateDecomposition> result;
	for (int i = 0; i < sortedFieldNames->size(); i++) {
		string fieldName = sortedFieldNames[i];
		bool exist = false;
		for (int j = 0; j < pdVec.size(); j++) {
			if (fieldName == pdVec[j].fieldName) {
				result.push_back(pdVec[j]);
				exist = true;
			}
		}
		if (!exist) {
			cqindex::PredicateDecomposition pd;
			pd.isValid = false;
			result.push_back(pd);
		}
	}
	return result;
}

//"iff", "electromagnetic", "speed", "elevation", "dir", "lon", "lat" 
SpatialIndex::Point* CQIndexUtils::transformEventToPoint(EventPtr e) {
	double* coords = new double[7];
	coords[0]= Utils::hashFun(e->getString("iff"));
	coords[1] = Utils::hashFun(e->getString("electromagnetic"));
	coords[2] = e->getFloat("speed");
	coords[3] = e->getFloat("elevation");
	coords[4] = e->getFloat("dir");
	coords[5] = e->getFloat("lon");
	coords[6] = e->getFloat("lat");

	SpatialIndex::Point* p = new SpatialIndex::Point(coords, 7);
	return p;
}