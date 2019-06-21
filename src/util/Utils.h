//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_UTILS_H
#define CONTINUOUSPROCESSING_UTILS_H


#pragma warning(disable:4996)


#include <time.h>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <cstring>
#include <ctime>

#include <mutex>

#define random(a, b) (rand() % (b-a) + a)
#define randomInt(a, b) (rand() % b + a)



using namespace std;
class Utils {
public:

	//system wise id
	static unsigned long id;

    //get the current time, millisecond.
    static long long getTime();

	static int movingObject_id_count;
	static int movingObject_id_total_numble;//the maximum object id to be generated.

    //static string getTimeStr();

	static std::hash<string> hashFun;

    static double randomFloat(int min, int max);

	static double randMToN(double M, double N);

	static int randOneOrNegativeOne();

    static string getRandomGroupName(int startRange = 0, int endRange = 100);

    static void lTrim(char * str);

    static void rTrim(char * str);

    static void trim(char * str);

    static string lTrim(const string& str);

    static string rTrim(const string& str);

    static string trim(const string& str);

    static string toLower(const string& s);

    static string toUpper(const string& s);

    static std::vector<std::string> split(const std::string &str, const std::string &delim);

	/*
	For example, str = "THEN EnemyDistance, distance(127.12, 35.33), hello world, speed(a, b)"
	delim=",";
	skipStart="("
	skipEnd=")"
	The function result is:
	THEN EnemyDistance
	 distance(127.12, 35.33)
	 hello world
	 speed(a, b)
	*/
	static std::vector<std::string> split(const std::string& str, const std::string& delim,
		const string skipStart,
		const string skipEnd);

    static void deleteAllMark(string &s, const string &mark);

	static vector<EventPtr> tranform(string str);
};

#endif //CONTINUOUSPROCESSING_UTILS_H
