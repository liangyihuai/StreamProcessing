#include "../stdafx.h"
#include <thread>
#include <iostream>

class ThreadOfEventFilter {
public:


	void run() {
		std::cout << "i am member1" << std::endl;
	}
	void member2(const char *arg1, unsigned arg2) {
		std::cout << "i am member2 and my first arg is (" << arg1 << ") and second arg is (" << arg2 << ")" << std::endl;
	}

	std::thread runThread() {
		return std::thread(&ThreadOfEventFilter::run, this);
	}
	std::thread member2Thread(const char *arg1, unsigned arg2) {
		return std::thread(&ThreadOfEventFilter::member2, this, arg1, arg2);
	}
};

int main0() {
	ThreadOfEventFilter *w = new ThreadOfEventFilter();
	std::thread tw1 = w->runThread();
	tw1.join();
	w->member2Thread("hello", 100).detach();

	system("pause");
	return 0;
}