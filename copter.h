#pragma once
#ifndef COPTER_COPTER_H
#define COPTER_COPTER_H

#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "enums.h"
#include "error.h"
#include "date.h"


void copyCopter(Copter *dest, Copter src);
enum Error readCopterLine(FILE *input, Copter *buf, enum Bool *bufEOF);

#endif //COPTER_COPTER_H
