#include "SinusoidalWaveRealTime.h"
#include <QApplication>
#include "InvalidFrequencyException.h"
#include "WaveException.h"
#include "WaveGUI.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	bool tema2 = false;
	bool final = true;

	if (final) {
		WaveGUI waveGUI;
		waveGUI.show();
		a.exec();
	}
	else if (tema2)
	{
		try {
			SinusoidalWaveFactory factory;
			SinusoidalWaveRealTime<double>* wave1 = factory.createWave(1.0, 2.0);
			SinusoidalWaveRealTime<int>* wave3 = factory.createWave(3, 4);

			SinusoidalWaveRealTime<double> waveExampleDouble(6.0, 1.0);
			Wave* basePtrDouble = &waveExampleDouble;
			SinusoidalWaveRealTime<double>* derivedPtrDouble = dynamic_cast<SinusoidalWaveRealTime<double>*>(basePtrDouble);

			if (derivedPtrDouble) {
				SinusoidalWaveRealTime<double>& waveToShowDouble = *derivedPtrDouble;

				waveToShowDouble.show();

				return a.exec();
			}
			else {
				std::cerr << "Downcast failed!" << std::endl;
				return 1;
			}

			SinusoidalWaveRealTime<int> waveExampleInt(6, 1);
			Wave* basePtrInt = &waveExampleInt;

			SinusoidalWaveRealTime<int>* derivedPtrInt = dynamic_cast<SinusoidalWaveRealTime<int>*>(basePtrInt);

			if (derivedPtrInt) {
				SinusoidalWaveRealTime<int>& waveToShowInt = *derivedPtrInt;

				waveToShowInt.show();

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
		a.exec();
	}
	return 1;
}