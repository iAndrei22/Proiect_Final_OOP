#pragma once
#include "BaseWaveException.h"
class WaveException : public BaseWaveException {
public:
	virtual const char* what() const noexcept override {
		return "Null parameter";
	}
};
