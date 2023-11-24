#include "SinusoidalWaveRealTime.h"
#include <QApplication>
#include "InvalidFrequencyException.h"
#include "WaveException.h"
#include <iostream>
//TODO static
int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	try {
		SinusoidalWaveRealTime waveExample(6.0, 1.0);
		Wave* basePtr = &waveExample;

		SinusoidalWaveRealTime* derivedPtr = dynamic_cast<SinusoidalWaveRealTime*>(basePtr);

		if (derivedPtr) {
			SinusoidalWaveRealTime& waveToShow = *derivedPtr;

			waveToShow.show();

			return a.exec();
		}
		else {
			std::cerr << "Downcast failed!" << std::endl;
			return 1;
		}
	}
	catch (const InvalidFrequencyException& e) {
		std::cerr << "Invalid Frequency Exception: " << e.what() << std::endl;
	}
	catch (const WaveException& e) {
		std::cerr << "Wave Exception: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown Exception" << std::endl;
	}

	return 1;
}