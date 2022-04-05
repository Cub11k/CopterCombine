#include "files.h"

enum Error openFiles(int cnt, char *files[], FILE **mvs, FILE **magnet, FILE **copter, FILE **out)
{
    // less than 3 args
    if (cnt < 4) {
        return NO_FILES;
    }
    if (cnt < 5) {
        return NO_OUTPUT;
    }
    if (cnt > 5) {
        return TOO_MANY_ARGS;
    }

    if (*mvs) {
        fclose(*mvs);
    }
    *mvs = fopen(files[1], "r");
    if (!(*mvs)) {
        return CANT_OPEN_MVS;
    }

    if (*magnet) {
        fclose(*magnet);
    }
    *magnet = fopen(files[2], "r");
    if (!(*magnet)) {
        return CANT_OPEN_MAGNET;
    }

    if (*copter) {
        fclose(*copter);
    }
    *copter = fopen(files[3], "r");
    if (!(*copter)) {
        return CANT_OPEN_COPTER;
    }

    if (*out) {
        fclose(*out);
    }
    *out = fopen(files[4], "w");
    if (!(*out)) {
        return CANT_OPEN_OUTPUT;
    }
    return OK;
}

enum Error skipComments(FILE *mvs, FILE *magnet, FILE *copter)
{
    // skip lines starting with ';' in mvs file
    int c;
    while ((c = fgetc(mvs)) == ';') {
        char trash[10000];
        if (fgets(trash, 10000, mvs) == NULL) {
            return NO_VALUES;
        }
    }
    if (c == EOF) {
        return NO_VALUES;
    }
    fseek(mvs, -1, SEEK_CUR);

    // skip lines starting with ';' in magnetometer file
    while ((c = fgetc(magnet)) == ';') {
        char trash[10000];
        if (fgets(trash, 10000, magnet) == NULL) {
            return NO_VALUES;
        }
    }
    if (c == EOF) {
        return NO_VALUES;
    }
    fseek(magnet, -1, SEEK_CUR);

    // skip all non-numerical values in copter file
    while (((c = fgetc(copter)) < '0' || c > '9') && c != EOF) {
        char trash[10000];
        if (fgets(trash, 10000, copter) == NULL) {
            return NO_VALUES;
        }
    }
    if (c == EOF) {
        return NO_VALUES;
    }
    fseek(copter, -1, SEEK_CUR);
    return OK;
}

enum Error createHeader(FILE *output)
{
    if (fprintf(output, "%*s %*s %*s %s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s\n",
                8, "MVS", 8, "FIELD", 5, "QMC", "ST", 10, "DATE", 11, "TIME",
                15, "LAt", 15, "Lng", 11, "AltAmsl", 15, "AltRel", 11, "Baro",
                11, "Roll", 11, "Pitch", 11, "Yaw", 11, "Bat") != 170) {
        return WRITE_ERROR;
    }
    return OK;
}

enum Error writeLine(FILE *output, long long mvs, Magnetometer *magnet, Copter *copter)
{
    if (!output) {
        return NOT_OPENED;
    }
    if (!magnet) {
        return NO_BUF;
    }
    // actual mvs data
    if (mvs != -1) {
        if (fprintf(output, "%08lld ", mvs) != 9) {
            return WRITE_ERROR;
        }
    } else {
        // no mvs data
        fprintf(output, "-------- ");
    }
    // actual magnetometer data
    if (fprintf(output, "%08lld %05d %02d %02d.%02d.%04d %02d:%02d:%02d%.3s",
                magnet->field, magnet->qmc, magnet->st,
                magnet->date.day, magnet->date.month, magnet->date.year,
                magnet->date.hour, magnet->date.min, magnet->date.sec, magnet->date.msec) != 40) {
        return WRITE_ERROR;
    }
    // actual copter data
    if (copter) {
        if (fprintf(output, " %*s %*s %*s %*s %*s %*s %*s %*s %*s\n",
                    15, copter->values[0], 15, copter->values[1], 11, copter->values[2],
                    15, copter->values[3], 11, copter->values[4], 11, copter->values[5],
                    11, copter->values[6], 11, copter->values[7], 11, copter->values[8]) != 121) {
            return WRITE_ERROR;
        }
    } else {
        // no copter data
        fprintf(output, " --------------- --------------- ----------- ---------------");
        fprintf(output, " ----------- ----------- ----------- ----------- -----------\n");
    }
    return OK;
}

void closeFiles(FILE *mvs, FILE *magnet, FILE *copter, FILE *output)
{
    if (mvs) {
        fclose(mvs);
    }
    if (magnet) {
        fclose(magnet);
    }
    if (copter) {
        fclose(copter);
    }
    if (output) {
        fclose(output);
    }
}
