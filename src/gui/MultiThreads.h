#pragma once

#include <thread>
#include <iostream>
#include <set>

using namespace std;

//perform CEP regularly.
//class ThreadOfTimerToPerformCEP {
//public:
//	void run();
//
//	std::thread runThread();
//};


//the thread to run the backend of stream processing
class ThreadOfEventFilter {
private:
	bool isStop = false;
	bool isWithGUI = true;
public:
	ThreadOfEventFilter(bool isWithGUI = true);
	void run();
	std::thread runThread();
	void stop();
};



//the thread to run the backend of stream processing
class ThreadOfProcessUnit {
public:
	void run();

	std::thread runThread();
};


class ThreadOfInputDataForSampleData1 {
public:
	void run();

	std::thread runThread();
};

