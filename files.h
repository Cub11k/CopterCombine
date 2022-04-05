#pragma once
#ifndef COPTER_FILES_H
#define COPTER_FILES_H

#include <stdio.h>
#include "structures.h"
#include "enums.h"

enum Error openFiles(int cnt, char *files[], FILE **mvs, FILE **magnet, FILE **copter, FILE **out);
enum Error skipComments(FILE *mvs, FILE *magnet, FILE *copter);
enum Error createHeader(FILE *output);
enum Error writeLine(FILE *output, long long mvs, Magnetometer *magnet, Copter *copter);
void closeFiles(FILE *mvs, FILE *magnet, FILE *copter, FILE *output);

#endif //COPTER_FILES_H
