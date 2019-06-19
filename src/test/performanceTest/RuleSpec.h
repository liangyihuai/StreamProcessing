#pragma once

#include <iostream>
#include <vector>

using namespace std;


string event_filter_rule = "If not duplicate(id) & not unusual(speed)\
\r\nFrom rawData\
\r\nThen targetData";


string ec_rule5 = "If target.iff = unknown\
\r\nFrom targetData\
\r\nThen enemyTarget";


string cq_enemy_approaching = "IF approaching(EnemyTarget) = true & distance(127.5, 35.5) < 0.1 & speed > 150\
\r\nFROM EnemyTarget\
\r\nTHEN SevereThreat1, threatLevel = severe";

string cq_enemy_hovering = "IF hovering(EnemyTarget) = true & distance(127.5, 35.5) < 0.1\
\r\nFROM EnemyTarget\
\r\nTHEN SevereThreat2, threatLevel = common";


string cq_enemy_aircraft = "IF ElevationAngle >30 & Speed > 150 & elevation > 100\
\r\nFROM EnemyTarget\
\r\nTHEN EnemyAircraft, objectType = aircraft";


string cq_enemy_distance = "IF elevation > 10\
\r\nFROM EnemyTarget\
\r\nTHEN EnemyDistance, distance(127.12, 35.33)";

//
string cq_enemy_count = "IF elevation > 10\
\r\nFROM EnemyTarget\
\r\nWindow length=3000, sliding=1000, distinct=objId\
\r\nTHEN EnemyCount, count()";


string cq_enemy_count1 = "If EnemyCount.count > 2 & EnemyDistance.distance >0.01\
\r\nFrom EnemyCount, EnemyDistance\
\r\nWindow length = 1000, sliding=1000\
\r\nThen enemycount1";


string cep_exist1 = "If exist(EnemyDistance) & exist(EnemyCount) & EnemyCount.count > 3 & EnemyDistance.distance > 0.3\
\r\nFrom EnemyCount, EnemyDistance\
\r\nWindow length=3000, sliding=1000\
\r\nThen cep_exist1";
