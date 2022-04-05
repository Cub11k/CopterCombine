#pragma once
#ifndef COPTER_DATE_H
#define COPTER_DATE_H

#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "enums.h"

enum Error validDate(Date buf);
int compareDate(Date first, Date second);
void copyDate(Date *dest, Date src);
enum Error checkStart(Date mvs, Date magnet, Date copter);
enum Error checkEnd(Date mvs, Date magnet, Date copter);
void printStartEnd(Date mvsStart, Date mvsEnd, Date magnetStart, Date magnetEnd,
                   Date copterStart, Date copterEnd);

#endif //COPTER_DATE_H
