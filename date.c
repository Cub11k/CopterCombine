#include "date.h"

enum Error validDate(Date buf)
{
    // check hour
    if (buf.hour < 0 || buf.hour > 23) {
        return INVALID_HOUR;
    }
    // check minute
    if (buf.min < 0 || buf.min > 59) {
        return INVALID_MIN;
    }
    // check second
    if (buf.sec < 0 || buf.sec > 59) {
        return INVALID_SEC;
    }
    //check month
    if (buf.month >= 1 && buf.month <= 12) {
        //check days
        if ((buf.day >= 1 && buf.day <= 31) &&
            (buf.month == 1 || buf.month == 3 || buf.month == 5 || buf.month == 7 ||
             buf.month == 8 || buf.month == 10 || buf.month == 12)) {
            return OK;
        } else if ((buf.day >= 1 && buf.day <= 30) &&
                   (buf.month == 4 || buf.month == 6 || buf.month == 9 || buf.month == 11)) {
            return OK;
        } else if ((buf.day >= 1 && buf.day <= 28) && (buf.month == 2)) {
            return OK;
        } else if (buf.day == 29 && buf.month == 2 &&
                   (buf.year % 400 == 0 || (buf.year % 4 == 0 && buf.year % 100 != 0))) {
            return OK;
        } else {
            return INVALID_DAY;
        }
    } else {
        return INVALID_MONTH;
    }
}

int compareDate(Date first, Date second)
{
    // compare year
    if (first.year - second.year) {
        return first.year - second.year;
    }
    // compare month
    if (first.month - second.month) {
        return first.month - second.month;
    }
    // compare day
    if (first.day - second.day) {
        return first.day - second.day;
    }
    // compare hour
    if (first.hour - second.hour) {
        return first.hour - second.hour;
    }
    // compare minute
    if (first.min - second.min) {
        return first.min - second.min;
    }
    // compare seconds
    return first.sec - second.sec;
}

void copyDate(Date *dest, Date src)
{
    dest->day = src.day;
    dest->month = src.month;
    dest->year = src.year;
    dest->hour = src.hour;
    dest->min = src.min;
    dest->sec = src.sec;
    strncpy(dest->msec, src.msec, 4);
}

enum Error checkStart(Date mvs, Date magnet, Date copter)
{
    // mvs after copter
    if (compareDate(mvs, copter) >= 0) {
        return MVS_START_ERROR;
    }
    // magnetometer after copter
    if (compareDate(magnet, copter) >= 0) {
        return MAGNET_START_ERROR;
    }
    return OK;
}

enum Error checkEnd(Date mvs, Date magnet, Date copter)
{
    // mvs before copter
    if (compareDate(mvs, copter) <= 0) {
        return MVS_END_ERROR;
    }
    // magnetometer before copter
    if (compareDate(magnet, copter) <= 0) {
        return MAGNET_END_ERROR;
    }
    return OK;
}

void printStartEnd(Date mvsStart, Date mvsEnd, Date magnetStart, Date magnetEnd,
                   Date copterStart, Date copterEnd)
{
    // print sorted start dates
    if (compareDate(mvsStart, magnetStart) < 0) {
        printf("%02d.%02d.%04d %02d:%02d:%02d%.3s : MVS Station started recording\n",
               mvsStart.day, mvsStart.month, mvsStart.year,
               mvsStart.hour, mvsStart.min, mvsStart.sec, mvsStart.msec);
        printf("%02d.%02d.%04d %02d:%02d:%02d%.3s : Magnetometer started recording\n",
               magnetStart.day, magnetStart.month, magnetStart.year,
               magnetStart.hour, magnetStart.min, magnetStart.sec, magnetStart.msec);
    } else {
        printf("%02d.%02d.%04d %02d:%02d:%02d%.3s : Magnetometer started recording\n",
               magnetStart.day, magnetStart.month, magnetStart.year,
               magnetStart.hour, magnetStart.min, magnetStart.sec, magnetStart.msec);
        printf("%02d.%02d.%04d %02d:%02d:%02d%.3s : MVS Station started recording\n",
               mvsStart.day, mvsStart.month, mvsStart.year,
               mvsStart.hour, mvsStart.min, mvsStart.sec, mvsStart.msec);
    }
    printf("%02d.%02d.%04d %02d:%02d:%02d%.3s : Copter started recording\n",
           copterStart.day, copterStart.month, copterStart.year,
           copterStart.hour, copterStart.min, copterStart.sec, copterStart.msec);

    printf("\n");

    // print sorted finish dates
    printf("%02d.%02d.%04d %02d:%02d:%02d%.3s : Copter finished recording\n",
           copterEnd.day, copterEnd.month, copterEnd.year,
           copterEnd.hour, copterEnd.min, copterEnd.sec, copterEnd.msec);
    if (compareDate(mvsEnd, magnetEnd) < 0) {
        printf("%02d.%02d.%04d %02d:%02d:%02d%.3s : MVS Station finished recording\n",
               mvsEnd.day, mvsEnd.month, mvsEnd.year,
               mvsEnd.hour, mvsEnd.min, mvsEnd.sec, mvsEnd.msec);
        printf("%02d.%02d.%04d %02d:%02d:%02d%.3s : Magnetometer finished recording\n",
               magnetEnd.day, magnetEnd.month, magnetEnd.year,
               magnetEnd.hour, magnetEnd.min, magnetEnd.sec, magnetEnd.msec);
    } else {
        printf("%02d.%02d.%04d %02d:%02d:%02d%.3s : Magnetometer finished recording\n",
               magnetEnd.day, magnetEnd.month, magnetEnd.year,
               magnetEnd.hour, magnetEnd.min, magnetEnd.sec, magnetEnd.msec);
        printf("%02d.%02d.%04d %02d:%02d:%02d%.3s : MVS Station finished recording\n",
               mvsEnd.day, mvsEnd.month, mvsEnd.year,
               mvsEnd.hour, mvsEnd.min, mvsEnd.sec, mvsEnd.msec);
    }
}