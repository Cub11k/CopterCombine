#include "magnetometer.h"

void copyMagnetometer(Magnetometer *dest, Magnetometer src)
{
    copyDate(&(dest->date), src.date);
    dest->type = src.type;
    dest->field = src.field;
    dest->qmc = src.qmc;
    dest->st = src.st;
}

long long approxMvs(Magnetometer buf1, Magnetometer buf2, Date date)
{
    // date not in the interval
    if (compareDate(buf1.date, date) > 0 || compareDate(buf2.date, date) < 0) {
        return -1;
    }
    // date is equal to left end of the interval
    if (compareDate(buf1.date, date) == 0) {
        return buf1.field;
    }
    // date is equal to right end of the interval
    if (compareDate(buf2.date, date) == 0) {
        return buf2.field;
    }

    // length of the interval
    long long len = 0;
    len += buf2.date.sec - buf1.date.sec;
    // length between left end of the interval and date
    long long len1 = 0;
    len1 += date.sec - buf1.date.sec;
    long long mvs = buf1.field + (buf2.field - buf1.field) * len1 / len;
    return mvs;
}

enum Error readMagnetometerLine(FILE *input, Magnetometer *buf, enum Bool *bufEOF)
{
    if (!input) {
        return NOT_OPENED;
    }
    if (!buf) {
        return NO_BUF;
    }
    if (fscanf(input, "%lld %d %d %d.%d.%d %d:%d:%d%s",
               &(buf->field), &(buf->qmc), &(buf->st),
               &(buf->date.month), &(buf->date.day), &(buf->date.year),
               &(buf->date.hour), &(buf->date.min), &(buf->date.sec), buf->date.msec) != 10) {
        *bufEOF = TRUE;
        return OK;
    }
    // convert year format YY to YYYY
    buf->date.year += 2000;
    // check if date is valid
    errorHandler(validDate(buf->date));
    return OK;
}