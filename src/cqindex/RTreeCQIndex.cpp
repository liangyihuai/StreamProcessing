#include "../stdafx.h"

#include "RTreeCQIndex.h"
#include "ProcessRegisterForCQIndex.h"

RTreeCQIndex::RTreeCQIndex(int dimension) {
	this->dimension = dimension;

	initialize();
}

void RTreeCQIndex::initialize() {
	Tools::PropertySet* ps = GetDefaults();
	Tools::Variant var;

	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = RT_RTree;
	ps->setProperty("IndexType", var);

	var.m_varType = Tools::VT_ULONG;
	var.m_val.ullVal = RT_Memory;
	ps->setProperty("IndexStorageType", var);

	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = dimension;
	ps->setProperty("Dimension", var);

	if (dimension <= 0)
		throw "dimension <= 0";

	Index * idx = new Index(*ps);
	delete ps;

	if (!idx->index().isIndexValid())
		throw "Failed to create valid index";
	else
		cout << "created index" << endl;

	this->idx = idx;
}

void RTreeCQIndex::buildIndex(Predicate* condition, int64_t regionId) {
	vector<cqindex::PredicateDecomposition> pdVec = CQIndexUtils::decomposeCondition(condition);
	double* lowCoords = new double[dimension];
	double* highCoords = new double[dimension];
	for (int i = 0; i < pdVec.size(); i++) {
		cqindex::PredicateDecomposition pd = pdVec[i];
		double lowValue = MIN_BOUNDARY;
		double hightValue = SIZE_MAX;
		if (pd.isValid == true) {
			if (pd.isStringEqual) {
				hightValue = lowValue = Utils::hashFun(pd.strValue);
			}else {
				if (pd.existLeftValue) {
					lowValue = pd.leftValue;
				}
				if (pd.existRightValue) {
					hightValue = pd.rightValue;
				}
			}
		}
		lowCoords[i] = lowValue;
		highCoords[i] = hightValue;
	}
	Point lowPoint(lowCoords, dimension);
	Point highPoint(highCoords, dimension);

	addRegion(lowPoint, highPoint, regionId);//add the condition to CQ index.

	delete[]lowCoords;
	delete[] highCoords;
}


void RTreeCQIndex::addRegion(SpatialIndex::Point low, SpatialIndex::Point high, int64_t id) {
	uint8_t * pData = 0;
	uint32_t nDataLength = 0;

	SpatialIndex::IShape* shape = new SpatialIndex::Region(low, high);

	idx->index().insertData(nDataLength, pData, *shape, id);

	cout << "Rectangle " << id << " inserted into index." << endl;
	delete shape;
}


list<Process*> RTreeCQIndex::filter(EventPtr e) {
	Point* point = CQIndexUtils::transformEventToPoint(e);

	ObjVisitor* visitor = new ObjVisitor;
	IShape* r = point;
	idx->index().intersectsWithQuery(*r, *visitor);

	int64_t nResultCount = visitor->GetResultCount();
	vector<IData*>& results = visitor->GetResults();

	vector<int64_t> *resultForId = new vector<int64_t>();
	for (int64_t i = 0; i < nResultCount; i++) {
		resultForId->push_back(results[i]->getIdentifier());
	}
	delete visitor;

	return ProcessRegisterForCQIndex::getProcess(*resultForId);
}


RTreeCQIndex::~RTreeCQIndex() {
	delete idx;
}

