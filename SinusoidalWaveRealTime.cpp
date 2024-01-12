#include "SinusoidalWaveRealTime.h"

// Definition of the static variable waveCount
template <typename T>
int SinusoidalWaveRealTime<T>::waveCount = 0;

// Constructor pentru copierea atributelor din altă instanță SinusoidalWaveRealTime
template <typename T>
SinusoidalWaveRealTime<T>::SinusoidalWaveRealTime(const SinusoidalWaveRealTime& other)
	: QWidget(other.parentWidget()), frequency(other.frequency), amplitude(other.amplitude),
	iWidth(other.iWidth), iHeight(other.iHeight),
	step(other.step), offset(other.offset), points(other.points) {}

//why is it giving linking error without them :(
template <>
SinusoidalWaveRealTime<double>::SinusoidalWaveRealTime(double frequency, double amplitude, QWidget* parent)
	: QWidget(parent), frequency(frequency), amplitude(amplitude), step(1), offset(0) {
	if (frequency < 0.0)
		throw InvalidFrequencyException();
	if (frequency == 0.0 || amplitude == 0.0)
		throw WaveException();
	SinusoidalWaveRealTime::waveCount++;
	iWidth = this->width();
	iHeight = this->height();
	// Calculate and store points for the waveform
	for (int x = 0; x < iWidth; x += step) {
		double radian = qDegreesToRadians(x * 360.0 / iWidth);
		double y = iHeight / 2 - qSin(radian * frequency) * iHeight / 4 * amplitude;
		points.push_back(QPoint(x, y));
	}
}

template <>
SinusoidalWaveRealTime<int>::SinusoidalWaveRealTime(int frequency, int amplitude, QWidget* parent)
	: QWidget(parent), frequency(frequency), amplitude(amplitude), step(1), offset(0) {
	if (frequency < 0)
		throw InvalidFrequencyException();
	if (frequency == 0 || amplitude == 0)
		throw WaveException();

	SinusoidalWaveRealTime::waveCount++;
	iWidth = this->width();
	iHeight = this->height();
	// Calculate and store points for the waveform
	for (int x = 0; x < iWidth; x += step) {
		double radian = qDegreesToRadians(x * 360.0 / iWidth);
		double y = iHeight / 2 - qSin(radian * frequency) * iHeight / 4 * amplitude;
		points.push_back(QPoint(x, y));
	}
}

// Constructor pentru crearea unei noi instanțe SinusoidalWaveRealTime cu parametrii specificați
template <typename T>
SinusoidalWaveRealTime<T>::SinusoidalWaveRealTime(T frequency, T amplitude, QWidget* parent)
	: QWidget(parent), frequency(frequency), amplitude(amplitude), step(1), offset(0) {
	if (frequency < T(0.0))
		throw InvalidFrequencyException();
	if (frequency == T(0.0) || amplitude == T(0.0))
		throw WaveException();

	SinusoidalWaveRealTime::waveCount++;
	iWidth = this->width();
	iHeight = this->height();
	// Calculate and store points for the waveform
	for (int x = 0; x < iWidth; x += step) {
		double radian = qDegreesToRadians(static_cast<double>(x) * 360.0 / iWidth);
		double y = iHeight / 2 - qSin(radian * static_cast<double>(frequency)) * iHeight / 4 * static_cast<double>(amplitude);
		points.push_back(QPoint(x, y));
	}
}

// Calculate the amplitude of the waveform at a given angle in radians
template <typename T>
T SinusoidalWaveRealTime<T>::calculateAmplitude(T radians) const {
	return amplitude * std::sin(static_cast<double>(radians) * frequency);
}

// Clone the current instance (create a new instance with the same attributes)
template <typename T>
SinusoidalWaveRealTime<T>* SinusoidalWaveRealTime<T>::clone() const {
	return new SinusoidalWaveRealTime<T>(*this);
}

// Event handler for painting the waveform on the widget
template <typename T>
void SinusoidalWaveRealTime<T>::paintEvent(QPaintEvent* event) {
	QPainter painter(this);

	// Set rendering options
	painter.setRenderHint(QPainter::Antialiasing, true);
	// Fill the background with white
	painter.fillRect(rect(), Qt::white);
	drawGrid(painter);  // Draw grid
	drawAxes(painter);  // Draw axes
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
template <typename T>
void SinusoidalWaveRealTime<T>::updateWavePoints() {
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

template <typename T>
void SinusoidalWaveRealTime<T>::drawGrid(QPainter& painter) {
	painter.setPen(QPen(Qt::lightGray, 1, Qt::DashLine));
	for (int y = 0; y < iHeight; y += iHeight / 4) {
		painter.drawLine(0, y, iWidth, y);
	}
	for (int x = 0; x < iWidth; x += iWidth / 10) {
		painter.drawLine(x, 0, x, iHeight);
	}
}

template <typename T>
void SinusoidalWaveRealTime<T>::drawAxes(QPainter& painter) {
	painter.setPen(QPen(Qt::black, 2));
	painter.drawLine(0, iHeight / 2, iWidth, iHeight / 2);
	painter.drawLine(iWidth / 2, 0, iWidth / 2, iHeight);
}

// Sleep for one second (used for animation delay)
template <typename T>
void SinusoidalWaveRealTime<T>::sleepOneSec() {
	QThread::sleep(1);
}

// Operator de atribuire pentru asignarea atributelor dintr-o altă instanță SinusoidalWaveRealTime
template <typename T>
SinusoidalWaveRealTime<T>& SinusoidalWaveRealTime<T>::operator=(const SinusoidalWaveRealTime& other) {
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