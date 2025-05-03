# ![Blink's Thinks](img/blinks-thinks.png)

## Index
* [Description](#description)
* [Dependencies](#dependencies)
* [Build](#build-instructions)
* [Play](#play)

## Description
Blink's Thinks is a point-and-click puzzle game. 

## Dependencies
* make
* clang
* valgrind
* raylib

## Build Instructions
To begin, clone the project and go to the root of the repository:

```bash
git clone https://github.com/BlinkDynamo/blinks-thinks.git blinks-thinks
cd blinks-thinks/
```

Build the binary:
```bash
make
``` 

## Installation
If the project built successfully, you now have two options to play the game: 

```bash
# Simple call (no valgrind).
./build/blinks-thinks

# Call with valgrind (uses .supp files in valgrind/supp and logs to valgrind/log).
./valgrind/run.sh
```

Should you want to clean the build/ and tests/ directories:
```bash
make clean
```
