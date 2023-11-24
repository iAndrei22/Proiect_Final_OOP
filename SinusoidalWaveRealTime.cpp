#include "SinusoidalWaveRealTime.h"

// Constructor for copying the attributes from another SinusoidalWaveRealTime instance
SinusoidalWaveRealTime::SinusoidalWaveRealTime(const SinusoidalWaveRealTime& other)
	: QWidget(other.parentWidget()), frequency(other.frequency), amplitude(other.amplitude),
	iWidth(other.iWidth), iHeight(other.iHeight),
	step(other.step), offset(other.offset), points(other.points) {}

// Constructor for creating a new SinusoidalWaveRealTime instance with given parameters
SinusoidalWaveRealTime::SinusoidalWaveRealTime(double frequency, double amplitude, QWidget* parent)
	: QWidget(parent), frequency(frequency), amplitude(amplitude), step(1), offset(0) {
	if (frequency < 0.0)
		throw InvalidFrequencyException();
	if (frequency == 0.0 || amplitude == 0.0)
		throw WaveException();

	iWidth = this->width();
	iHeight = this->height();
	// Calculate and store points for the waveform
	for (int x = 0; x < iWidth; x += step) {
		double radian = qDegreesToRadians(x * 360.0 / iWidth);
		double y = iHeight / 2 - qSin(radian * frequency) * iHeight / 4 * amplitude;
		points.push_back(QPoint(x, y));
	}
}

// Calculate the amplitude of the waveform at a given angle in radians
double SinusoidalWaveRealTime::calculateAmplitude(double radians) const {
	return amplitude * std::sin(radians * frequency);
}

// Clone the current instance (create a new instance with the same attributes)
SinusoidalWaveRealTime* SinusoidalWaveRealTime::clone() const {
	return new SinusoidalWaveRealTime(*this);
}

// Event handler for painting the waveform
void SinusoidalWaveRealTime::paintEvent(QPaintEvent* event) {
	QPainter painter(this);

	// Set rendering options
	painter.setRenderHint(QPainter::Antialiasing, true);
	// Fill the background with white
	painter.fillRect(rect(), Qt::white);
	// Set the pen color to blue
	painter.setPen(Qt::blue);

	// Convert points to QPolygonF for drawing
	QPolygonF poly;
	for (const auto& point : points) {
		poly << QPointF(point.x(), point.y());
	}

	// Draw the waveform
	painter.drawPolyline(poly);

	// Trigger a paint event for continuous updating
	this->update();
	// Update the waveform points
	updateWavePoints();
}

// Update the waveform points based on the current offset
void SinusoidalWaveRealTime::updateWavePoints() {
	iWidth = this->width();
	iHeight = this->height();
	points.clear();
	// Recalculate and store points for the waveform with updated offset
	for (int x = 0; x < iWidth; x += step) {
		double radian = qDegreesToRadians((x + offset) * 360.0 / iWidth);
		double y = iHeight / 2 - qSin(radian * frequency) * iHeight / 4 * amplitude;
		points.push_back(QPoint(x, y));
	}
	// Increment or reset the offset for animation
	if (offset < iWidth)
		offset++;
	else
		offset = 0;
}

// Sleep for one second (used for animation delay)
void SinusoidalWaveRealTime::sleepOneSec() {
	QThread::sleep(1);
}

SinusoidalWaveRealTime& SinusoidalWaveRealTime::operator=(const SinusoidalWaveRealTime& other)
{
	if (this != &other) {  // Avoid self-assignment
		// Copy attributes from the other instance
		frequency = other.frequency;
		amplitude = other.amplitude;
		iWidth = other.iWidth;
		iHeight = other.iHeight;
		step = other.step;
		offset = other.offset;
		points = other.points;
	}
	return *this;
}