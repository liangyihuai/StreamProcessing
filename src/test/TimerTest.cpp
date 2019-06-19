#include "../stdafx.h"
#include <chrono>
#include <iostream>
#include <future>

void timer() {
	std::cout << "Start\n";
	for (int i = 0; i < 10; ++i) {
		std::cout << (10 - i) << '\n';
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	std::cout << "DONE\n";
}


int main() {
	auto future = std::async(timer);
	std::cout << "test\n";
}