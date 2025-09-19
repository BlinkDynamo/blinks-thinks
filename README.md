# ![Blink's Thinks](res/img/title_text.png)

## Index
- [Description](#description)
- [Play Online](#play-online)
- [Mission Statement](#mission-statement)
- [Contribution](#contribution)
- [Dependencies](#dependencies)
- [Build](#build-instructions)
- [Play Natively](#play-natively)
- [Cleanup](#cleanup)
- [License](#license)

## Description
Blink's Thinks is a self-hosting point-and-click puzzle game.

It runs on a simple C++ engine that uses raylib + raylib modules at it's core.  It is currently
compilable for Linux (clang++) and web (Emscripten). The project uses GitHub Pages to host the
web-compiled game in a separate branch, 'gh-pages'. GitHub Workflows re-compiles the game to
this branch on each push.

## Play Online
To play the most recent commit of the game hosted on GitHub Pages, go [here](https://blinkdynamo.github.io/blinks-thinks/).

## Mission Statement
I got inspired to start this project when I saw some [tsoding](https://github.com/tsoding)
making web assembly games with raylib and hosting them on GitHub pages. I wanted to make
something simple, but with character. This isn't an 'example' project or template code-- this
is my creative work (code, design, music, etc). I hope this project falls somewhere between
complete noob and industry-standard 1000 contributor FOSS project (which seems to be the two
heavy ends of the spectrum on GitHub).

## Contribution
Since this project is such a personal thing to me, I'm not interested in accepting blind pull
requests of feature contributions, such as level design or music. If you have an idea you would
like to see added, I'd be happy to hear your idea over email. Bugfixes are always open to submit.

## Dependencies
If you would like to build the game locally, you will need these hard dependencies:
- make
- clang++
- emscripten
- raylib (installed, not just the submodule)

Along with this soft dependency:
- python (for locally hosting an http server)

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

## Play Natively
If the project built successfully, you now have various options to play the game: 

For native build:
```bash
# To play the release version (no assertions).
./build/native/release/blinks_thinks

# To play the debug version (assertions).
./build/native/debug/blinks_thinks
```

For web build:
```bash
# NOTE: The web build will always be a release build (no assertions).

# Start the http server.
make serve

# Navigate to the locally hosted page that Emscripten compiled.
firefox localhost:8080/blinks-thinks.html
```

## Cleanup
Should you want to clean the build files.
```bash
make clean
```

# License
Blink's Thinks is licensed under the GNU General Public License v3.0. You should have recieved
a copy of the license along with this program. If not, see <https://www.gnu.org/licenses>.

This project uses raylib, along with a small snippet of raylib example code for the intro
animation. Both of these are licensed under an unmodified zlib/libpng license, which is an
OSI-certified, BSD-like license that allows static linking with closed source software.
Both are copyright (c) 2014-2025 Ramon Santamaria (@raysan5).
