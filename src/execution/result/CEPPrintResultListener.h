#pragma once
#include "ResultListener.h"


class CEPPrintResultListener : public ResultListener {
public:
	void update(const ResultPtr& result) {
		vector<EventPtr> eventVec = result->getResultEventVec();
		for (EventPtr ePtr : eventVec) {
			string streamName = ePtr->getDestination();
			cout << endl << "CEP["<< streamName << "]; time: " << Utils::getTime() << endl;
		}
	}

};