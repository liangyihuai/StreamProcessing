#include "../../stdafx.h"

#include "NaiveTimeDistinctSlidingWindow.h"

NaiveTimeDistinctSlidingWindow::NaiveTimeDistinctSlidingWindow(int timeLen) {
	this->timeWinLen = timeLen;
	for (int i = 0; i < Utils::movingObject_id_total_numble; i++) {
		eventArray.push_back(nullptr);
	}
}

bool NaiveTimeDistinctSlidingWindow::push_back(EventPtr e) {
	if (eventQueue.size() > MAX_WINDOW_SIZE) {
		std::cout << "the window is full. operator name: ExistOP, stream name: ";
		return false;
	}

	if (e == nullptr) {
		throw "the parameter is empty.";
	}

	//get moving object ID
	int objId = e->getInt("objid");
//	cout << endl << "Object ID: " << objId << endl;
	eventArray[objId] = e;

	this->event_size++;
	return true;
}

void NaiveTimeDistinctSlidingWindow::refresh() {
	long long curr = Utils::getTime();
	EventPtr e;

	for (int i = 0; i < eventArray.size(); i++) {
		if (eventArray[i] != nullptr && eventArray[i]->getTime() + timeWinLen < curr) {
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
	long long maxTime = 0;
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
	return event_size <= 0;
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

NaiveTimeDistinctSlidingWindow::~NaiveTimeDistinctSlidingWindow() {
	eventArray.clear();
}