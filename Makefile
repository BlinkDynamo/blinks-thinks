# -------------------------------------------------------------------------------------------- #
#                                           Makefile                                           #
# -------------------------------------------------------------------------------------------- #
#																							   #
#	Notable acronyms/shorthand																   #
# 	used in variable names:                                                                    #
#                                                                                              #
# 	RL  = raylib                                                                               #
# 	BT  = Blink's Thinks																	   #
# 	NAT = native                     														   #
# 	D   = directory	                                                                           #
#																							   #
# -------------------------------------------------------------------------------------------- #

.PHONY: all web native serve clean

# Source directories. SRC_BT for Blink's Thinks, and SRC_RL for raylib.
SRC_BT := src
SRC_RL := external/raylib/src

# Build directories.
D_BUILD_OBJ := build/obj
D_BUILD_OUT := build/out
D_BUILD_LIB := build/lib

# D_BUILD_OBJ subdirectories. For object files.
D_OBJ_NAT := $(D_BUILD_OBJ)/native
D_OBJ_WEB := $(D_BUILD_OBJ)/web
D_OBJ_RL := $(D_BUILD_OBJ)/raylib

# D_BUILD_OUT subdirectories. For final executables and game files to serve.
D_OUT_NAT := $(D_BUILD_OUT)/native
D_OUT_WEB := $(D_BUILD_OUT)/web

# D_BUILD_LIB subdirectories. For libraries.
D_LIB_RL := $(D_BUILD_LIB)/raylib

# Blink's Thinks source files. 
BT_SRCS := $(wildcard $(SRC_BT)/*.cpp)

# Library build. This is where the external/raylib/ submodule sends it's *.o files.
RL_WEB := $(D_LIB_RL)/libraylib_web.a
RL_WEB_OBJS := $(D_OBJ_RL)/rcore.o \
			   $(D_OBJ_RL)/rshapes.o \
			   $(D_OBJ_RL)/rtextures.o \
			   $(D_OBJ_RL)/rtext.o \
			   $(D_OBJ_RL)/rmodels.o \
			   $(D_OBJ_RL)/utils.o \
			   $(D_OBJ_RL)/raudio.o

# Shared warning flags. Work for both emcc and clang++, as emcc is clang-based.
WARNINGS := -Wall -Wextra -Werror \
			-Wpedantic -Wshadow -Wnon-virtual-dtor \
			-Wold-style-cast -Wsign-conversion

# The standard of c++ to use. 
STD := -std=c++23

# Native build. This assumes an installed raylib library.
# It does not search in the 'build/lib/' directory.
NATIVE_COMPILER := clang++ $(STD)
NATIVE_EXEC := $(D_OUT_NAT)/blinks-thinks
NATIVE_FLAGS := $(WARNINGS) \
				-g \
				-Iinclude \
				-lraylib \
				-lm \
				-ldl \
				-lpthread \
				-lGL

# Web build.
WEB_COMPILER := em++ $(STD)
WEB_EXEC := $(D_OUT_WEB)/index.html
# Expand each file inside 'audio/' with xargs and format them as flags.
WEB_PRELOAD_ASSETS := $(shell find audio -type f | xargs -I{} echo --preload-file {})
WEB_FLAGS := $(WARNINGS) \
			 -I. \
			 -Iinclude \
			 -I$(SRC_RL) \
			 $(RL_WEB) \
			 -DPLATFORM_WEB \
			 -DRAUDIO_IMPLEMENTATION \
			 -D_SUPPORT_MODULE_RAUDIO \
			 -s USE_GLFW=3 \
			 -s ASYNCIFY \
			 -s ALLOW_MEMORY_GROWTH=1\
			 -s FORCE_FILESYSTEM=1 \
			 $(WEB_PRELOAD_ASSETS)  \
			 --shell-file web/shell.html

# Library build.
RL_WEB_COMPILER := emcc
			 
# -------------------------------------------------------------------------------------------- #
#                                       Dependency Tree.                                       #
# -------------------------------------------------------------------------------------------- #
 
# Build all platform targets.
all: native web

# Build for Linux.
native:	$(D_OUT_NAT)
	@printf "[INFO] Native build.\n"
	$(NATIVE_COMPILER) $(BT_SRCS) -o $(NATIVE_EXEC) $(NATIVE_FLAGS)

# Build for the web.
web: $(D_OUT_WEB) $(RL_WEB) 	
	@printf "[INFO] Web build.\n"
	$(WEB_COMPILER) -o $(WEB_EXEC) $(BT_SRCS) $(WEB_FLAGS)	

# Build the web library for raylib.
$(RL_WEB):	$(D_LIB_RL) $(RL_WEB_OBJS)
	@printf "[INFO] Library build.\n"
	emar rcs $(RL_WEB) $(RL_WEB_OBJS)	

# Raylib object file rules (check if these already exist before recompiling).
$(D_OBJ_RL)/rcore.o: $(SRC_RL)/rcore.c | $(D_OBJ_RL)
	$(RL_WEB_COMPILER) -w -c $< -o $@ -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
$(D_OBJ_RL)/rshapes.o: $(SRC_RL)/rshapes.c | $(D_OBJ_RL)
	$(RL_WEB_COMPILER) -w -c $< -o $@ -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
$(D_OBJ_RL)/rtextures.o: $(SRC_RL)/rtextures.c | $(D_OBJ_RL)
	$(RL_WEB_COMPILER) -w -c $< -o $@ -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
$(D_OBJ_RL)/rtext.o: $(SRC_RL)/rtext.c | $(D_OBJ_RL)
	$(RL_WEB_COMPILER) -w -c $< -o $@ -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
$(D_OBJ_RL)/rmodels.o: $(SRC_RL)/rmodels.c | $(D_OBJ_RL)
	$(RL_WEB_COMPILER) -w -c $< -o $@ -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
$(D_OBJ_RL)/utils.o: $(SRC_RL)/utils.c | $(D_OBJ_RL)
	$(RL_WEB_COMPILER) -w -c $< -o $@ -DPLATFORM_WEB
$(D_OBJ_RL)/raudio.o: $(SRC_RL)/raudio.c | $(D_OBJ_RL)
	$(RL_WEB_COMPILER) -w -c $< -o $@ -DPLATFORM_WEB

# Build directories.
$(D_OBJ_NAT):
	@mkdir -p $(D_OBJ_NAT)

$(D_OBJ_WEB):
	@mkdir -p $(D_OBJ_WEB)

$(D_OBJ_RL):
	@mkdir -p $(D_OBJ_RL)

$(D_OUT_NAT):
	@mkdir -p $(D_OUT_NAT)

$(D_OUT_WEB):
	@mkdir -p $(D_OUT_WEB)

$(D_LIB_RL):
	@mkdir -p $(D_LIB_RL)

# Serve the web build files to a local http server on port 8080.
serve: $(D_OUT_WEB)
	cd $(D_OUT_WEB) && python -m http.server 8080

clean:
	rm -rf build
