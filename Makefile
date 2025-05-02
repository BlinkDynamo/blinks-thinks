.PHONY: all clean

all:
	mkdir -p build
	clang++ -std=c++11 src/main.cpp src/splash_screens.cpp -o build/wizard-tower -L.lib -lraylib -Iinclude -lm -ldl -lpthread -lGL

clean:
	rm -rf build
