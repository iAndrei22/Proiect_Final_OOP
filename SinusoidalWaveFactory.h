#pragma once

#include "SinusoidalWaveRealTime.h"

// Forward declaration
template <typename T>
class SinusoidalWaveRealTime;

class SinusoidalWaveFactory {
public:
	SinusoidalWaveFactory();  // Constructorul clasei
	~SinusoidalWaveFactory(); // Destructorul clasei

	template<typename T>
	SinusoidalWaveRealTime<T>* createWave(T frequency, T amplitude);
};
