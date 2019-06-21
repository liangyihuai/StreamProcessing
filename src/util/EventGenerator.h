#pragma once

#include "Utils.h"
#include "../common/Event.h"
#include "iostream"

using namespace std;

class EventGenerator {
public:

	static EventPtr generateEvent() {
		Event* e = new Event(Utils::id++, Utils::getTime());

		e->addAttr("objid", Utils::movingObject_id_count++);
		if (Utils::movingObject_id_count >= Utils::movingObject_id_total_numble) {
			Utils::movingObject_id_count = 0;
		}

		//e->addAttr("iff", "unknown");

		if (((int)Utils::randomFloat(0, 1000)) % 2 == 0) {
			e->addAttr("iff", "ally");
		}
		else {
			e->addAttr("iff", "unknown");
		}
		e->addAttr("elevationAngle", (float)Utils::randomFloat(0, 90));
		e->addAttr("speed", (float)Utils::randomFloat(-10, 800));
		e->addAttr("lon", (float)Utils::randomFloat(127, 129));
		e->addAttr("lat", (float)Utils::randomFloat(35, 37));
		e->addAttr("dir", (float)Utils::randomFloat(0, 360));
		float ele = (float)Utils::randomFloat(-300, 10000);
		e->addAttr("elevation", ele);
		e->addAttr("ele", ele);

		if (Utils::id % 2 == 0) {
			e->addAttr("communicationsetup", true);
		}
		else {
			e->addAttr("communicationsetup", false);
		}

		e->addAttr("elevationangle", (float)Utils::randomFloat(0, 360));
		/*double ran = ((double)rand())/RAND_MAX;
		if (ran < 0.3) {
			e->addAttr("electromagnetic", "enemy");
		}
		else if (ran < 0.6) {
			e->addAttr("electromagnetic", "neutral");
		}
		else {
			e->addAttr("electromagnetic", "ally");
		}*/

		//cout << *e;
		return EventPtr (e);
	}

};


