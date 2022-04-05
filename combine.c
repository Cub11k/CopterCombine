#include "structures.h"
#include "enums.h"
#include "files.h"
#include "error.h"
#include "date.h"
#include "copter.h"
#include "magnetometer.h"

void Combine(int argc, char *argv[]) {
    // input and output streams
    FILE *mvsStation = NULL;
    FILE *magnetometer = NULL;
    FILE *copter = NULL;
    FILE *output = NULL;
    errorHandler(openFiles(argc, argv, &mvsStation, &magnetometer, &copter, &output));

    // skip comments in files
    errorHandler(skipComments(mvsStation, magnetometer, copter));

    // buffers to store information
    Magnetometer mvsBufFirst = {.type = MVS};
    Magnetometer mvsBufSecond = {.type = MVS};
    Magnetometer magnetBuf = {.type = MAGNETOMETER};
    Copter copterBuf = {.values = {{0},
                                   {0},
                                   {0},
                                   {0},
                                   {0},
                                   {0},
                                   {0},
                                   {0},
                                   {0}}};

    enum Bool mvsEOF = FALSE;
    enum Bool magnetEOF = FALSE;
    enum Bool copterEOF = FALSE;

    // get first records from each File
    errorHandler(readMagnetometerLine(mvsStation, &mvsBufFirst, &mvsEOF));
    errorHandler(readMagnetometerLine(mvsStation, &mvsBufSecond, &mvsEOF));
    errorHandler(readMagnetometerLine(magnetometer, &magnetBuf, &magnetEOF));
    errorHandler(readCopterLine(copter, &copterBuf, &copterEOF));

    // buffers to store start dates
    Date mvsStart;
    copyDate(&mvsStart, mvsBufFirst.date);
    Date magnetStart;
    copyDate(&magnetStart, magnetBuf.date);
    Date copterStart;
    copyDate(&copterStart, copterBuf.date);

    // check recording start
    errorHandler(checkStart(mvsStart, magnetStart, copterStart));

    // create header of the file
    errorHandler(createHeader(output));

    // skip mvs without magnetometer data provided
    while (!mvsEOF && compareDate(mvsBufSecond.date, magnetBuf.date) < 0) {
        copyMagnetometer(&mvsBufFirst, mvsBufSecond);
        errorHandler(readMagnetometerLine(mvsStation, &mvsBufSecond, &mvsEOF));
    }

    // write data from magnetometer and mvs until copter's take-off
    long long mvs = -1;
    while (!magnetEOF && compareDate(magnetBuf.date, copterBuf.date) < 0) {
        if (!mvsEOF) {
            mvs = approxMvs(mvsBufFirst, mvsBufSecond, magnetBuf.date);
        }
        errorHandler(writeLine(output, mvs, &magnetBuf, NULL));
        errorHandler(readMagnetometerLine(magnetometer, &magnetBuf, &magnetEOF));
        if (compareDate(magnetBuf.date, mvsBufSecond.date) > 0) {
            copyMagnetometer(&mvsBufFirst, mvsBufSecond);
            errorHandler(readMagnetometerLine(mvsStation, &mvsBufSecond, &mvsEOF));
        }
    }

    // write data from mvs, magnetometer and copter until copter's landing
    mvs = -1;
    while (!magnetEOF && !copterEOF) {
        if (!mvsEOF) {
            mvs = approxMvs(mvsBufFirst, mvsBufSecond, magnetBuf.date);
        }
        errorHandler(writeLine(output, mvs, &magnetBuf, &copterBuf));
        errorHandler(readCopterLine(copter, &copterBuf, &copterEOF));
        if (compareDate(copterBuf.date, magnetBuf.date) > 0) {
            errorHandler(readMagnetometerLine(magnetometer, &magnetBuf, &magnetEOF));
        }
        if (compareDate(magnetBuf.date, mvsBufSecond.date) > 0) {
            copyMagnetometer(&mvsBufFirst, mvsBufSecond);
            errorHandler(readMagnetometerLine(mvsStation, &mvsBufSecond, &mvsEOF));
        }
    }

    // write data from mvs and magnetometer until magnetometer finish recording
    mvs = -1;
    while (!magnetEOF) {
        if (!mvsEOF) {
            mvs = approxMvs(mvsBufFirst, mvsBufSecond, magnetBuf.date);
        }
        errorHandler(writeLine(output, mvs, &magnetBuf, NULL));
        errorHandler(readMagnetometerLine(magnetometer, &magnetBuf, &magnetEOF));
        if (compareDate(magnetBuf.date, mvsBufSecond.date) > 0) {
            copyMagnetometer(&mvsBufFirst, mvsBufSecond);
            errorHandler(readMagnetometerLine(mvsStation, &mvsBufSecond, &mvsEOF));
        }
    }

    // skip all mvs to find finish date
    while (!mvsEOF) {
        copyMagnetometer(&mvsBufFirst, mvsBufSecond);
        errorHandler(readMagnetometerLine(mvsStation, &mvsBufSecond, &mvsEOF));
    }

    // buffers to store end dates
    Date mvsEnd;
    copyDate(&mvsEnd, mvsBufSecond.date);
    Date magnetEnd;
    copyDate(&magnetEnd, magnetBuf.date);
    Date copterEnd;
    copyDate(&copterEnd, copterBuf.date);

    // check recording end
    errorHandler(checkEnd(mvsEnd, magnetEnd, copterEnd));

    // print start date and finish date to console
    printStartEnd(mvsStart, mvsEnd, magnetStart, magnetEnd, copterStart, copterEnd);

    closeFiles(mvsStation, magnetometer, copter, output);
}

int main(int argc, char *argv[])
{
    Combine(argc, argv);
    return 0;
}