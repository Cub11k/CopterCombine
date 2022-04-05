C_COMPILER = gcc
OBJECTS = error.o files.o date.o magnetometer.o copter.o
HEADERS = structures.h enums.h
FLAGS = -Wall -Werror -O2
RESULT = combine

COMBINE_SOURCE = combine.c
Combine: $(COMBINE_SOURCE) $(HEADERS) $(OBJECTS)
	$(C_COMPILER) $(OBJECTS) $(COMBINE_SOURCE) -o $(RESULT) $(FLAGS)

ERROR_HEADERS = error.h
ERROR_SOURCE = error.c
error.o: $(ERROR_SOURCE) $(ERROR_HEADERS) $(HEADERS)
	$(C_COMPILER) -c $(ERROR_SOURCE) -o error.o $(FLAGS)

FILES_HEADERS = files.h
FILES_SOURCE = files.c
files.o: $(FILES_SOURCE) $(FILES_HEADERS) $(HEADERS)
	$(C_COMPILER) -c $(FILES_SOURCE) -o files.o $(FLAGS)

DATE_HEADERS = date.h
DATE_SOURCE = date.c
date.o: $(DATE_SOURCE) $(DATE_HEADERS) $(HEADERS)
	$(C_COMPILER) -c $(DATE_SOURCE) -o date.o $(FLAGS)

MAGNETOMETER_HEADERS = magnetometer.h
MAGNETOMETER_SOURCE = magnetometer.c
magnetometer.o: $(MAGNETOMETER_SOURCE) $(MAGNETOMETER_HEADERS) $(HEADERS)
	$(C_COMPILER) -c $(MAGNETOMETER_SOURCE) -o magnetometer.o $(FLAGS)

COPTER_HEADERS = copter.h
COPTER_SOURCE = copter.c
copter.o: $(COPTER_SOURCE) $(COPTER_HEADERS) $(HEADERS)
	$(C_COMPILER) -c $(COPTER_SOURCE) -o copter.o $(FLAGS)

.PHONY: clean
clean:
	rm $(OBJECTS) $(RESULT)