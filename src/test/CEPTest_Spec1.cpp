//
// Created by USER on 12/6/2018.
//

#include "stdafx.h"

#include <iostream>
#include "CQProcess.h"
#include "RadarEvent.h"
#include "EqualString.h"
#include "EventCapture.h"
#include "CQStoreResultListener.h"
#include "ExecuteScheduler.h"
#include "GreaterThanFloat.h"
#include "And.h"
#include "ExistOp.h"
#include "BoolOpPredicate.h"
#include "CEPStoreResultListener.h"

using namespace std;

EventPtr getEvent(long id, string iff, float speed) {
	RadarEvent* e = new RadarEvent(id, Utils::getTime());
	e->setIff(iff);
	e->setSpeed(speed);
	EventPtr ep1(e);
	return ep1;
}

int main() {
	list<string> ecSpecStrings = FileReaderUtils::readFile("event_capture_spec.txt");
	list<EventCaptureSpec*> eventcaptureSpecs = EventCaptureSpecParser::parseAllEventCaptureSpec(ecSpecStrings);
	for (EventCaptureSpec* spec : eventcaptureSpecs) {
		EventCapture* ec = spec->instance();
		ExecuteScheduler::registerEventCapture(ec);
	}
	QueueReader ecReader1;
	DerivedEventStore::registerReader("allytarget", &ecReader1);
	QueueReader ecReader2;
	DerivedEventStore::registerReader("enemytarget", &ecReader2);

	list<string> cqSpecStrings = FileReaderUtils::readFile("cq_spec.txt");
	list<CQSpec*> cqSpecs = CQSpecParser::parseAllCQSpec(cqSpecStrings);
	for (CQSpec* spec : cqSpecs) {
		CQProcess * cq = spec->instance();
		ExecuteScheduler::registerCQProcess(cq);
	}
	QueueReader cqReader1;
	DerivedEventStore::registerReader("flyingtarget", &cqReader1);

	list<string> cepSpecStrings = FileReaderUtils::readFile("cep_spec.txt");
	list<CEPSpec*> cepSpecs = CEPSpecParser::parseAllCEPSpec(cepSpecStrings);
	for (CEPSpec* spec : cepSpecs) {
		CEPProcess* cep = spec->instance();
		cep->setResultListener(new CEPStoreResultListener());
		ExecuteScheduler::registerCEPProcess(cep);
	}
	QueueReader cepReader1;
	DerivedEventStore::registerReader("ceptarget1", &cepReader1);

	//3. generate events
	EventPtr e1 = getEvent(0, "ally", 700);
	EventPtr e2 = getEvent(1, "", 800);
	EventPtr e3 = getEvent(2, "unknown", 377);
	EventPtr e4 = getEvent(2, "unknown", 377);
	EventPtr e5 = getEvent(2, "ally", 400);
	EventPtr e6 = getEvent(3, "ally", 400);
	EventPtr e7 = getEvent(3, "unknown", 1000);
	EventPtr e8 = getEvent(4, "ally", 600);

	EventPtr eventList[] = { e1, e2, e3, e4, e5, e6, e7, e8 };
	
	cout << "Input data: " << endl;
	for (EventPtr e : eventList) {
		cout << "id=" << e->getId() << ", iff=" << e->getString("iff") << ", speed=" << e->getFloat("speed") << endl;
		ExecuteScheduler::run(e);
	}
	ExecuteScheduler::executeCEPProcess();

	cout << "\nEvent Capture: allytarget: " << endl;
	while (!ecReader1.isEmpty()) {
		EventPtr e = ecReader1.dequeue();
		cout << "id=" << e->getId() << ", iff=" << e->getString("iff") << ", speed=" << e->getFloat("speed") << endl;
	}

	cout << "\nEvent Capture: enemytarget: " << endl;
	while (!ecReader2.isEmpty()) {
		EventPtr e = ecReader2.dequeue();
		cout << "id=" << e->getId() << ", iff=" << e->getString("iff") << ", speed=" << e->getFloat("speed") << endl;
	}
	
	cout << "\nCQ result: flyingtarget: " << endl;
	while (!cqReader1.isEmpty()) {
		EventPtr e = cqReader1.dequeue();
		cout << "id=" << e->getId() << ", iff=" << e->getString("iff") << ", speed=" << e->getFloat("speed") << endl;
	}

	cout << "\nCEP result: " << endl;
	while (!cepReader1.isEmpty()) {
		EventPtr e = cepReader1.dequeue();
		cout << "time: "<<Utils::getTime() << ", complexEvent: cepTarget1" << endl;
	}

	system("pause");
	return 0;
};
