# ![Blink's Thinks](img/blinks-thinks.png)

## Index
* [Description](#description)
* [Dependencies](#dependencies)
* [Build](#build-instructions)
* [Play](#play)
* [Cleanup](#cleanup)

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

## Play
If the project built successfully, you now have two options to play the game: 

```bash
# Simple call (no valgrind).
./build/blinks-thinks

# Call with valgrind (uses .supp files in valgrind/supp and logs to valgrind/log).
./valgrind/run.sh
```

For specific information about gameplay strategy and rules, see TUTORIAL.md.

## Cleanup
Should you want to clean the build/ and tests/ directories:
```bash
make clean
```
