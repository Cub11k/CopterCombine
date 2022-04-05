#ifndef COPTER_STRUCTURES_H
#define COPTER_STRUCTURES_H

typedef struct Date
{
    int day;
    int month;
    int year;
    int hour;
    int min;
    int sec;
    char msec[4];
} Date;

typedef struct Magnetometer
{
    enum Types
    {
        MVS, MAGNETOMETER
    } type;
    long long field;
    int qmc;
    int st;
    Date date;
} Magnetometer;

typedef struct Copter
{
    Date date;
    // LAt, Lng, AltAmsl, AltRel, Baro, Roll, Pitch, Yaw, Bat
    char values[9][16];
} Copter;

#endif //COPTER_STRUCTURES_H
