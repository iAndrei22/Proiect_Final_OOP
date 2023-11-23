#include "Wave.h"
#include <QPainter>

SinusoidalWaveRealTime::SinusoidalWaveRealTime(double frequency, double amplitude, QWidget* parent)
	: QWidget(parent), frequency(frequency), amplitude(amplitude), step(1), offset(0) {
	iWidth = this->width();
	iHeight = this->height();
	for (int x = 0; x < iWidth; x += step) {
		double radian = qDegreesToRadians(x * 360.0 / iWidth);
		double y = iHeight / 2 - qSin(radian * frequency) * iHeight / 4 * amplitude;
		points.push_back(QPoint(x, y));
	}
}

double SinusoidalWaveRealTime::calculateAmplitude(double radians) const {
	return amplitude * std::sin(radians * frequency);
}

SinusoidalWaveRealTime* SinusoidalWaveRealTime::clone() const {
	return new SinusoidalWaveRealTime(*this);
}

void SinusoidalWaveRealTime::paintEvent(QPaintEvent* event) {
	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillRect(rect(), Qt::white); // Fill the background with white
	painter.setPen(Qt::blue); // Set the pen color to blue
	QPolygonF poly;
	for (const auto& point : points) {
		poly << QPointF(point.x(), point.y());
	}

	painter.drawPolyline(poly);

	this->update();
	updateWavePoints();
}

void SinusoidalWaveRealTime::updateWavePoints() {
	iWidth = this->width();
	iHeight = this->height();
	points.clear();
	for (int x = 0; x < iWidth; x += step) {
		double radian = qDegreesToRadians((x + offset) * 360.0 / iWidth);
		double y = iHeight / 2 - qSin(radian * frequency) * iHeight / 4 * amplitude;
		points.push_back(QPoint(x, y));
	}
	if (offset < iWidth)
		offset++;
	else
		offset = 0;
}

void SinusoidalWaveRealTime::sleepOneSec() {
	QThread::sleep(1);
}