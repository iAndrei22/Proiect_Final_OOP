#include "SinusoidalWaveRealTime.h"
#include <QApplication>
#include "InvalidFrequencyException.h"
#include "WaveException.h"
int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	try {
		SinusoidalWaveRealTime wave(2.0, 0.0);
		wave.show();

		return a.exec();
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