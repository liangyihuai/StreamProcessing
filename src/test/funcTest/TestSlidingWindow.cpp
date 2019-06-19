#include <iostream>

#include "../../util/EventGenerator.h"
#include "../../op/win/Window.h"
#include "../../op/win/NaiveTimeSlidingWindow.h"
#include "../../op/Count.h"
#include "../../op/Average.h"
using namespace std;

/*
Test stateful operators Count and Average.
*/
int main() {
	Count count;
	NaiveTimeSlidingWindow<long>* nwin  = new NaiveTimeSlidingWindow<long>();
	nwin->setStatefulOperator(&count);

	Average avg("speed");
	NaiveTimeSlidingWindow<double>* nwin2 = new NaiveTimeSlidingWindow<double>();
	nwin2->setStatefulOperator(&avg);
	
	for (int i = 0; i < 10; i++) {
		EventPtr e = EventGenerator::generateEvent();
		nwin->push_back(e);
		nwin2->push_back(e);

		long countResult = 0;
		nwin->reevaluate(countResult);
		cout << "count = " << countResult << endl;

		double avgResult = 0.0;
		nwin2->reevaluate(avgResult);
		cout << "avg = " << avgResult << endl;
	}

	system("pause");
	return 0;
}

