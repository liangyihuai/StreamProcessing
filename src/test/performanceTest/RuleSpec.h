#pragma once

#include <iostream>
#include <vector>

using namespace std;

//-------------------------------------------------------------
/*event filtering*/
//-------------------------------------------------------------
string event_filter_rule = "If not duplicate(id) & not unusual(speed)\
\r\nFrom rawData\
\r\nThen FilterEvent0";

string event_filter_rule2 = "IF id > -1 & 0 <= dir <= 360 & 0 <= lon <= 180 & 0 <= lat <= 180 & -10 < ele < 5000 & 0 <= elevationAngle <= 90 & 0 <= speed < 5000\
\r\nFROM FilterEvent0\
\r\nTHEN FilteredData";

//-------------------------------------------------------------
/*classify enemy targets and ally targets.*/
//-------------------------------------------------------------
string ec_enemy_target = "If FilteredData.iff = unknown\
\r\nFrom FilteredData\
\r\nThen EnemyTarget";

string ec_ally_target = "If FilteredData.iff == ally\
\r\nFrom FilteredData\
\r\nThen AllyTarget";

//-------------------------------------------------------------
/*classify aircraft, battleship and submarine for enemy and ally.*/
//-------------------------------------------------------------
string cq_enemy_aircraft = "IF ElevationAngle>20 & speed>150 & elevation > 100\
\r\nFROM EnemyTarget\
\r\nTHEN EnemyAircraft, objectType = aircraft";

string cq_enemy_battleship = "IF ElevationAngle < 10 & elevation < 10 & elevation > -3 & Speed<50\
\r\nFROM EnemyTarget\
\r\nTHEN EnemyBattleship, objectType = battleship";

string cq_enemy_submarine = "IF elevation < -3 & speed < 50\
\r\nFrom EnemyTarget\
\r\nTHEN EnemySubmarine, objectType = submarine";

string cq_ally_aircraft = "IF ElevationAngle>20 & speed>150 & elevation > 100\
\r\nFROM AllyTarget\
\r\nTHEN AllyAircraft, objectType = aircraft";

string cq_ally_battleship = "IF ElevationAngle < 10 & elevation < 10 & elevation > -3 & Speed<50\
\r\nFROM AllyTarget\
\r\nTHEN AllyBattleship, objectType = battleship";

string cq_ally_submarine = "IF elevation < -3 & speed < 50\
\r\nFrom AllyTarget\
\r\nTHEN AllySubmarine, objectType = submarine";

//------------------------------------------------------------------------------------------
/*Threat level of each moving object, including severe threat, common threat and no threat.*/
//------------------------------------------------------------------------------------------
string cq_enemy_approaching_aircraft_severe = "IF approaching(EnemyAircraft) = true & distance(127.8, 36.9) < 0.5 & speed > 150\
\r\nFROM EnemyAircraft\
\r\nTHEN AircraftSevereThreat, threatLevel = severe";

string cq_enemy_hovering_aircraft_common = "IF hovering(EnemyAircraft) = true & distance(127.5, 35.5) > 0.5 & distance(127.5, 35.5) < 1\
\r\nFrom EnemyAircraft\
\r\nThen AircraftCommonThreat, threatLevel=common";

string cq_enemy_hovering_aircraft_noThreat =  "IF hovering(EnemyAircraft) = true & distance(127.5, 35.5) > 1\
\r\nFrom EnemyAircraft\
\r\nThen AircraftNoThreat, threatLevel=no";


string cq_enemy_battleship_hovering_common = "IF hovering(EnemyBattleship) = true & distance(127.5, 35.5) > 0.5 & distance(127.5, 35.5) < 1\
\r\nFrom EnemyBattleship\
\r\nThen BattleshipCommonThreat, threatLevel=common";

string cq_enemy_battleship_approaching_severe= "IF approaching(EnemyBattleship) = true & distance(127.5, 35.5) < 0.5\
\r\nFrom EnemyBattleship\
\r\nThen BattleshipSevereThreat, threatLevel=severe";

string cq_enemy_battleship_hovering_noThreat = "IF hovering(EnemyBattleship) = true & distance(127.5, 35.5) > 1 \
\r\nFrom EnemyBattleship\
\r\nThen BattleshipNoThreat, threatLevel=no";


string cq_enemy_submarine_hovering_common = "IF hovering(EnemySubmarine) = true & distance(127.5, 35.5) > 0.5 & distance(127.5, 35.5) < 1\
\r\nFrom EnemySubmarine\
\r\nThen SubmarineCommonThreat, threatLevel=common";

string cq_enemy_submarine_approaching_severe = "IF approaching(EnemySubmarine) = true & distance(127.5, 35.5) < 0.5\
\r\nFrom EnemySubmarine\
\r\nThen SubmarineSevereThreat, threatLevel=severe";

string cq_enemy_submarine_hovering_noThreat = "IF hovering(EnemySubmarine) = true & distance(127.5, 35.5) > 1 \
\r\nFrom EnemySubmarine\
\r\nThen SubmarineNoThreat, threatLevel=no";

//-------------------------------------------------------------
/*Count by threat levels, which are severe threat, common threat, no threat.*/
//-------------------------------------------------------------
string cq_count_severe_threat_battleship = "IF BattleshipSevereThreat.threatLevel = severe\
\r\nFrom BattleshipSevereThreat\
\r\nWindow length = 1000, sliding=1000, distinct=objID\
\r\nThen BattleshipCountSevereThreat, Count()";

string cq_count_common_threat_battleshp = "IF BattleshipCommonThreat.threatLevel = common\
\r\nFrom BattleshipCommonThreat\
\r\nWindow length = 1000, sliding=1000, distinct=objID\
\r\nThen BattleshipCountCommonThreat, count()";

string cq_count_no_threat_battleshp = "IF BattleshipNoThreat.threatLevel = no\
\r\nFrom BattleshipNoThreat\
\r\nWindow length = 1000, sliding=1000, distinct=objID\
\r\nThen BattleshipCountNoThreat, count()";

string cq_count_severe_threat_aircraft = "IF AircraftSevereThreat.threatLevel = severe\
\r\nFrom AircraftSevereThreat\
\r\nWindow length = 1000, sliding=1000, distinct=objID\
\r\nThen AircraftCountSevereThreat, Count()";

string cq_count_common_threat_aircraft = "IF AircraftCommonThreat.threatLevel = common\
\r\nFrom AircraftCommonThreat\
\r\nWindow length = 1000, sliding=1000, distinct=objID\
\r\nThen AircraftCountCommonThreat, Count()";

string cq_count_no_threat_aircraft = "IF AircraftNoThreat.threatLevel = no\
\r\nFrom AircraftNoThreat\
\r\nWindow length = 1000, sliding=1000, distinct=objID\
\r\nThen AircraftCountNoThreat, Count()";

string cq_count_severe_threat_Submarine = "IF SubmarineSevereThreat.threatLevel = severe\
\r\nFrom SubmarineSevereThreat\
\r\nWindow length = 1000, sliding=1000, distinct=objID\
\r\nThen SubmarineCountSevereThreat, Count()";

string cq_count_common_threat_Submarine = "IF SubmarineCommonThreat.threatLevel = common\
\r\nFrom SubmarineCommonThreat\
\r\nWindow length = 1000, sliding=1000, distinct=objID\
\r\nThen SubmarineCountCommonThreat, Count()";

string cq_count_no_threat_Submarine = "IF SubmarineNoThreat.threatLevel = no\
\r\nFrom SubmarineNoThreat\
\r\nWindow length = 1000, sliding=1000, distinct=objID\
\r\nThen SubmarineCountNoThreat, Count()";

//-------------------------------------------------------------
/*Threat situation detection.*/
//-------------------------------------------------------------
string cq_situation_common_battleship = "If BattleshipCountCommonThreat.count >= 3\
\r\nFrom BattleshipCountCommonThreat\
\r\nThen CommonBattleshipSituationThreat_Level1";

string cq_situation_severe_battleship = "If BattleshipCountSevereThreat.count > 0\
\r\nFrom BattleshipCountSevereThreat\
\r\nThen SevereBattleshipSituationThreat_Level2";

string cq_situation_common_aircraft = "If AircraftCountCommonThreat.count >= 3\
\r\nFrom AircraftCountCommonThreat\
\r\nThen CommonAircraftSituationThreat_Level1";

string cq_situation_severe_aircraft = "If AircraftCountSevereThreat.count >= 0\
\r\nFrom AircraftCountSevereThreat\
\r\nThen SevereAircraftSituationThreat_Level2";

string cq_situation_severe_commonBattleship = "If BattleshipCountCommonThreat.count > 2 & BattleshipCountSevereThreat.count > 0\
\r\nFrom BattleshipCountCommonThreat, BattleshipCountSevereThreat\
\r\nWindow length = 1000, sliding=1000\
\r\nThen Severe_Common_battleshipSituationThreat_Level3;";

string cq_situation_severe_commonAircraft = "If AircraftCountCommonThreat.count > 2 & AircraftCountSevereThreat.count > 0\
\r\nFrom AircraftCountCommonThreat, AircraftCountSevereThreat\
\r\nWindow length = 1000, sliding=1000\
\r\nThen Severe_Common_aircraftSituationThreat_Level3;";

/*severe aircraft and common battleship*/
string cq_situation_servereAircraft_commonBattleship = "If AircraftCountSevereThreat.count > 0 & BattleshipCountCommonThreat.count > 0\
\r\nFrom AircraftCountSevereThreat, BattleshipCountCommonThreat\
\r\nWindow length = 1000, sliding=1000\
\r\nThen SevereAircraft_CommonBattleship_SituationThreat_Level4;";

/*common aircraft and severe battleship*/
string cq_situation_servereBattleship_commonAircraft = "If AircraftCountCommonThreat.count > 0 & BattleshipCountSevereThreat.count > 0\
\r\nFrom AircraftCountCommonThreat, BattleshipCountSevereThreat\
\r\nWindow length = 1000, sliding=1000\
\r\nThen CommonAircraft_SevereBattleship_SituationThreat_Level4;";

//-------------------------------------------------------------
/*CEP Response*/
//-------------------------------------------------------------
string cep_response_enemy_battleship1 = "If exist(CommonBattleshipSituationThreat_Level1) & exist(BattleshipCountCommonThreat) & BattleshipCountCommonThreat.objectType == battleship & BattleshipCountCommonThreat.distance(127.5, 35.5) > 0.5\
	\r\nFrom CommonBattleshipSituationThreat_Level1, BattleshipCountCommonThreat\
	\r\nThen ResponseEnemyBattleship1";

string cep_response_enemy_battleship2 = "If exist(SevereBattleshipSituationThreat_Level2) & exist(BattleshipCountSevereThreat) & BattleshipCountSevereThreat.objectType == battleship & BattleshipCountSevereThreat.distance(127.5, 35.5) < 0.5\
	\r\nFrom SevereBattleshipSituationThreat_Level2, BattleshipCountSevereThreat\
	\r\nThen ResponseEnemyBattleship2";

string cep_response_enemy_aircraft1 = "If exist(CommonAircraftSituationThreat_Level1) & exist(AircraftCountCommonThreat) & AircraftCountCommonThreat.objectType ==  aircraft & AircraftCountCommonThreat..distance(127.5, 35.5) > 0.5\
\r\nFrom CommonAircraftSituationThreat_Level1, AircraftCountCommonThreat\
\r\nThen ResponseEnemyAircraft1";

string cep_response_enemy_aircraft2 = "If exist(SevereAircraftSituationThreat_Level2) & exist(AircraftCountSevereThreat) & AircraftCountSevereThreat.objectType ==  aircraft & AircraftCountSevereThreat..distance(127.5, 35.5) < 0.5\
\r\nFrom SevereAircraftSituationThreat_Level2, AircraftCountSevereThreat\
\r\nThen ResponseEnemyAircraft2";





//string cq_count_common_threat_battleship = "IF CommonThreat.objectType == Battleship\
//\r\nFrom CommonThreat\
//\r\nWindow length = 1000, sliding=1000, distinct=objID\
//\r\nThen BattleshipCountCommonThreat, Count()";
//
//string cq_count_severe_threat_aircraft = "IF SevereThreat.objectType == aircraft\
//\r\nFrom SevereThreat\
//\r\nWindow length = 1000, sliding=1000, distinct=objID\
//\r\nThen AircraftCountSevereThreat, count()";
//
//string cq_count_common_threat_aircraft = "IF CommonThreat.objectType == aircraft\
//\r\nFrom CommonThreat\
//\r\nWindow length = 1000, sliding=1000, distinct=objID\
//\r\nThen AircraftCountCommonThreat, count()";
//
//
//
//
//string cq_enemy_approaching = "IF approaching(EnemyTarget) = true & distance(127.5, 35.5) < 0.1 & speed > 150\
//\r\nFROM EnemyTarget\
//\r\nTHEN SevereThreat1, threatLevel = severe";
//
//string cq_enemy_hovering = "IF hovering(EnemyTarget) = true & distance(127.5, 35.5) < 0.1\
//\r\nFROM EnemyTarget\
//\r\nTHEN SevereThreat2, threatLevel = common";


//string cq_enemy_aircraft = "IF ElevationAngle >30 & Speed > 150 & elevation > 100\
//\r\nFROM EnemyTarget\
//\r\nTHEN EnemyAircraft, objectType = aircraft";
//
//
//string cq_enemy_distance = "IF elevation > 10\
//\r\nFROM EnemyTarget\
//\r\nTHEN EnemyDistance, distance(127.12, 35.33)";
//
////
//string cq_enemy_count = "IF elevation > 10\
//\r\nFROM EnemyTarget\
//\r\nWindow length=3000, sliding=1000, distinct=objId\
//\r\nTHEN EnemyCount, count()";
//
//
//string cq_enemy_count1 = "If EnemyCount.count > 2 & EnemyDistance.distance >0.01\
//\r\nFrom EnemyCount, EnemyDistance\
//\r\nWindow length = 1000, sliding=1000\
//\r\nThen enemycount1";
//
//
//string cep_exist1 = "If exist(EnemyDistance) & exist(EnemyCount) & EnemyCount.count > 3 & EnemyDistance.distance > 0.3\
//\r\nFrom EnemyCount, EnemyDistance\
//\r\nWindow length=3000, sliding=1000\
//\r\nThen cep_exist1";
