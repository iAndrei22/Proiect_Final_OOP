#pragma once

#include <QWidget>
#include <cmath>
#include "Wave.h"
#include "InvalidFrequencyException.h"
#include "WaveException.h"
#include "SinusoidalWaveFactory.h"

class SinusoidalWaveFactory;

// Class representing a real-time sinusoidal waveform displayed in a QWidget
template <typename T>
class SinusoidalWaveRealTime : public QWidget, public Wave {
private:
	T frequency;          // Frequency of the sinusoidal waveform
	T amplitude;          // Amplitude of the sinusoidal waveform
	int iWidth;                // Width of the widget
	int iHeight;               // Height of the widget
	int step;                  // Step for calculating points in the waveform
	int offset;                // Offset for animation effect
	std::vector<QPoint> points; // Vector to store calculated points of the waveform

public:
	// Static variable to keep track of the number of instances created
	static int waveCount;

	// Constructor for copying attributes from another SinusoidalWaveRealTime instance
	SinusoidalWaveRealTime(const SinusoidalWaveRealTime& other);

	// Constructor for creating a new SinusoidalWaveRealTime instance with given parameters
	SinusoidalWaveRealTime(T frequency, T amplitude, QWidget* parent = nullptr);

	// Calculate the amplitude of the waveform at a given angle in radians
	T calculateAmplitude(T radians) const;

	// Clone the current instance (create a new instance with the same attributes)
	virtual SinusoidalWaveRealTime* clone() const override;

	// Event handler for painting the waveform on the widget
	void paintEvent(QPaintEvent* event) override;

	void drawGrid(QPainter& painter);
	void drawAxes(QPainter& painter);

	// Update the waveform points based on the current offset
	void updateWavePoints();

	// Sleep for one second (used for animation delay)
	void sleepOneSec();

	static SinusoidalWaveFactory* getFactory();

	SinusoidalWaveRealTime& operator=(const SinusoidalWaveRealTime& other);
	//public slots:
	//	// Slot for handling amplitude changes
	//	void setAmplitude(double newAmplitude);
	//
	//	// Slot for handling frequency changes
	//	void setFrequency(double newFrequency);
};