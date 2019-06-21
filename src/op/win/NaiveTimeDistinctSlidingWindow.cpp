#include "../../stdafx.h"

#include "NaiveTimeDistinctSlidingWindow.h"

NaiveTimeDistinctSlidingWindow::NaiveTimeDistinctSlidingWindow(int timeLen) {
	this->timeWinLen = timeLen;
	this->distinctField = "objid";
	for (int i = 0; i < Utils::movingObject_id_total_numble; i++) {
		eventArray.push_back(nullptr);
	}
}

//this constructor will call the first constructor
NaiveTimeDistinctSlidingWindow::NaiveTimeDistinctSlidingWindow(int timeLen, string distinctField)
				: NaiveTimeDistinctSlidingWindow(timeLen) {
	this->distinctField = distinctField;
}

bool NaiveTimeDistinctSlidingWindow::push_back(EventPtr e) {
	//get moving object ID
	int index = getIndexByDistinctField(e);
//	cout << endl << "Object ID: " << objId << endl;
	
	if (eventArray[index] == nullptr) {
		eventArray[index] = e;
		this->event_size++;
	}else {
		eventArray[index] = e;
	}

	return true;
}

void NaiveTimeDistinctSlidingWindow::refresh() {
	long long curr = Utils::getTime();
	EventPtr e;

	for (int i = 0; i < eventArray.size(); i++) {
		if (eventArray[i] != nullptr && (eventArray[i]->getTime() + timeWinLen) < curr) {
			eventArray[i] = nullptr;
			this->event_size--;
		}
	}
}

int NaiveTimeDistinctSlidingWindow::size() {
	return this->event_size;
}

void NaiveTimeDistinctSlidingWindow::reevaluate(double& result) {
	refresh();
	list<EventPtr> refreshedEvents;
	for (int i = 0; i < eventArray.size(); i++) {
		if (eventArray[i] != nullptr) {
			refreshedEvents.push_back(eventArray[i]);
		}
	}

	ResultPtr r = op->resultMultEvents(&refreshedEvents, true);
	result = r->getResultDouble();
}

void NaiveTimeDistinctSlidingWindow::reevaluate(long& result) {
	refresh();
	list<EventPtr> refreshedEvents;
	for (int i = 0; i < eventArray.size(); i++) {
		if (eventArray[i] != nullptr) {
			refreshedEvents.push_back(eventArray[i]);
		}
	}

	ResultPtr r = op->resultMultEvents(&refreshedEvents, true);
	result = r->getResultLong();
}

void NaiveTimeDistinctSlidingWindow::reevaluate(bool& result) {
	refresh();
	list<EventPtr> refreshedEvents;
	for (int i = 0; i < eventArray.size(); i++) {
		if (eventArray[i] != nullptr) {
			refreshedEvents.push_back(eventArray[i]);
		}
	}

	ResultPtr r = op->resultMultEvents(&refreshedEvents, true);
	result = r->getResultBool();
}

EventPtr NaiveTimeDistinctSlidingWindow::front() {
	long long maxTime = -1;
	int maxIndex = -1;
	for (int i = 0; i < eventArray.size(); i++) {
		EventPtr e = eventArray[i];
		if (e != nullptr) {
			if (e->getTime() > maxTime) {
				maxTime = e->getTime();
				maxIndex = i;
			}
		}
	}
	if (maxIndex < 0) throw "the event queue is empty.";
	return eventArray[maxIndex];
}

bool NaiveTimeDistinctSlidingWindow::empty() {
	//debug----------start -------
	int size = 0;
	for (EventPtr e : eventArray) {
		if (e != nullptr) size++;
	}
	if (size != this->event_size) {
		cout << "wrong calculation of this->event_size" << endl;
		throw "";
	}
	if (this->event_size < 0) {
		cout << "this->event_size < 0" << endl;
		throw "";
	}
	//------------------end----------

	return event_size == 0;
}

bool NaiveTimeDistinctSlidingWindow::checkAllEvents(Predicate& pre) {
	refresh();
	for (EventPtr e : eventArray) {
		if (e != nullptr) {
			if (pre.check(e)) return true;
		}
	}
	return false;
}

void NaiveTimeDistinctSlidingWindow::setDistinctField(string distinctField) {
	this->distinctField = distinctField;
}

int NaiveTimeDistinctSlidingWindow::getIndexByDistinctField(EventPtr e) {
	if (this->distinctField.length() == 0) {
		cout << "distinct field is empty." << endl;
		throw "";
	}
	return e->getInt(this->distinctField);
}

NaiveTimeDistinctSlidingWindow::~NaiveTimeDistinctSlidingWindow() {
	eventArray.clear();
}