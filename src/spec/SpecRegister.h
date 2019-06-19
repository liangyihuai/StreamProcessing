#pragma once

#include <unordered_map>
#include <string>

/*
To store input rule specifications at string form.
*/
class SpecRegister {
private:
	//output target name to string rule
	static std::unordered_map<std::string, std::string> event_filter_rule_map;
	static std::unordered_map<std::string, std::string> event_capture_rule_map;
	static std::unordered_map<std::string, std::string> cq_rule_map;
	static std::unordered_map<std::string, std::string> cep_rule_map;
public:

	static void register_event_filter_rule(string output_target, string rules);
	static void register_event_capture_rule(string output_target, string rules);
	static void register_cq_rule(string output_target, string rules);
	static void register_cep_rule(string output_target, string rules);

	static string query_event_filter_rule(string output_target);
	static string query_event_capture_rule(string output_target);
	static string query_cq_rule(string output_target);
	static string query_cep_rule(string output_target);
	static string query(string output_target);
	static list<string> queryAll();

	static bool delete_event_filter_rule(string output_target);
	static bool delete_event_capture(string output_target);
	static bool delete_cq_rule(string output_target);
	static bool delete_cep_rule(string output_target);
	static bool delete_rule(string output_target);
};