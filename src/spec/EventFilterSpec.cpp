#include "../stdafx.h"
#include "EventFilterSpec.h"
#include "../execution/EventProcess.h"

EventProcess * EventFilterSpec::instance() {
	EventProcess* eventFilter = new EventProcess();
	for (string field : notUnusualFieldList) {
		eventFilter->addUnusualName(field);
	}
	eventFilter->setDeduplicationField(notDuplicateField);
	eventFilter->setInputStream(inputStream);
	eventFilter->setOutputStreamName(outputStream);
	return eventFilter;
}

void EventFilterSpec::setInputStream(string name) {
	this->inputStream = name;
}

void EventFilterSpec::setOutputStream(string name) {
	this->outputStream = name;
}

void EventFilterSpec::setNotDuplicateField(string field) {
	this->notDuplicateField = field;
}

void EventFilterSpec::addNotUnusualField(string field) {
	this->notUnusualFieldList.push_back(field);
}