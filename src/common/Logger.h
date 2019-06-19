#pragma once

#include <iostream>

using namespace std;

enum LogType{ERROR, };

class Logger {
	friend ostream& operator<<(ostream&, const Logger&);
public:
	Logger() {}

	static Logger& instance() {
		return *Logger::logger;
	}

private:
	static Logger* logger;

}; 

Logger* Logger::logger = new Logger();

ostream& operator<<(ostream& out, const Logger& log){
	out << "";
	return out;
}

ostream& LOG(LogType t) {
	return ;
}