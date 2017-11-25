#------------------------------------------------------------------------------
# GNOME Shortcut Manager Makefile
# Type "make" at root directory to compile all
#------------------------------------------------------------------------------
### There is manual for using Makefile syntax
### https://en.wikibooks.org/wiki/Make
#------------------------------------------------------------------------------
# "All or nothing" – We compile only all, we don't support single-compile

# Default compiler, g++ for gcc
CC = g++

# Additional compile parameters
CFLAGS = -std=c++14 `pkg-config --cflags gtk+-3.0 gmodule-2.0` -rdynamic
LIBS = `pkg-config --libs gtk+-3.0 gmodule-2.0`
ADD_FLAGS = -g -Wall # -g and -Wall are for debugging

# Directiories / output files
BIN_DIR = bin
SRC_DIR = src
INCLUDE_DIR = include
OUTPUT = GNOME-Shortcut-Manager

# Included sources and headers
# PLEASE: Keep this list alphabetically, excluding main
# main Should be at the beginning
SOURCES = $(SRC_DIR)/main.cpp \
	$(SRC_DIR)/aboutwindow.cpp \
	$(SRC_DIR)/filemanager.cpp \
	$(SRC_DIR)/filepicker.cpp \
	$(SRC_DIR)/mainwindow.cpp

HEADERS =\
	$(INCLUDE_DIR)/aboutwindow.h \
	$(INCLUDE_DIR)/filemanager.h \
	$(INCLUDE_DIR)/filepicker.h \
	$(INCLUDE_DIR)/mainwindow.h

# Main compilation command
# Keep this clean, everything is in variables; above
all: dirs $(SOURCES) $(HEADERS)
	$(CC) $(SOURCES) $(HEADERS) $(CFLAGS) $(LIBS) $(ADD_FLAGS) -o $(BIN_DIR)/$(OUTPUT)

# Clean command
clean:
	rm -f -r $(BIN_DIR)

# Create Directiories before compiling
dirs:
	test -d $(BIN_DIR) || mkdir -p $(BIN_DIR)
