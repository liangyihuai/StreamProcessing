#include "../../stdafx.h"
#include <iostream>
#include "../../gui/RuleRegisterUtils.h"
#include "../../gui/MultiThreads.h"
#include "../../execution/ExecuteScheduler.h"
#include "RuleSpec.h"

using namespace std;

int main() {
	RuleRegisterUtils::registerEventFilter(event_filter_rule);
	RuleRegisterUtils::registerEventCapture(event_filter_rule2);
	RuleRegisterUtils::registerEventCapture(ec_enemy_target);
	RuleRegisterUtils::registerEventCapture(ec_ally_target);

	RuleRegisterUtils::registerCQ(cq_enemy_aircraft);
	RuleRegisterUtils::registerCQ(cq_enemy_battleship);
	RuleRegisterUtils::registerCQ(cq_enemy_submarine);
	RuleRegisterUtils::registerCQ(cq_ally_aircraft);
	RuleRegisterUtils::registerCQ(cq_ally_battleship);
	RuleRegisterUtils::registerCQ(cq_ally_submarine);
	RuleRegisterUtils::registerCQ(cq_enemy_approaching_aircraft_severe);
	RuleRegisterUtils::registerCQ(cq_enemy_hovering_aircraft_common);
	RuleRegisterUtils::registerCQ(cq_enemy_hovering_aircraft_noThreat);
	RuleRegisterUtils::registerCQ(cq_enemy_battleship_hovering_common);
	RuleRegisterUtils::registerCQ(cq_enemy_battleship_approaching_severe);
	RuleRegisterUtils::registerCQ(cq_enemy_battleship_hovering_noThreat);
	RuleRegisterUtils::registerCQ(cq_enemy_submarine_hovering_common);
	RuleRegisterUtils::registerCQ(cq_enemy_submarine_approaching_severe);
	RuleRegisterUtils::registerCQ(cq_enemy_submarine_hovering_noThreat);
	RuleRegisterUtils::registerCQ(cq_count_severe_threat_battleship);
	RuleRegisterUtils::registerCQ(cq_count_common_threat_battleshp);
	RuleRegisterUtils::registerCQ(cq_count_no_threat_battleshp);
	RuleRegisterUtils::registerCQ(cq_count_severe_threat_aircraft);
	RuleRegisterUtils::registerCQ(cq_count_common_threat_aircraft);
	RuleRegisterUtils::registerCQ(cq_count_no_threat_aircraft);
	RuleRegisterUtils::registerCQ(cq_count_severe_threat_Submarine);
	RuleRegisterUtils::registerCQ(cq_count_common_threat_Submarine);
	RuleRegisterUtils::registerCQ(cq_count_no_threat_Submarine);
	RuleRegisterUtils::registerCQ(cq_situation_noThreat_AircraftBattleshipSubmarine);
	RuleRegisterUtils::registerCQ(cq_situation_noThreat_battleship);
	RuleRegisterUtils::registerCQ(cq_situation_common_battleship);
	RuleRegisterUtils::registerCQ(cq_situation_severe_battleship);
	RuleRegisterUtils::registerCQ(cq_situation_noThreat_aircraft);
	RuleRegisterUtils::registerCQ(cq_situation_common_aircraft);
	RuleRegisterUtils::registerCQ(cq_situation_severe_aircraft);
	RuleRegisterUtils::registerCQ(cq_situation_noThreat_submarine);
	RuleRegisterUtils::registerCQ(cq_situation_common_submarine);
	RuleRegisterUtils::registerCQ(cq_situation_severe_submarine);
	RuleRegisterUtils::registerCQ(cq_situation_severe_commonBattleship);
	RuleRegisterUtils::registerCQ(cq_situation_severe_commonAircraft);
	RuleRegisterUtils::registerCQ(cq_situation_severe_commonSubmarine);
	RuleRegisterUtils::registerCQ(cq_situation_servereAircraft_commonBattleship);
	RuleRegisterUtils::registerCQ(cq_situation_servereBattleship_commonAircraft);
	RuleRegisterUtils::registerCQ(cq_situation_commonAircraft_severeSubmarine);
	RuleRegisterUtils::registerCQ(cq_situation_severe_AircraftBattleshipSubmarine);

	RuleRegisterUtils::registerCEP(cep_response_enemy_battleship1);
	RuleRegisterUtils::registerCEP(cep_response_enemy_battleship2);
	RuleRegisterUtils::registerCEP(cep_response_enemy_aircraft1);
	RuleRegisterUtils::registerCEP(cep_response_enemy_aircraft2);
	RuleRegisterUtils::registerCEP(cep_response_enemy_severe_aircraftBattleshipSubmarine);

	//thread for event filtering.
	ThreadOfEventFilter* threadOfEventFilter = new ThreadOfEventFilter();
	threadOfEventFilter->runThread().detach();

	ExecuteScheduler::initialize();

	//thread for EventCapture, CQ and CEP.
	ThreadOfProcessUnit * threadOfProcessUnit = new ThreadOfProcessUnit();
	threadOfProcessUnit->runThread().detach();

	system("pause");
	return 0;
}