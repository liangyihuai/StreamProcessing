#pragma once

#include <string>

using namespace std;

class RuleSpecForSampleData1 {
public:

	string event_filter_rule = "If not duplicate(id) & not unusual(speed)\
\r\nFrom rawData\
\r\nThen FilteredData";


	string ec_enemy_target = "If FilteredData.iff = unknown\
\r\nFrom FilteredData\
\r\nThen EnemyTarget";


	string ec_enemy_aircraft = "IF ElevationAngle>20 & speed>150 & elevation > 100\
\r\nFROM EnemyTarget\
\r\nTHEN EnemyAircraft";

	string ec_enemy_battleship = "IF ElevationAngle < 10 & elevation < 10 & elevation > -3 & Speed<50\
\r\nFROM EnemyTarget\
\r\nTHEN EnemyBattleship";

	string cq_enemy_approaching_aircraft_severe = "IF approaching(EnemyAircraft) = true & speed > 150\
\r\nFROM EnemyAircraft\
\r\nTHEN AircraftSevereThreat, threatLevel = severe";

	string cq_enemy_battleship_hovering_common = "IF hovering(EnemyBattleship) = true & distance(127.5, 35.5) > 0.5 & distance(127.5, 35.5) < 1\
\r\nFrom EnemyBattleship\
\r\nThen BattleshipCommonThreat, threatLevel=common";


	string cq_count_severe_threat_aircraft = "IF AircraftSevereThreat.threatLevel = severe\
\r\nFrom AircraftSevereThreat\
\r\nWindow length = 4000, sliding=1000, distinct=objID\
\r\nThen AircraftCountSevereThreat, Count()";

	string cq_count_common_threat_battleshp = "IF BattleshipCommonThreat.threatLevel = common\
\r\nFrom BattleshipCommonThreat\
\r\nWindow length = 4000, sliding=1000, distinct=objID\
\r\nThen BattleshipCountCommonThreat, count()";


	/*severe aircraft and common battleship*/
	string cq_situation_servereAircraft_commonBattleship = "If AircraftCountSevereThreat.count > 0 & BattleshipCountCommonThreat.count > 2\
\r\nFrom AircraftCountSevereThreat, BattleshipCountCommonThreat\
\r\nWindow length = 3000, sliding=1000\
\r\nThen SevereAircraft_CommonBattleship_SituationThreat_Level4;";

	string cep_response_enemy_severe_aircraft_commomBattleship = "If exist(SevereAircraft_CommonBattleship_SituationThreat_Level4)\
\r\nFrom SevereAircraft_CommonBattleship_SituationThreat_Level4\
\r\nWindow length=3000, sliding=1000\
\r\nThen Response_Enemy_SevereAircraft_SevereBattleship";

};