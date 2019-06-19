#pragma once


#include "Result.h"
#include "../../util/Utils.h"
#include "../../common/HashEvent.h"

class SingleEventResult : public Result {
private:
	EventPtr event;
public:
	EventPtr getResultEvent() override {
		return event;
	}

	void setEvent(const EventPtr& e) {
		this->event = e;
	}
};