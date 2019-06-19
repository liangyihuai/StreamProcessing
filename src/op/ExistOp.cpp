#include "../stdafx.h"
#include "ExistOp.h"
#include "../execution/result/BoolResult.h"

ExistOp::ExistOp(string _streamName) {
	this->streamName = _streamName;
}


ResultPtr ExistOp::result(EventPtr event) {
	cout << "This function is not implemented. You should not call it." << endl;
	throw runtime_error("");
}

ResultPtr ExistOp::resultMultEvents(list<EventPtr> *eventList, bool isReset) {
	if (eventList == nullptr || eventList->size() == 0) {
		return ResultPtr(new BoolResult(false));
	}else {
		return ResultPtr(new BoolResult(true));
	}
}




