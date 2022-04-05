# CopterCombine

CopterCombine is a program in C, that combines logs from MVS station, magnetometer and copter itself

## Installation

Clone repository to your computer with git
```bash
cd /path-to-clone-to
git clone github.com/Cub1tor/CopterCombine.git
```
or Download the archive and unzip it with any tool

## Compilation

### There is a makefile, designed for the GNU make

```bash
make
# or
make Combine
```

### To remove all compiled files use:

```bash
make clean
```

## Usage

### Program accepts 4 arguments:

1. First one is the path to file with MVS station log
2. Second one is the path to file with Magnetometer log
3. Third one is the path to file with Copter log
4. Fourth one is the path to file which will contain result (will be created or overwritten)

### For example:
```bash
./combine /logs/mvs-log.txt /logs/magnetometer-log.txt /logs/copter-log.txt /logs/full-log.txt
```

## Input files format

### For MVS and Magnetometer

Comments are the first lines, starting with `;`

**Format for one line:**
- `Field -> 8 digits, double` 
- `Measurement error -> 5 digits, double`
- `Station number -> 2 digits, integer`
- `Date -> MM.DD.YY`
- `Time -> HH:MM:SS,mm`

### For Copter

Comments are the first lines without numerical digits

**Format for one line:**
- `Date -> DD.MM.YYYY`
- `Time -> HH:MM:SS`
- `9 values -> each no more than 15 digits`

## Error codes

- `0 -> All is fine`
- `1 -> Not enough input files`
- `2 -> No output file`
- `3 -> Too many arguments passed`
- `4 -> File with MVS station log can't be opened` 
- `5 -> File with Magnetometer log can't be opened`
- `6 -> File with Copter log can't be opened`
- `7 -> Output can't be opened`
- `8 -> One of the files is not opened when trying ro read`
- `9 -> No buffer provided to store data`
- `10 -> Error occurred while reading from file`
- `11 -> Error occurred while writing into file`
- `12 -> One of the files has no values inside`
- `13 -> Invalid seconds value in date`
- `14 -> Invalid minute value in date`
- `15 -> Invalid hour value in date`
- `16 -> Invalid day value in date`
- `17 -> Invalid month value in date`
- `18 -> MVS station started recording after or at the same time with copter's take-off`
- `19 -> MVS station finished recording before or at the same time with copter's landing`
- `20 -> Magnetometer started recording after or at the same time with copter's take-off`
- `21 -> Magnetometer finished recording before or at the same time with copter's landing`
