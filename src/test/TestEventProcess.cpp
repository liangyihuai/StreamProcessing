#include "stdafx.h"
#include "EventProcess.h"
#include "EventCapture.h"
#include "EqualString.h"


//system wise index
int index = 0;

EventPtr getEvent(int id, string iff, float speed) {
	RadarEvent* e = new RadarEvent(id, Utils::getTime());
	e->setIff(iff);
	e->setSpeed(speed);
	EventPtr ep1(e);
	return ep1;
}

int main() {
	EventProcess ep(2);
	ep.addUnusualName("iff");
	ep.addUnusualName("speed");
	ep.setDeduplicationField("id");

	//3. generate events
	EventPtr e1 = getEvent(index++, "ally", 700);
	EventPtr e2 = getEvent(index, "", 800);
	EventPtr e3 = getEvent(index++, "unknown", 377);
	EventPtr e4 = getEvent(index, "ally", 400);
	EventPtr e5 = getEvent(index, "unknown", 1000);
	EventPtr e6 = getEvent(index++, "ally", 600);
	EventPtr e7 = getEvent(index++, "ally", -1);
	EventPtr e8 = getEvent(index++, "ally", 600);
	EventPtr e9 = getEvent(index++, "ally", 6);
	EventPtr e10 = getEvent(index++, "ally", -1);
	EventPtr e11 = getEvent(index++, "ally", 600);

	EventPtr eventList[] = { e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11 };
	for (EventPtr ev : eventList) {
		cout << "input id=" << ev->getId() << ", iff=" << ev->getString("iff") << ", speed=" << ev->getFloat("speed") << endl;
	}
	cout << endl;

	for (EventPtr ev : eventList) {
		if (ep.filter(ev)) {
			cout << "output id=" << ev->getId() << ", iff=" << ev->getString("iff") << ", speed=" << ev->getFloat("speed") << endl;
		}
	}
	

	system("pause");
	return 0;
}