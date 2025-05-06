.PHONY: all clean

COMPILER = clang++ -std=c++11

SRCS = src/main.cpp \
	   src/splash_screen.cpp \
	   src/background.cpp \
	   src/button.cpp

EXEC = build/blinks-thinks

all:
	mkdir -p build
	$(COMPILER) $(SRCS) -o $(EXEC) -L.lib -lraylib -Iinclude -lm -ldl -lpthread -lGL

clean:
	rm -rf build
