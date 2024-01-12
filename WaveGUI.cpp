#include "WaveGUI.h"

WaveGUI::WaveGUI(QWidget* parent) : QWidget(parent) {
	setWindowTitle("Wave Generator");
	setFixedSize(400, 250);

	amplitudeLabel = new QLabel("Amplitude:");
	frequencyLabel = new QLabel("Frequency:");

	amplitudeEdit = new QLineEdit;
	frequencyEdit = new QLineEdit;

	createWaveButton = new QPushButton("Create Wave");
	styleButton(createWaveButton);
	connect(createWaveButton, SIGNAL(clicked()), this, SLOT(createWave()));

	QFormLayout* formLayout = new QFormLayout;
	formLayout->addRow(amplitudeLabel, amplitudeEdit);
	formLayout->addRow(frequencyLabel, frequencyEdit);

	QGroupBox* groupBox = new QGroupBox("Wave Parameters");
	groupBox->setLayout(formLayout);
	styleGroupBox(groupBox);

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(groupBox);
	layout->addWidget(createWaveButton);
	layout->setAlignment(createWaveButton, Qt::AlignHCenter);

	setLayout(layout);

	setFixedSize(400, 250);
}

void WaveGUI::createWave() {
	try {
		double amplitude = amplitudeEdit->text().toDouble();
		double frequency = frequencyEdit->text().toDouble();

		if (amplitude <= 0 || frequency <= 0) {
			QMessageBox::critical(this, "Error", "Invalid amplitude or frequency. Please enter positive values.");
		}
		else {
			SinusoidalWaveFactory factory;
			Wave* wave = factory.createWave(frequency, amplitude);
			SinusoidalWaveRealTime<double>* waveToShow = dynamic_cast<SinusoidalWaveRealTime<double>*>(wave);
			waveToShow->setWindowTitle("SinusoidalWave - Count: " + QString::number(SinusoidalWaveRealTime<double>::waveCount));
			waveToShow->show();
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void WaveGUI::styleButton(QPushButton* button) {
	button->setStyleSheet("QPushButton {"
		"background-color: #4CAF50;"
		"border: none;"
		"color: white;"
		"padding: 10px 20px;"
		"text-align: center;"
		"text-decoration: none;"
		"display: inline-block;"
		"font-size: 16px;"
		"border-radius: 5px;"
		"}"
		"QPushButton:hover {"
		"background-color: #45a049;"
		"}"
	);
}

void WaveGUI::styleGroupBox(QGroupBox* groupBox) {
	groupBox->setStyleSheet("QGroupBox {"
		"border: 2px solid gray;"
		"border-radius: 5px;"
		"margin-top: 1ex;"
		"}"
		"QGroupBox::title {"
		"subcontrol-origin: margin;"
		"left: 10px;"
		"padding: 0 3px;"
		"}"
	);
}