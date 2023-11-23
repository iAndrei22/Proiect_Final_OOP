#pragma once

#include "BaseWaveException.h"

class InvalidFrequencyException : public BaseWaveException {
public:
	virtual const char* what() const noexcept override {
		return "Negative Frequency";
	}
};
