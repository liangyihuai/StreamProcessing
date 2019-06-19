
#include "stdafx.h"

#include <iostream>
#include "CQProcess.h"
#include "RadarEvent.h"
#include "EqualString.h"
#include "EventCapture.h"
#include "CQStoreResultListener.h"
#include "ExecuteScheduler.h"
#include "LessThanOpPreDouble.h"
#include "And.h"
#include "DistanceOp.h"
#include "TruePredicate.h"

using namespace std;

//system wise index
int index = 0;

EventPtr getEvent(string iff, float x, float y) {
	RadarEvent* e = new RadarEvent(index++, Utils::getTime());
	e->setIff(iff);
	e->setLon(x);
	e->setLat(y);
	EventPtr ep1(e);
	return ep1;
}

void captureEvents() {
	EventCapture* eventCapture = new EventCapture;
	//1. set up condition
	EqualString* equalString = new EqualString("ally", "iff");
	eventCapture->setCondition(Condition(equalString));
	//eventCapture->setCondition(new TruePredicate);
	//2. set up output stream name
	eventCapture->setOutputStream("allyTarget");

	//3. generate events
	EventPtr e1 = getEvent("ally", 1, 1);
	EventPtr e2 = getEvent("unknown", 2, 1);
	EventPtr e3 = getEvent("unknown", 3, 1);
	EventPtr e4 = getEvent("ally", 1, 2);
	EventPtr e5 = getEvent("unknown", 3, 3);
	EventPtr e6 = getEvent("ally", 2, 2);

	EventPtr eventList[] = { e1, e2, e3, e4, e5, e6 };

	//4. input the evnets
	for (EventPtr e : eventList) {
		eventCapture->process(e);
	}
}

int main() {
	//1. capture event
	captureEvents();

	//5. set up a reader and read the capture events
	QueueReader reader;
	DerivedEventStore::registerReader("allyTarget", &reader);

	//2. set up CQ spec
	CQProcess cqProcess;
	DistanceOp distanceOp("lon", "lat", 3, 2);
	LessThanOpPreDouble* lessThanOpPre = new LessThanOpPreDouble(&distanceOp, 1.1);
	cqProcess.setPredicate(lessThanOpPre);

	cqProcess.setInputStream("allyTarget");
	cqProcess.setOutputStreamName("flyingTarget");
	cqProcess.setResultListener(new CQStoreResultListener());

	//3. set up execution scheduler
	ExecuteScheduler executeScheduler;
	executeScheduler.registerCQProcess(&cqProcess);
	executeScheduler.executeCQProcess();

	//4. set up a reader and read the capture events
	QueueReader reader3;
	DerivedEventStore::registerReader("flyingTarget", &reader3);

	cout << "Event Capture result: " << endl;
	while (!reader.isEmpty()) {
		EventPtr e = reader.dequeue();
		cout << "id=" << e->getId() << ", iff=" << e->getString("iff") << ", lon = " << e->getFloat("lon") << ", lat = " << e->getFloat("lat") << endl;
	}

	cout << "\nCQ result: " << endl;
	while (!reader3.isEmpty()) {
		EventPtr e = reader3.dequeue();
		cout << "id=" << e->getId() << ", iff=" << e->getString("iff") << ", lon = " << e->getFloat("lon") << ", lat = " << e->getFloat("lat") << endl;
	}

	system("pause");
	return 0;
};
