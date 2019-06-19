//
// Created by USER on 12/6/2018.
//

#include "stdafx.h"

#include "CQProcess.h"
#include "RadarEvent.h"
#include "EqualString.h"
#include "EventCapture.h"
#include "CQStoreResultListener.h"
#include "ExecuteScheduler.h"
#include "CQSpecParser.h"

using namespace std;

//system wise index
int index = 0;

EventPtr getEvent(string iff, float speed) {
	RadarEvent* e = new RadarEvent(index++, Utils::getTime());
	e->setIff(iff);
	e->setSpeed(speed);
	EventPtr ep1(e);
	return ep1;
}

void captureEvents() {
	EventCapture* eventCapture = new EventCapture;
	//1. set up condition
	EqualString* equalString = new EqualString("ally", "iff");
	eventCapture->setCondition(Condition(equalString));
	//2. set up output stream name
	eventCapture->setOutputStream("allytarget");

	//3. generate events
	EventPtr e1 = getEvent("ally", 700);
	EventPtr e2 = getEvent("", 800);
	EventPtr e3 = getEvent("unknown", 377);
	EventPtr e4 = getEvent("ally", 400);
	EventPtr e5 = getEvent("unknown", 1000);
	EventPtr e6 = getEvent("ally", 600);

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
	DerivedEventStore::registerReader("allytarget", &reader);

	//2. set up CQ spec
	list<string> specStrings = FileReaderUtils::readFile("CQSpec.txt");
	list<CQSpec*> cqSpecs = CQSpecParser::parseAllCQSpec(specStrings);

	
	CQProcess *cqProcess = cqSpecs.front()->instance();
	cqProcess->setResultListener(new CQStoreResultListener());

	//3. set up execution scheduler
	ExecuteScheduler executeScheduler;
	executeScheduler.registerCQProcess(cqProcess);
	executeScheduler.executeCQProcess();

	//4. set up a reader and read the capture events
	QueueReader reader3;
	DerivedEventStore::registerReader("flyingtarget", &reader3);

	cout << "Event Capture result: " << endl;
	while (!reader.isEmpty()) {
		EventPtr e = reader.dequeue();
		cout << "id=" << e->getId() << ", iff=" << e->getString("iff") << ", speed=" << e->getFloat("speed") << endl;
	}

	cout << "\nCQ result: " << endl;
	while (!reader3.isEmpty()) {
		EventPtr e = reader3.dequeue();
		cout << "id=" << e->getId() << ", iff=" << e->getString("iff") << ", speed=" << e->getFloat("speed") << endl;
	}

	system("pause");
	return 0;
};
