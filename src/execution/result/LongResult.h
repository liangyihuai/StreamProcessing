#pragma once

#include "Result.h"

class LongResult : public Result {
private:
	long value = 0;
public:
	LongResult() {}

	LongResult(long value) : value(value) {}

	void setValue(long v) {
		this->value = v;
	}

	long getResultLong() override {
		return value;
	}
};

