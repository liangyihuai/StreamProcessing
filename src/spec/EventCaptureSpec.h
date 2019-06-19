#pragma once

#include "Spec.h"
#include "../expression/Condition.h"
#include "../execution/EventCapture.h"

class EventCaptureSpec : public Spec {
private:
	string inputStream;
	string outputStream;
	Condition conditon;
public:
	EventCapture * instance();

	void setInputStream(string name);

	void setOutputStream(string name);

	void setCondition(Condition con);

	string getOutputStream();
};