#pragma once

#include "CQSpec.h"
#include "SpecParser.h"


class CQSpecParser: public SpecParser {
public:

	//static list<CQSpec*> parseAllCQSpec(const list<string> allCQSpecs);

	/*
	If distance < 20
	From airplane
	Window type=, len=, sliding=
	Then WideAreaDefenceTarget
	*/
	static CQSpec* parseOneCQSpec(list<string> oneCQSpec);
};