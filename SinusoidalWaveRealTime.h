#pragma once

#include <QWidget>
#include <cmath>
#include "Wave.h"
#include "InvalidFrequencyException.h"
#include "WaveException.h"
// Class representing a real-time sinusoidal waveform displayed in a QWidget
class SinusoidalWaveRealTime : public QWidget, public Wave {
private:
	double frequency;          // Frequency of the sinusoidal waveform
	double amplitude;          // Amplitude of the sinusoidal waveform
	int iWidth;                // Width of the widget
	int iHeight;               // Height of the widget
	int step;                  // Step for calculating points in the waveform
	int offset;                // Offset for animation effect
	std::vector<QPoint> points; // Vector to store calculated points of the waveform

public:
	// Constructor for copying attributes from another SinusoidalWaveRealTime instance
	SinusoidalWaveRealTime(const SinusoidalWaveRealTime& other);

	// Constructor for creating a new SinusoidalWaveRealTime instance with given parameters
	SinusoidalWaveRealTime(double frequency, double amplitude, QWidget* parent = nullptr);

	// Calculate the amplitude of the waveform at a given angle in radians
	virtual double calculateAmplitude(double radians) const override;

	// Clone the current instance (create a new instance with the same attributes)
	virtual SinusoidalWaveRealTime* clone() const override;

	// Event handler for painting the waveform on the widget
	void paintEvent(QPaintEvent* event) override;

	// Update the waveform points based on the current offset
	void updateWavePoints();

	// Sleep for one second (used for animation delay)
	void sleepOneSec();
};
