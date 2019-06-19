#pragma once

#include "SpecParser.h"

#include "../expression/Condition.h"

#include "EventFilterSpec.h"
#include "../execution/EventCapture.h"
#include "CEPSpec.h"
#include "../op/OperatorRegister.h"
#include "../expression/BoolOpPredicate.h"
#include "../expression/GreatThanOpPreDouble.h"
#include "../expression/LessThanOpPreDouble.h"
#include "../expression/Predicate.h"

class CEPSpecParser{

public:

	//static list<CEPSpec*> parseAllCEPSpec(const list<string> allCEPSpecs);

	/*
	If distance < 20
	From airplane
	Window type=, len=, sliding=
	Then WideAreaDefenceTarget
	*/
	static CEPSpec* parseOneCEPSpec(list<string> oneCEPSpec);

private:
	//currently, assume only & conjunction
	static void parseMultiExpression(string expStr, CEPSpec *cepSpec);

	//only parsing the operator existOp()
	static void parseExistOpExpression(string expStr, CEPSpec * cepSpec);

	//format is: "streamName.field mid right", for example: "plane.speed > 12"
	//It could be "streamName.operatorName() > 12", or
	//"operatorName(streamName.fieldName) > 12"
	static bool splitExpression(const string expression, string& stream, string & fieldName, string &mid, string & right);

	static Predicate * parseValueExpression(string name, string mid, string value);

	//parse the expression with operator
	//1. parse and generate operator
	//2. parse and generate predicate object
	static Predicate * parseExpressionWithOperator(string expression);
};