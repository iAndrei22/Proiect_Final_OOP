#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <QPainter>
#include <QPaintEvent>
#include <QThread>
#include <QWidget>
#include "WaveException.h"

class Wave {
public:
	virtual double calculateAmplitude(double radians) const = 0;
	virtual Wave* clone() const = 0;
	virtual ~Wave() = default;
};
