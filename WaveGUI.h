#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QIcon>
#include "SinusoidalWaveFactory.h"
#include "Wave.h"

class WaveGUI : public QWidget {
	Q_OBJECT

public:
	WaveGUI(QWidget* parent = nullptr);

public slots:
	void createWave();

private:
	QLabel* amplitudeLabel;
	QLabel* frequencyLabel;
	QLineEdit* amplitudeEdit;
	QLineEdit* frequencyEdit;
	QPushButton* createWaveButton;

private slots:
	void styleButton(QPushButton* button);
	void styleGroupBox(QGroupBox* groupBox);
};
