all:
	gcc src/main.c src/logo.c -o wizard-tower -L.lib -lraylib -Iinclude -lm -ldl -lpthread -lGL
