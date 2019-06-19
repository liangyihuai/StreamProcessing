#include "stdafx.h"

#include "CEPProcess.h"
#include "EventCapture.h"
#include "EqualString.h"
#include "ExecuteScheduler.h"
#include "ExistOp.h"
#include "BoolOpPredicate.h"
#include "CEPStoreResultListener.h"


EventPtr getEvent(string iff, float speed) {
	RadarEvent* e = new RadarEvent(Utils::id++, Utils::getTime());
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
	eventCapture->setOutputStream("allyTarget");

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

QueueReader* captureEvents2() {
	EventCapture* eventCapture = new EventCapture;
	//1. set up condition
	EqualString* equalString = new EqualString("unknown", "iff");
	eventCapture->setCondition(Condition(equalString));
	//2. set up output stream name
	eventCapture->setOutputStream("unknownTarget");

	QueueReader *reader1 = new QueueReader();
	DerivedEventStore::registerReader("unknownTarget", reader1);

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

	return reader1;
}

int main() {
	captureEvents();
	QueueReader* reader2 = captureEvents2();

	CEPProcess cep;
	ExistOp existOp1("allyTarget");
	BoolOpPredicate boolOpPre(&existOp1);
	cep.addPredicate(&boolOpPre, "allyTarget");
	cep.addPredicate(&boolOpPre, "unknownTarget");
	cep.addOutputStream("cepTarget1");
	cep.setResultListener(new CEPStoreResultListener());

	ExecuteScheduler::registerCEPProcess(&cep);
	
	QueueReader reader3;
	DerivedEventStore::registerReader("cepTarget1", &reader3);

	QueueReader *reader1 = new QueueReader();
	DerivedEventStore::registerReader("allyTarget", reader1);

	ExecuteScheduler::executeCEPProcess();


	while (!reader1->isEmpty()) {
		EventPtr e = reader1->dequeue();
		cout << e->getId() << ", " << e->getString("iff") << ", " << e->getFloat("speed") << endl;
	}

	cout << endl;
	while (!reader2->isEmpty()) {
		EventPtr e = reader2->dequeue();
		cout << e->getId() << ", " << e->getString("iff") << ", " << e->getFloat("speed") << endl;
	}

	cout << endl;
	while (!reader3.isEmpty()) {
		EventPtr e = reader3.dequeue();
		cout << reader3.getStreamName() << ", " << e->getId() << ", " << e->getTime() << endl;
	}

	system("pause");
	return 0;
}

