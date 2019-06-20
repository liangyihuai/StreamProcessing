//
// Created by USER on 12/6/2018.
//
#include "stdafx.h"

#include "EventCaptureSpecParser.h"

using namespace std;

//system wise index
int index = 0;

EventPtr getEvent(string iff) {
	RadarEvent* e = new RadarEvent(index++, Utils::getTime());
	e->setIff(iff);
	EventPtr ep1(e);
	return ep1;
}

void eventCaptureTest1() {
	list<string> specStrings = FileReaderUtils::readFile("EventCaptureSpec.txt");
	list<EventCaptureSpec*> specList = EventCaptureSpecParser::parseAllEventCaptureSpec(specStrings);

	EventCapture* eventCapture = specList.front()->instance();

	//3. generate events
	EventPtr e1 = getEvent("ally");
	EventPtr e2 = getEvent("");
	EventPtr e3 = getEvent("unknown");
	EventPtr e4 = getEvent("ally");
	EventPtr e5 = getEvent("unknown");
	EventPtr e6 = getEvent("ally");

	EventPtr eventList[] = { e1, e2, e3, e4, e5, e6 };

	//4. input the evnets
	for (EventPtr e : eventList) {
		eventCapture->process(e);
	}

	//5. set up a reader and read the capture events
	QueueReader reader;
	DerivedEventStore::registerReader("allytarget", &reader);
	/*SharedQueueReader reader2;
	DerivedEventStore::registerReader("allyTarget", &reader2);*/

	while (!reader.isEmpty()) {
		EventPtr e = reader.dequeue();
		cout << e->getId() << ", " << e->getString("iff") << endl;
	}


	/*while (!reader2.isEmpty()) {
		EventPtr e = reader2.dequeue();
		cout << e->getId() << ", " << e->getString("iff") << endl;
	}*/
}

int main() {

	eventCaptureTest1();

	system("pause");
	return 0;
}