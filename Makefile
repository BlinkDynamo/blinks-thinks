.PHONY: all clean

COMPILER = clang++ -std=c++11

SRCS = src/main.cpp src/splash_screens.cpp src/backgrounds.cpp src/button.cpp

EXEC = build/blinks-thinks

all:
	mkdir -p build
	$(COMPILER) $(SRCS) -o $(EXEC) -L.lib -lraylib -Iinclude -lm -ldl -lpthread -lGL

clean:
	rm -rf build
