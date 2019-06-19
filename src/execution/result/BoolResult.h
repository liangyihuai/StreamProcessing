#pragma once

#include "Result.h"

class BoolResult : public Result {
private:
	bool value = false;
public:
	BoolResult() {}

	BoolResult(bool value) : value(value) {}

	void setValue(int v) {
		this->value = v;
	}

	bool getResultBool() override{
		return value;
	};
};