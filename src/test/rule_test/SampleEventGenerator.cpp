#include "../../stdafx.h"

#include "SampleEventGenerator.h"

SampleEventGenerator::SampleEventGenerator(int eventNum) {
	this->eventNum = eventNum;

	for (int i = 0; i < Utils::movingObject_id_total_numble; i++) {
		this->trajectoryBuffer.push_back(new vector<EventPtr>);
	}
}

vector<EventPtr> SampleEventGenerator::generateSampleEvent1() {
	srand((unsigned)time(0));

	int n = this->eventNum;
	vector<EventPtr> result;

	for (int i = 0; i < n; i++) {
		Event* e = new Event(Utils::id++, Utils::getTime());

		int objId = Utils::movingObject_id_count++;
		e->addAttr("objid", objId);
		if (objId == 0) {//object ID = 0
			/*speed*/
			e->addAttr("speed", (float)Utils::randomFloat(200, 300));

			/*longitude and latitude*/
			float newLon = 0.0f;
			float newLat = 0.0f;
			if(trajectoryBuffer[0]->size() == 0){
				newLon = 127.6F;
				newLat = 35.5F;
			}else if (trajectoryBuffer[0]->size() == 1) {
				float previousLon = trajectoryBuffer[0]->at(0)->getFloat("lon");
				float previousLat = trajectoryBuffer[0]->at(0)->getFloat("lat");
				newLon = previousLon + Utils::randMToN(obj0_lon_step_range_min, obj0_lon_step_range_max);
				newLat = previousLat + Utils::randMToN(obj0_lat_step_range_min, obj0_lat_step_range_max);
			}else {
				int currentSize = trajectoryBuffer[0]->size();
				EventPtr previousEvent1 = this->trajectoryBuffer[objId]->at(currentSize - 2);
				EventPtr previousEvent2 = this->trajectoryBuffer[objId]->at(currentSize - 1);

				float lon1 = previousEvent1->getFloat("lon");
				float lat1 = previousEvent1->getFloat("lat");
				float lon2 = previousEvent2->getFloat("lon");
				float lat2 = previousEvent2->getFloat("lat");

				newLon = lon2 + Utils::randMToN(obj0_lon_step_range_min, obj0_lon_step_range_max);
				newLat = lat2 + 0.06 + Utils::randMToN(obj0_lat_step_range_min, obj0_lat_step_range_max);
				if (newLat > 37) {
					newLat = lat2;
					newLon = lon2 + 0.06;
				}
			}

			e->addAttr("lon", newLon);
			e->addAttr("lat", newLat);

			e->addAttr("elevationangle", (float)Utils::randomFloat(40, 90));

			float ele = (float)Utils::randomFloat(100, 1000);
			e->addAttr("elevation", ele);
			e->addAttr("ele", ele);
		}else {
			/*speed*/
			e->addAttr("speed", (float)Utils::randomFloat(3, 29));
			/*longitude and latitude*/
			float newLon = 0.0f;
			float newLat = 0.0f;
			if (trajectoryBuffer[objId]->size() == 0) {
				newLon = Utils::randMToN(min_lon_other_obj, max_lon_other_obj);
				newLat = Utils::randMToN(min_lat_other_obj, max_lat_other_obj);
			}
			else if (trajectoryBuffer[objId]->size() == 1) {
				do {
					float previousLon = trajectoryBuffer[objId]->at(0)->getFloat("lon");
					float previousLat = trajectoryBuffer[objId]->at(0)->getFloat("lat");
					newLon = previousLon + Utils::randMToN(obj_other_step_range_min, obj_other_step_range_max);
					newLat = previousLat + Utils::randMToN(obj_other_step_range_min, obj_other_step_range_max);
				} while (newLon < min_lon_other_obj || newLon > max_lon_other_obj
					|| newLat < min_lat_other_obj || newLat > max_lat_other_obj);
			}
			else {
				do {
					int currentSize = trajectoryBuffer[objId]->size();
					EventPtr previousEvent1 = this->trajectoryBuffer[objId]->at(currentSize - 2);
					EventPtr previousEvent2 = this->trajectoryBuffer[objId]->at(currentSize - 1);

					float lon1 = previousEvent1->getFloat("lon");
					float lat1 = previousEvent1->getFloat("lat");
					float lon2 = previousEvent2->getFloat("lon");
					float lat2 = previousEvent2->getFloat("lat");

					float lon_temp = lon2 - lon1;
					float lat_temp = lat2 - lat1;
					float step_temp = 0.06;
					if (lon_temp < -step_temp) lon_temp = -step_temp;
					if (lon_temp > step_temp) lon_temp = step_temp;
					if (lat_temp < -step_temp) lat_temp = -step_temp;
					if (lat_temp > step_temp) lat_temp = step_temp;

					newLon = lon2 + lon_temp + Utils::randMToN(obj_other_step_range_min, obj_other_step_range_max);
					newLat = lat2 + lat_temp + Utils::randMToN(obj_other_step_range_min, obj_other_step_range_max);
					if (newLon < min_lon_other_obj || newLon > max_lon_other_obj
						|| newLat < min_lat_other_obj || newLat > max_lat_other_obj) {
						newLon = lon2 + Utils::randOneOrNegativeOne()*(lon2 - lon1) + Utils::randMToN(obj_other_step_range_min, obj_other_step_range_max);
						newLat = lat2 + Utils::randOneOrNegativeOne()*(lat2 - lat1) + Utils::randMToN(obj_other_step_range_min, obj_other_step_range_max);
					}
				} while (newLon < min_lon_other_obj || newLon > max_lon_other_obj
					|| newLat < min_lat_other_obj || newLat > max_lat_other_obj);
			}

			e->addAttr("lon", newLon);
			e->addAttr("lat", newLat);

			e->addAttr("elevationangle", (float)Utils::randomFloat(0, 9));

			float ele = (float)Utils::randomFloat(-3, 10);
			e->addAttr("elevation", ele);
			e->addAttr("ele", ele);
		}

		if (Utils::movingObject_id_count >= Utils::movingObject_id_total_numble) {
			Utils::movingObject_id_count = 0;
		}

		e->addAttr("iff", "unknown");
		
		e->addAttr("dir", (float)Utils::randomFloat(0, 360));
		
		if (Utils::id % 2 == 0) {
			e->addAttr("communicationsetup", true);
		}
		else {
			e->addAttr("communicationsetup", false);
		}

		EventPtr event(e);
		result.push_back(event);
		this->trajectoryBuffer[objId]->push_back(event);
	}
	
	return result;
}

SampleEventGenerator::~SampleEventGenerator() {
	for (vector<EventPtr>* v : this->trajectoryBuffer) {
		v->clear();
		delete v;
		v = nullptr;
	}
}