#include "../stdafx.h"
#include "EventCaptureSpec.h"

EventCapture * EventCaptureSpec::instance() {
	EventCapture * ec = new EventCapture(outputStream);
	ec->setCondition(conditon);
	ec->setInputStreamName(inputStream);
	ec->setOutputStreamName(outputStream);
	return ec;
}

void EventCaptureSpec::setInputStream(string name) {
	this->inputStream = name;
}

void EventCaptureSpec::setOutputStream(string name) {
	this->outputStream = name;
}

void EventCaptureSpec::setCondition(Condition con) {
	this->conditon = con;
}

string EventCaptureSpec::getOutputStream() {
	return this->outputStream;
}