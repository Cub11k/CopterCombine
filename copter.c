#include "copter.h"

void copyCopter(Copter *dest, Copter src)
{
    copyDate(&(dest->date), src.date);
    for (int i = 0; i < 9; ++i) {
        strncpy(dest->values[i], src.values[i], 16);
    }
}

enum Error readCopterLine(FILE *input, Copter *buf, enum Bool *bufEOF)
{
    if (!input) {
        return NOT_OPENED;
    }
    if (!buf) {
        return NO_BUF;
    }
    if (fscanf(input, "%d.%d.%d,%d:%d:%d,",
               &(buf->date.day), &(buf->date.month), &(buf->date.year),
               &(buf->date.hour), &(buf->date.min), &(buf->date.sec)) != 6) {
        *bufEOF = TRUE;
        return OK;
    }
    // check if date is valid
    errorHandler(validDate(buf->date));

    // get rest of the line with 9 values
    char line[1001] = {0};
    if (fscanf(input, "%1000s", line) != 1) {
        return READ_ERROR;
    }
    char *position = line;
    char *delimeter = NULL;
    for (int i = 0; i < 9; ++i) {
        // find first comma
        delimeter = strchr(position, ',');
        // if not found -> last value or read error
        if (!delimeter) {
            if (i != 8) {
                return READ_ERROR;
            } else {
                snprintf(buf->values[i], 16, "%.15s", position);
            }
        } else {
            strncpy(buf->values[i], position, delimeter - position);
            position = delimeter + 1;
        }
    }
    return OK;
}