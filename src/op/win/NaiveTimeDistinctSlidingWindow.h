#pragma once

#include <iostream>
#include "NaiveTimeSlidingWindow.h"
#include "set"

class NaiveTimeDistinctSlidingWindow : public NaiveTimeSlidingWindow {
public:
	NaiveTimeDistinctSlidingWindow(int timeLen);
	NaiveTimeDistinctSlidingWindow(int timeLen, string distinctField) :NaiveTimeDistinctSlidingWindow(timeLen);
	~NaiveTimeDistinctSlidingWindow();

	void refresh() override;
	void reevaluate(double& result)override;
	void reevaluate(long& result)override;
	void reevaluate(bool& result)override;
	bool push_back(EventPtr e)override;
	EventPtr front()override;
	bool empty()override;
	int size()override;
	//if anyone meets the predicate, return true, else return false.
	bool checkAllEvents(Predicate& pre) override;

	void setDistinctField(string distinctField);
	int getIndexByDistinctField(EventPtr e);
private:
	string distinctField;
	vector<EventPtr> eventArray;//array

	int event_size = 0;
};
