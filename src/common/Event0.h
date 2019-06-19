//
// Created by USER on 12/4/2018.
//
//
//#ifndef CONTINUOUSPROCESSING_EVENT_H
//#define CONTINUOUSPROCESSING_EVENT_H
//#include <iostream>
//#include <set>
//#include <memory>
//#include "Consts.h"
//#include <map>
//
//using namespace std;
////using namespace google;
//
///**
// * A simple attribute
// */
//typedef struct EventAttribute {
//	string name;
//	ValType type;
//	union {
//		int intVal;
//		float floatVal;
//		bool boolVal;
//		string stringVal;
//	};
//} Attribute;
//
////enum EventType {
////	EVENT_MSG, TIME_SLIDING_MSG
////};
//
//class Event {
//public:
//	/*EventType getEventType() { return eventType; }
//	void setEventType(EventType type) { this->eventType = type; }*/
//
//    virtual long getId(){ return 0L;};
//
//	virtual string getDestination() {
//		return this->destination;
//	};
//
//    virtual long long getTime() {return 0LL;};
//
//    virtual int getInt(string attrName){
//		std::cout << "function size is not implemented" << endl;
//        throw runtime_error("");
//    }
//
//    virtual float getFloat(string attrName){
//		std::cout << "function size is not implemented" << endl;
//        throw runtime_error("");
//    }
//
//    virtual string getString(string attrName){
//		std::cout << "function size is not implemented" << endl;
//        throw runtime_error("");
//    }
//
//    virtual void print(ostream& out){
//		std::cout << "function size is not implemented" << endl;
//        throw runtime_error("");
//    }
//
//	virtual string toString() = 0;
//
//	virtual void setDestination(string destination) = 0;
//
//	//add more attributes "extendedEntry" to the copy of current event. The current evnet does not change.
//	virtual Event* extend(const map<string, string>& extendedEntry) = 0;
//
//private:
//    friend std::ostream& operator<< (std::ostream& os, Event& e);
//
//	//event message or control message, event msg in default.
//	//EventType eventType = EVENT_MSG;
//protected:
//	string destination = "";//the destination the event will be passed to.
//};
//
//
//typedef shared_ptr<Event> EventPtr;
//#endif //CONTINUOUSPROCESSING_EVENT_H
