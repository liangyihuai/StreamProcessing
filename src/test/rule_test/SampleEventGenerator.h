#pragma once
#include "../../common/Event.h"
#include "../../util/Utils.h"

class SampleEventGenerator {
public:
	SampleEventGenerator(int eventNum = 75);
	~SampleEventGenerator();

	vector<EventPtr> generateSampleEvent1();

private:
	//for sample data 1
	float obj0_lon_step_range_min = -0.01;//the minimum moving range of the first objest in longitude direction.
	float obj0_lon_step_range_max = 0.03;
	float obj0_lat_step_range_min = 0.03;
	float obj0_lat_step_range_max = 0.09;

	float obj_other_step_range_min = -0.08;//the minimum moving range of other objects
	float obj_other_step_range_max = 0.08;

	float min_lon_other_obj = 127.8;
	float max_lon_other_obj = 128.5;

	float min_lat_other_obj = 35.1;
	float max_lat_other_obj = 35.6;

	vector<vector<EventPtr>*> trajectoryBuffer;

	int eventNum;

	//for sample data 2

};