# Makefile

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -Isrc/lexer -Isrc/parser -Isrc/ast -Isrc/semantic -Isrc/ir -Isrc/codegen -Isrc/utils -g
LDFLAGS =

# Dirs
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Source Files
SRCS = $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)

# Object Files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Target Executable
TARGET = $(BIN_DIR)/CompilerCRB

# Default Target
all: $(TARGET)

# Link Object Files to Create Executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile Source Files to Object Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/$(dir $*)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean Build Artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Phony Targets
.PHONY: all clean
