# -------------------------------------------------------------------------------------------- #
#                                           Makefile                                           #
# -------------------------------------------------------------------------------------------- #
#																							   #
#	Notable acronyms/shorthand																   #
# 	used in variable names:                                                                    #
#                                                                                              #
# 	NAT  = native                     														   #
# 	RL   = raylib                                                                              #
# 	BT   = Blink's Thinks																	   #
# 	D    = directory	                                                                       #
#																							   #
# -------------------------------------------------------------------------------------------- #
.PHONY: all web native serve clean

# Source directories. D_SRC_BT for Blink's Thinks, and D_SRC_RL for raylib.
D_SRC_BT := src
D_SRC_RL := external/raylib/src

# Build directories.
D_BUILD := build

# D_BUILD subdirectories.
D_BUILD_NAT := $(D_BUILD)/native
D_BUILD_WEB := $(D_BUILD)/web
D_BUILD_RL := $(D_BUILD)/raylib

# D_OBJ subdirectories. For object files.
D_OBJ_NAT := $(D_BUILD_NAT)/src
D_OBJ_WEB := $(D_BUILD_WEB)/src
D_OBJ_RL := $(D_BUILD_RL)/src

# D_OUT subdirectories. For output files and final executables.
D_OUT_NAT := $(D_BUILD_NAT)/out
D_OUT_WEB := $(D_BUILD_WEB)/out
D_OUT_RL := $(D_BUILD_RL)/out

# Blink's Thinks source files. 
BT_SRCS := $(wildcard $(D_SRC_BT)/*.cpp)
BT_OBJS_NAT := $(patsubst $(D_SRC_BT)/%.cpp, $(D_OBJ_NAT)/%.o,$(BT_SRCS))
BT_OBJS_WEB := $(patsubst $(D_SRC_BT)/%.cpp, $(D_OBJ_WEB)/%.o,$(BT_SRCS))

# Library build. This is where the external/raylib/ submodule sends it's *.o files.
RL_WEB := $(D_OUT_RL)/libraylib_web.a
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
NAT_COMP := clang++ $(STD)
NAT_EXEC := $(D_OUT_NAT)/blinks-thinks
NAT_COMP_FLAGS := $(WARNINGS) -g -Iinclude
NAT_LINK_FLAGS := -lraylib -lm -ldl -lpthread -lGL
				

# Web build.
WEB_COMP := em++ $(STD)
WEB_EXEC := $(D_OUT_WEB)/index.html

WEB_COMP_FLAGS := $(WARNINGS) -I. -Iinclude -I$(D_SRC_RL) -DPLATFORM_WEB -DRAUDIO_IMPLEMENTATION \
			      -D_SUPPORT_MODULE_RAUDIO 

# Expand each file inside 'res/' with xargs and format them as flags.
WEB_PRELOAD_ASSETS := $(shell find res -type f | xargs -I{} echo --preload-file {})

WEB_LINK_FLAGS := $(RL_WEB) -s USE_GLFW=3 -s ASYNCIFY -s ALLOW_MEMORY_GROWTH=1 \
				  -s FORCE_FILESYSTEM=1 $(WEB_PRELOAD_ASSETS) --shell-file web/shell.html

# Library build.
RL_WEB_COMP := emcc
			 
# -------------------------------------------------------------------------------------------- #
#                                       Dependency Tree.                                       #
# -------------------------------------------------------------------------------------------- #

# --- Linking rules. --- #

# Build all platform targets.
all: native web

# Build for Linux.
native:	$(D_BUILD_NAT) $(BT_OBJS_NAT)
	@printf "[INFO] Native build.\n"
	$(NAT_COMP) $(BT_OBJS_NAT) -o $(NAT_EXEC) $(NAT_LINK_FLAGS)

# Build for the web.
web: $(D_BUILD_WEB) $(RL_WEB) $(BT_OBJS_WEB)
	@printf "[INFO] Web build.\n"
	$(WEB_COMP) $(BT_OBJS_WEB) -o $(WEB_EXEC) $(WEB_LINK_FLAGS)	

# Build the web library for raylib.
$(RL_WEB):	$(D_BUILD_RL) $(RL_WEB_OBJS)
	@printf "[INFO] Library build.\n"
	emar rcs $(RL_WEB) $(RL_WEB_OBJS)

# --- Compiling rules. --- #

# Native Blink's Thinks object file rules.
$(D_OBJ_NAT)%.o: $(D_SRC_BT)/%.cpp | $(D_OBJ_NAT)
	$(NAT_COMP) $(STD) $(NAT_COMP_FLAGS) -c $< -o $@

# Web Blink's Thinks object file rules.
$(D_OBJ_WEB)%.o: $(D_SRC_BT)/%.cpp | $(D_OBJ_WEB)
	$(WEB_COMP) $(STD) $(WEB_COMP_FLAGS) -Iinclude -c $< -o $@

# Raylib object file rules (check if these already exist before recompiling).
$(D_OBJ_RL)/rcore.o: $(D_SRC_RL)/rcore.c | $(D_OBJ_RL)
	$(RL_WEB_COMP) -w -c $< -o $@ -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2

$(D_OBJ_RL)/rshapes.o: $(D_SRC_RL)/rshapes.c | $(D_OBJ_RL)
	$(RL_WEB_COMP) -w -c $< -o $@ -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2

$(D_OBJ_RL)/rtextures.o: $(D_SRC_RL)/rtextures.c | $(D_OBJ_RL)
	$(RL_WEB_COMP) -w -c $< -o $@ -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2

$(D_OBJ_RL)/rtext.o: $(D_SRC_RL)/rtext.c | $(D_OBJ_RL)
	$(RL_WEB_COMP) -w -c $< -o $@ -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2

$(D_OBJ_RL)/rmodels.o: $(D_SRC_RL)/rmodels.c | $(D_OBJ_RL)
	$(RL_WEB_COMP) -w -c $< -o $@ -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2

$(D_OBJ_RL)/utils.o: $(D_SRC_RL)/utils.c | $(D_OBJ_RL)
	$(RL_WEB_COMP) -w -c $< -o $@ -DPLATFORM_WEB

$(D_OBJ_RL)/raudio.o: $(D_SRC_RL)/raudio.c | $(D_OBJ_RL)
	$(RL_WEB_COMP) -w -c $< -o $@ -DPLATFORM_WEB

# --- Directory rules. --- #
$(D_BUILD_NAT):
	@mkdir -p $(D_OBJ_NAT)
	@mkdir -p $(D_OUT_NAT)

$(D_BUILD_WEB):
	@mkdir -p $(D_OBJ_WEB)
	@mkdir -p $(D_OUT_WEB)

$(D_BUILD_RL):
	@mkdir -p $(D_OBJ_RL)
	@mkdir -p $(D_OUT_RL)

# --- Utilities. --- #

# Serve the web build files to a local http server on port 8080.
serve: $(D_OBJ_WEB)
	cd $(D_BUILD_WEB) && python -m http.server 8080

clean:
	rm -rf build
