
#include "../stdafx.h"

#include "SpecRegister.h"

std::unordered_map<std::string, std::string> SpecRegister::event_filter_rule_map;
std::unordered_map<std::string, std::string> SpecRegister::event_capture_rule_map;
std::unordered_map<std::string, std::string> SpecRegister::cq_rule_map;
std::unordered_map<std::string, std::string> SpecRegister::cep_rule_map;

void SpecRegister::register_event_filter_rule(string output_target, string rules) {
	event_filter_rule_map[output_target] = rules;
}

void SpecRegister::register_event_capture_rule(string output_target, string rules) {
	event_capture_rule_map[output_target] = rules;
}

void SpecRegister::register_cq_rule(string output_target, string rules) {
	cq_rule_map[output_target] = rules;
}

void SpecRegister::register_cep_rule(string output_target, string rules) {
	cep_rule_map[output_target] = rules;
}

string SpecRegister::query_event_filter_rule(string output_target) {
	return event_filter_rule_map[output_target];
}

string SpecRegister::query_event_capture_rule(string output_target) {
	return event_capture_rule_map[output_target];
}

string SpecRegister::query_cq_rule(string output_target) {
	return cq_rule_map[output_target];
}

string SpecRegister::query_cep_rule(string output_target) {
	return cep_rule_map[output_target];
}

bool SpecRegister::delete_event_filter_rule(string output_target) {
	event_filter_rule_map.erase(output_target);
	return true;
}

bool SpecRegister::delete_event_capture(string output_target) {
	event_capture_rule_map.erase(output_target);
	return true;
}

bool SpecRegister::delete_cq_rule(string output_target) {
	cq_rule_map.erase(output_target);
	return true;
}

bool SpecRegister::delete_cep_rule(string output_target) {
	cep_rule_map.erase(output_target);
	return true;
}

bool SpecRegister::delete_rule(string output_target) {
	if (event_capture_rule_map.find(output_target) != event_capture_rule_map.end()) {
		event_capture_rule_map.erase(output_target);
		return true;
	}
	else if (cq_rule_map.find(output_target) != cq_rule_map.end()) {
		cq_rule_map.erase(output_target);
		return true;
	}
	else if (cep_rule_map.find(output_target) != cep_rule_map.end()) {
		cep_rule_map.erase(output_target);
		return true;
	}
	return false;
}

string SpecRegister::query(string output_target) {
	if (event_capture_rule_map.find(output_target) != event_capture_rule_map.end()) {
		return event_capture_rule_map[output_target];
	}
	else if (cq_rule_map.find(output_target) != cq_rule_map.end()) {
		return cq_rule_map[output_target];
	}
	else if (cep_rule_map.find(output_target) != cep_rule_map.end()) {
		return cep_rule_map[output_target];
	}
	return "No target rule specification.";	
}

list<string> SpecRegister::queryAll() {
	list<string> allSpecs;
	for (auto iter = event_capture_rule_map.begin(); iter != event_capture_rule_map.end(); iter++) {
		allSpecs.push_back(iter->first);
		allSpecs.push_back(iter->second);
	}
	for (auto iter = cq_rule_map.begin(); iter != cq_rule_map.end(); iter++) {
		allSpecs.push_back(iter->first);
		allSpecs.push_back(iter->second);
	}
	for (auto iter = cep_rule_map.begin(); iter != cep_rule_map.end(); iter++) {
		allSpecs.push_back(iter->first);
		allSpecs.push_back(iter->second);
	}
	return allSpecs;
}