#include "SinusoidalWaveFactory.h"

template <typename T>
SinusoidalWaveRealTime<T>* SinusoidalWaveFactory::createWave(T frequency, T amplitude) {
	return new SinusoidalWaveRealTime<T>(frequency, amplitude);
}

template SinusoidalWaveRealTime<double>* SinusoidalWaveFactory::createWave<double>(double, double);
template SinusoidalWaveRealTime<int>* SinusoidalWaveFactory::createWave<int>(int, int);

SinusoidalWaveFactory::SinusoidalWaveFactory()
{
}

SinusoidalWaveFactory::~SinusoidalWaveFactory()
{
}