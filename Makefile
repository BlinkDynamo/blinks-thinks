.PHONY: all clean

all:
	mkdir -p build
	gcc src/main.c src/splash_screens.c -o build/wizard-tower -L.lib -lraylib -Iinclude -lm -ldl -lpthread -lGL

clean:
	rm -rf build
