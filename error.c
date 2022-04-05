#include "error.h"

void errorHandler(enum Error err)
{
    switch (err) {
        case NO_FILES:
            printf("Not enough files provided. Aborting with code %d.\n", NO_FILES);
            exit(NO_FILES);
        case NO_OUTPUT:
            printf("No name for output file provided. Aborting with code %d.\n", NO_OUTPUT);
            exit(NO_OUTPUT);
        case TOO_MANY_ARGS:
            printf("Too many arguments passed. Aborting with code %d.\n", TOO_MANY_ARGS);
            exit(TOO_MANY_ARGS);
        case CANT_OPEN_MVS:
            printf("MVS station input file can't be opened. ");
            printf("Aborting with code %d.\n", CANT_OPEN_MVS);
            exit(CANT_OPEN_MVS);
        case CANT_OPEN_MAGNET:
            printf("Magnetometer input file can't be opened. ");
            printf("Aborting with code %d.\n", CANT_OPEN_MAGNET);
            exit(CANT_OPEN_MAGNET);
        case CANT_OPEN_COPTER:
            printf("Copter input file can't be opened. ");
            printf("Aborting with code %d.\n", CANT_OPEN_COPTER);
            exit(CANT_OPEN_COPTER);
        case CANT_OPEN_OUTPUT:
            printf("Output file can't be opened. ");
            printf("Aborting with code %d.\n", CANT_OPEN_OUTPUT);
            exit(CANT_OPEN_OUTPUT);
        case NOT_OPENED:
            printf("One of files is not opened. Aborting with code %d.\n", NOT_OPENED);
            exit(NOT_OPENED);
        case NO_BUF:
            printf("No buffer provided to store information. ");
            printf("Aborting with code %d.\n", NO_BUF);
            exit(NO_BUF);
        case READ_ERROR:
            printf("An error occurred while reading. Aborting with code %d.\n", READ_ERROR);
            exit(READ_ERROR);
        case WRITE_ERROR:
            printf("An error occurred while writing. Aborting with code %d.\n", WRITE_ERROR);
            exit(WRITE_ERROR);
        case NO_VALUES:
            printf("No values provided in one of input files. ");
            printf("Aborting with code %d.\n", NO_VALUES);
            exit(NO_VALUES);
        case INVALID_SEC:
            printf("Invalid second in the time. Aborting with code %d.\n", INVALID_SEC);
            exit(INVALID_SEC);
        case INVALID_MIN:
            printf("Invalid minute in the time. Aborting with code %d.\n", INVALID_MIN);
            exit(INVALID_MIN);
        case INVALID_HOUR:
            printf("Invalid hour in the time. Aborting with code %d.\n", INVALID_HOUR);
            exit(INVALID_HOUR);
        case INVALID_DAY:
            printf("Invalid day in the date. Aborting with code %d.\n", INVALID_DAY);
            exit(INVALID_DAY);
        case INVALID_MONTH:
            printf("Invalid month in the date. Aborting with code %d.\n", INVALID_MONTH);
            exit(INVALID_MONTH);
        case MVS_START_ERROR:
            printf("MVS Station started recording after Copter's takeoff. ");
            printf("Aborting with code %d.\n", MVS_START_ERROR);
            exit(MVS_START_ERROR);
        case MAGNET_START_ERROR:
            printf("Magnetometer started recording after Copter's takeoff. ");
            printf("Aborting with code %d.\n", MAGNET_START_ERROR);
            exit(MAGNET_START_ERROR);
        case MVS_END_ERROR:
            printf("MVS Station finished recording before Copter's landing. ");
            printf("Aborting with code %d.\n", MVS_END_ERROR);
            exit(MVS_END_ERROR);
        case MAGNET_END_ERROR:
            printf("Magnetometer finished recording before Copter's landing. ");
            printf("Aborting with code %d.\n", MAGNET_END_ERROR);
            exit(MAGNET_END_ERROR);
        default:
            return;
    }
}
