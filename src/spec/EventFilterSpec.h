#pragma once

#include "Spec.h"
#include <list>
#include "../execution/EventProcess.h"

class EventFilterSpec {
private:
	string inputStream;
	string outputStream;
	string notDuplicateField;
	list<string> notUnusualFieldList;

public:
	EventProcess * instance();

	void setInputStream(string name);

	void setOutputStream(string name);

	void setNotDuplicateField(string field);

	void addNotUnusualField(string field);
};