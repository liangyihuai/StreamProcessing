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

#include "CEPSpecParser.h"

using namespace std;

EventPtr getEvent(long id, string iff, float speed) {
	RadarEvent* e = new RadarEvent(id, Utils::getTime());
	e->setIff(iff);
	e->setSpeed(speed);
	EventPtr ep1(e);
	return ep1;
}

void captureEvents(QueueReader * reader) {
	EventCapture* eventCapture = new EventCapture;
	//1. set up condition
	EqualString* equalString = new EqualString("ally", "iff");
	eventCapture->setCondition(Condition(equalString));
	//2. set up output stream name
	eventCapture->setOutputStream("allytarget");

	DerivedEventStore::registerReader("allytarget", reader);
	ExecuteScheduler::registerEventCapture(eventCapture);
}

void captureEvents2(QueueReader * reader) {
	EventCapture* eventCapture = new EventCapture;
	//1. set up condition
	EqualString* equalString = new EqualString("unknown", "iff");
	eventCapture->setCondition(Condition(equalString));
	//2. set up output stream name
	eventCapture->setOutputStream("enemytarget");

	DerivedEventStore::registerReader("enemytarget", reader);

	ExecuteScheduler::registerEventCapture(eventCapture);
}

void cqProcess(QueueReader * reader) {
	//2. set up CQ spec
	string inputStream = "allytarget";
	string outputStream = "flyingtarget";

	CQProcess *cqProcess = new CQProcess();
	EqualString* equalString = new EqualString("ally", "iff");
	GreaterThanFloat* greaterThan = new GreaterThanFloat(500, "speed");
	And* andPre = new And();
	andPre->AND(equalString)->AND(greaterThan);
	cqProcess->setPredicate(andPre);

	cqProcess->setInputStream(inputStream);
	cqProcess->setOutputStreamName(outputStream);
	cqProcess->setResultListener(new CQStoreResultListener());

	ExecuteScheduler::registerCQProcess(cqProcess);
	DerivedEventStore::registerReader(outputStream, reader);
}

void cep(QueueReader * reader1) {
	/*list<string> cepSpecStrings = FileReaderUtils::readFile("cep_spec.txt");
	list<CEPSpec*> cepSpecs = CEPSpecParser::parseAllCEPSpec(cepSpecStrings);
	for (CEPSpec* spec : cepSpecs) {
		CEPProcess* cep = spec->instance();
		cep->setResultListener(new CEPStoreResultListener());
		ExecuteScheduler::registerCEPProcess(cep);
	}
*/
	string inputStreamName = "flyingtarget";
	string inputStreamName2 = "enemytarget";
	string outputStreamName = "ceptarget1";

	CEPProcess* cep = new CEPProcess();
	BoolOpPredicate *boolOpPre = new BoolOpPredicate(new ExistOp(inputStreamName));
	BoolOpPredicate *boolOpPre2 = new BoolOpPredicate(new ExistOp(inputStreamName2));
	cep->addPredicate(boolOpPre, inputStreamName);
	cep->addPredicate(boolOpPre2, inputStreamName2);
	cep->addOutputStream(outputStreamName);
	cep->setResultListener(new CEPStoreResultListener());
	ExecuteScheduler::registerCEPProcess(cep);

	DerivedEventStore::registerReader(outputStreamName, reader1);
}

int main() {
	EventProcess ep;
	ep.setDeduplicationField("id");
	ExecuteScheduler::registerEventProcess(ep);

	QueueReader readerEvent1;
	captureEvents(&readerEvent1);

	QueueReader readerEvent2;
	captureEvents2(&readerEvent2);

	QueueReader readerCQ;
	cqProcess(&readerCQ);

	QueueReader readerCEP1;
	cep(&readerCEP1);

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
	for (EventPtr e : eventList) {
		ExecuteScheduler::run(e);
	}
	ExecuteScheduler::executeCEPProcess();

	cout << "Event Capture result1: " << endl;
	while (!readerEvent1.isEmpty()) {
		EventPtr e = readerEvent1.dequeue();
		cout << "id=" << e->getId() << ", iff=" << e->getString("iff") << ", speed=" << e->getFloat("speed") << endl;
	}

	cout << "\nEvent Capture result2: " << endl;
	while (!readerEvent2.isEmpty()) {
		EventPtr e = readerEvent2.dequeue();
		cout << "id=" << e->getId() << ", iff=" << e->getString("iff") << ", speed=" << e->getFloat("speed") << endl;
	}

	cout << "\nCQ result: " << endl;
	while (!readerCQ.isEmpty()) {
		EventPtr e = readerCQ.dequeue();
		cout << "id=" << e->getId() << ", iff=" << e->getString("iff") << ", speed=" << e->getFloat("speed") << endl;
	}

	cout << "\nCEP result: " << endl;
	while (!readerCEP1.isEmpty()) {
		EventPtr e = readerCEP1.dequeue();
		cout << "id=" << e->getId() << ", iff=" << e->getString("iff") << ", speed=" << e->getFloat("speed") << endl;
	}

	system("pause");
	return 0;
};
