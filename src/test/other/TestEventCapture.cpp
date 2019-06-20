//
// Created by USER on 12/6/2018.
//
#include "stdafx.h"

#include <iostream>
#include "EventCapture.h"
#include "EqualString.h"
#include "RadarEvent.h"
#include "Utils.h"

using namespace std;

//system wise index
int index = 0;

EventPtr getEvent(string iff){
    RadarEvent* e = new RadarEvent(index++, Utils::getTime());
    e->setIff(iff);
    EventPtr ep1(e);
    return ep1;
}

void eventCaptureTest1(){
    EventCapture* eventCapture = new EventCapture;
    //1. set up condition
    EqualString* equalString = new EqualString("ally", "iff");
    eventCapture->setCondition(Condition(equalString));
    //2. set up output stream name
    eventCapture->setOutputStream("allyTarget");

    //3. generate events
    EventPtr e1 = getEvent("ally");
    EventPtr e2 = getEvent("");
    EventPtr e3 = getEvent("unknown");
    EventPtr e4 = getEvent("ally");
    EventPtr e5 = getEvent("unknown");
    EventPtr e6 = getEvent("ally");

    EventPtr eventList[] = {e1, e2, e3, e4, e5, e6};

    //4. input the evnets
    for(EventPtr e: eventList){
        eventCapture->process(e);
    }

    //5. set up a reader and read the capture events
    QueueReader reader;
    DerivedEventStore::registerReader("allyTarget", &reader);
	/*SharedQueueReader reader2;
	DerivedEventStore::registerReader("allyTarget", &reader2);*/

    while(!reader.isEmpty()){
        EventPtr e = reader.dequeue();
        cout << e->getId() << ", " << e->getString("iff") << endl;
    }

	
	/*while (!reader2.isEmpty()) {
		EventPtr e = reader2.dequeue();
		cout << e->getId() << ", " << e->getString("iff") << endl;
	}*/
}

int main(){

    eventCaptureTest1();

	system("pause");
    return 0;
}