#include <iostream>

#include "../performanceTest/DataSample1.h"
#include "../../util/Utils.h"
#include "../performanceTest/SampleEventGenerator.h"

using namespace std;

int main() {

	SampleEventGenerator g;
	vector<EventPtr> v = g.generateSampleEvent1();

	for (EventPtr e : v) {
		cout << "" << *e << "\\n\\" << endl;
	}

	system("pause");
	return 0;
}