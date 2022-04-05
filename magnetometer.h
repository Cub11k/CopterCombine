#pragma once
#ifndef COPTER_MAGNETOMETER_H
#define COPTER_MAGNETOMETER_H

#include <stdio.h>
#include "structures.h"
#include "enums.h"
#include "date.h"
#include "error.h"

void copyMagnetometer(Magnetometer *dest, Magnetometer src);
long long approxMvs(Magnetometer buf1, Magnetometer buf2, Date date);
enum Error readMagnetometerLine(FILE *input, Magnetometer *buf, enum Bool *bufEOF);

#endif //COPTER_MAGNETOMETER_H
