.PHONY: all web clean 

# Common variables

SRC_DIR := src
INCLUDE_DIR := include
LIB_DIR := lib
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
LIB := $(LIB_DIR)/libraylib.a

# Native build
NATIVE_BUILD_DIR := build/native
NATIVE_COMPILER = clang++ -std=c++11
NATIVE_EXEC := $(NATIVE_BUILD_DIR)/blinks-thinks
NATIVE_FLAGS := -I$(INCLUDE_DIR) -L.$(LIB_DIR) -lraylib -Iinclude -lm -ldl -lpthread -lGL

# Web build
WEB_BUILD_DIR := build/web
WEB_COMPILER := emcc
WEB_EXEC := $(WEB_BUILD_DIR)/blinks-thinks.html
WEB_FLAGS := -Os -Wall -I. -I$(INCLUDE_DIR) $(LIB) -s USE_GLFW=3 -s ASYNCIFY --shell-file web/shell.html -DPLATFORM_WEB

all: native web
	
native:	
	@mkdir -p $(NATIVE_BUILD_DIR)
	$(NATIVE_COMPILER) $(SRCS) -o $(NATIVE_EXEC) $(NATIVE_FLAGS)


web:
	@mkdir -p build $(WEB_BUILD_DIR)
	$(WEB_COMPILER) -o $(WEB_EXEC) $(SRCS) $(WEB_FLAGS)	

serve:
	cd $(WEB_BUILD_DIR) && python -m http.server 8080

clean:
	rm -rf build
