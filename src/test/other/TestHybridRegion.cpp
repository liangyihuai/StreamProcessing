//#include <iostream>
//#include <spatialindex/capi/sidx_api.h>
//#include <spatialindex/capi/sidx_impl.h>
//#include <spatialindex/capi/sidx_config.h>
//#include <cassert>
//
//using namespace std;
//using namespace SpatialIndex;
//
//Index * createIndex() {
//	Tools::PropertySet* ps = GetDefaults();
//	Tools::Variant var;
//
//	var.m_varType = Tools::VT_ULONG;
//	var.m_val.ulVal = RT_RTree;
//	ps->setProperty("IndexType", var);
//
//	var.m_varType = Tools::VT_ULONG;
//	var.m_val.ullVal = RT_Memory;
//	ps->setProperty("IndexStorageType", var);
//
//	var.m_varType = Tools::VT_ULONG;
//	var.m_val.ulVal = 4;
//	ps->setProperty("Dimension", var);
//
//	Index * idx = new Index(*ps);
//	delete ps;
//
//	if (!idx->index().isIndexValid())
//		throw "Failed to create valid index";
//	else
//		cout << "created index" << endl;
//	return idx;
//}
//
//void addRegion(Index* idx, double x1, double y1, double x2, double y2,
//	double x3, double y3, double x4, double y4, int64_t id) {
//	double coords1[] = { x1, x2, x3, x4 };
//	double coords2[] = { y1, y2, y3, y4 };
//
//	uint8_t * pData = 0;
//	uint32_t nDataLength = 0;
//
//	IShape* shape = new Region(Point(coords1, 4), Point(coords2, 4));
//
//	idx->index().insertData(nDataLength, pData, *shape, id);
//
//	cout << "Rectangle " << id << " inserted into index." << endl;
//	delete shape;
//}
//
//vector<IData*>* getIntersectedRegion(Index* idx, Point * p) {
//
//	ObjVisitor* visitor = new ObjVisitor;
//
//	IShape* r = p;
//
//	idx->index().intersectsWithQuery(*r, *visitor);
//
//	int64_t nResultCount;
//	nResultCount = visitor->GetResultCount();
//
//	vector<IData*>& results = visitor->GetResults();
//	vector<IData*> * resultsCopy = new vector<IData*>();
//
//	for (int64_t i = 0; i < nResultCount; i++) {
//		resultsCopy->push_back(dynamic_cast<IData*>(results[i]->clone()));
//	}
//
//	delete visitor;
//	cout << "found " << nResultCount << " results. " << endl;
//
//	return resultsCopy;
//}
//
//
//void testIntersectionRegions() {
//	Index * idx = createIndex();
//
//	hash<string> ha;
//	//iff, electromagnetic, speed, elevation; 
//	size_t allyHash = ha("ally");
//	size_t enemyHash = ha("enemy");
//
//	const int MIN = -999999;
//
//	addRegion(idx, allyHash, allyHash, ha("a"), ha("a"), 500, SIZE_MAX, MIN, SIZE_MAX, 1);
//	addRegion(idx, enemyHash, enemyHash, MIN, SIZE_MAX, MIN, 400, MIN, SIZE_MAX, 2);
//	addRegion(idx, MIN, SIZE_MAX, ha("a"), ha("a"), MIN, SIZE_MAX, 20, SIZE_MAX, 3);
//	addRegion(idx, enemyHash, enemyHash, ha("b"), ha("b"), 200, SIZE_MAX, 10, SIZE_MAX, 4);
//
//
//	double coords[] = { allyHash, ha("a"), 700, 40 };
//	vector<IData*> * results = getIntersectedRegion(idx, &Point(coords, 4));
//
//	assert(results->size() == 2);
//	assert((*results)[0]->getIdentifier() == 1);
//	assert((*results)[1]->getIdentifier() == 3);
//
//	double coords2[] = { allyHash, ha("a"), 200, 40 };
//	results = getIntersectedRegion(idx, &Point(coords2, 4));
//	assert(results->size() == 1);
//	assert((*results)[0]->getIdentifier() == 3);
//
//	double coords3[] = { enemyHash, ha("a"), 200, 40 };
//	results = getIntersectedRegion(idx, &Point(coords3, 4));
//	assert(results->size() == 2);
//	assert((*results)[0]->getIdentifier() == 2);
//	assert((*results)[1]->getIdentifier() == 3);
//
//	double coords4[] = { enemyHash, ha("a"), 500, 10 };
//	results = getIntersectedRegion(idx, &Point(coords4, 4));
//	assert(results->size() == 0);
//}
//
//int main() {
//	testIntersectionRegions();
//
//	system("pause");
//}
//
//
//
//
//
