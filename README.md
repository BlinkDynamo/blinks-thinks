# ![Blink's Thinks](img/blinks-thinks.png)

## Index
* [Description](#description)
* [License](#license)
* [Dependencies](#dependencies)
* [Build](#build-instructions)
* [Play](#play)
* [Cleanup](#cleanup)

## Description
Blink's Thinks is a point-and-click puzzle game using raylib.

Blink's Thinks is a video game built using raylib and C++. It uses all original source music, 
code, art, and design (other than some included code for the raylib animation). It is currently 
compilable for Linux (clang++) and web (Emscripten). The project uses GitHub Pages to host the 
web-compiled game in a separate branch, 'gh-pages'. GitHub Workflows re-compiles the game to 
this branch on each push.

To play the most recent commit of the game, go ![here](blinkdynamo.github.io/blinks-thinks/).

# License
Blink's Thinks is licensed under the GNU General Public License v3.0. You should have recieved
a copy of the license along with this program. If not, see <https://www.gnu.org/licenses>.

This project uses raylib, along with a small snippet of raylib example code for the intro
animation. Both are these are licensed using a permissive zlib license, and are copyright
of Raymon Santamaria (@raysan5).

## Dependencies
If you would like to build the game locally, you will need these hard dependencies:
* make
* clang++
* emscripten
* raylib (installed, not just the submodule)

Along with these soft dependencies (according to your needs):
* valgrind (for development and leak checks)
* python (for locally hosting an http server)

## Build Instructions
To begin, clone the project and go to the root of the repository:

```bash
git clone https://github.com/BlinkDynamo/blinks-thinks.git blinks-thinks
cd blinks-thinks/
```

You can now build either for web, or native Linux. A simple 'make' builds both:
```bash
# Native build.
make native

# Web build.
make web

# Native and web build.
make
``` 

## Play
If the project built successfully, you now have various options to play the game: 

For native build:
```bash
# Simple call (no valgrind).
./build/blinks-thinks

# Call with valgrind (uses .supp files in valgrind/supp and logs to valgrind/log).
./valgrind/run.sh
```

For web build:
```bash
# Start the http server.
make serve

# Navigate to the locally hosted page that Emscripten compiled.
firefox localhost:8080/blinks-thinks.html
```

## Cleanup
Should you want to clean the build/ and tests/ directories:
```bash
make clean
```
