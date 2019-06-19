#pragma once

#include "Spec.h"
#include <vector>
#include "../execution/CEPProcess.h"
#include "../common/SinkType.h"


class CEPSpec : public Spec {
private:
	vector<string> inputStreams;
	string outputStreamName;

	vector<ExistOp*> existOpPredicateList;
	vector<Predicate*> predicates;

	SinkType sinkType;

	int winLen = -1;
	int winSliding = -1;

public:
	CEPSpec();

	CEPProcess * instance();

	void setOutputStreamName(string name);

	void addExistOpPredicate(ExistOp * pre, string stream);

	string getOutputStreamName();

	void addPredicate(Predicate* pre);

	void setPredicates(vector<Predicate*> preList);

	void setInputStreams(vector<string> inputStreams);

	void setWinLen(int winLen);

	void setWinSliding(int sliding);
};