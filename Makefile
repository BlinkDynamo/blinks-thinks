.PHONY: all web clean 

# Common variables

SRC_DIR := src
INCLUDE_DIR := include
LIB_DIR := lib
LIB_WEB := $(LIB_DIR)/libraylib_web.a
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Native build. This assumes an installed raylib library for now. It does not use the local 'lib/' directory.
NATIVE_BUILD_DIR := build/native
NATIVE_COMPILER = clang++ -std=c++11
NATIVE_EXEC := $(NATIVE_BUILD_DIR)/blinks-thinks
NATIVE_FLAGS := -g \
				-Wall \
				-Wextra \
				-Werror \
				-I$(INCLUDE_DIR) \
				-lraylib \
				-Iinclude \
				-lm \
				-ldl \
				-lpthread \
				-lGL

# Web build
WEB_BUILD_DIR := build/web
WEB_COMPILER := emcc
WEB_EXEC := $(WEB_BUILD_DIR)/index.html
# Expand each file inside 'audio/' with xargs and format them as flags.
WEB_PRELOAD_ASSETS := $(shell find audio -type f | xargs -I{} echo --preload-file {})
WEB_FLAGS := -Os \
			 -Wall \
			 -I. \
			 -I$(INCLUDE_DIR) \
			 $(LIB_WEB) \
			 -DPLATFORM_WEB \
			 -DRAUDIO_IMPLEMENTATION \
			 -D_SUPPORT_MODULE_RAUDIO \
			 -s USE_GLFW=3 \
			 -s ASYNCIFY \
			 -s ALLOW_MEMORY_GROWTH=1\
			 -s FORCE_FILESYSTEM=1 \
			 $(WEB_PRELOAD_ASSETS)  \
			 --shell-file web/shell.html
			 
			 

all: native web
	
native:	
	@mkdir -p $(NATIVE_BUILD_DIR)
	$(NATIVE_COMPILER) $(SRCS) -o $(NATIVE_EXEC) $(NATIVE_FLAGS)


web: $(LIB_WEB)
	@mkdir -p $(WEB_BUILD_DIR)
	$(WEB_COMPILER) -o $(WEB_EXEC) $(SRCS) $(WEB_FLAGS)	

$(LIB_WEB):	
	@mkdir -p $(LIB_DIR)
	emcc -c external/raylib/src/rcore.c -o external/raylib/src/rcore.o -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
	emcc -c external/raylib/src/rshapes.c -o external/raylib/src/rshapes.o -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
	emcc -c external/raylib/src/rtextures.c -o external/raylib/src/rtextures.o -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
	emcc -c external/raylib/src/rtext.c -o external/raylib/src/rtext.o -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
	emcc -c external/raylib/src/rmodels.c -o external/raylib/src/rmodels.o -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
	emcc -c external/raylib/src/utils.c -o external/raylib/src/utils.o -Os -Wall -DPLATFORM_WEB
	emcc -c external/raylib/src/raudio.c -o external/raylib/src/raudio.o -Os -Wall -DPLATFORM_WEB
	
	emar rcs $(LIB_WEB) \
		external/raylib/src/rcore.o \
		external/raylib/src/rshapes.o \
		external/raylib/src/rtextures.o \
		external/raylib/src/rtext.o \
		external/raylib/src/rmodels.o \
		external/raylib/src/utils.o \
		external/raylib/src/raudio.o

serve:
	cd $(WEB_BUILD_DIR) && python -m http.server 8080

clean:
	rm -rf build
	rm -rf lib
