# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2 -Iinclude
LDFLAGS = -lm
# Enable OpenMP if you plan to parallelize (optional)
# CFLAGS += -fopenmp

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Source files
BS_SRC = $(SRC_DIR)/model_bs/bs.c
HESTON_SRC = $(SRC_DIR)/model_heston/heston.c
MERTON_SRC = $(SRC_DIR)/model_merton/merton.c
MAIN_SRC = $(SRC_DIR)/main.c

# Object files
BS_OBJ = $(BUILD_DIR)/bs.o
HESTON_OBJ = $(BUILD_DIR)/heston.o
MERTON_OBJ = $(BUILD_DIR)/merton.o
MAIN_OBJ = $(BUILD_DIR)/main.o

# All object files
OBJS = $(BS_OBJ) $(HESTON_OBJ) $(MERTON_OBJ) $(MAIN_OBJ)

# Target executable
TARGET = option_pricing

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile Black-Scholes
$(BS_OBJ): $(BS_SRC) $(INCLUDE_DIR)/bs.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(BS_SRC) -o $(BS_OBJ)

# Compile Heston Model
$(HESTON_OBJ): $(HESTON_SRC) $(INCLUDE_DIR)/heston.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(HESTON_SRC) -o $(HESTON_OBJ)

# Compile Merton Model
$(MERTON_OBJ): $(MERTON_SRC) $(INCLUDE_DIR)/merton.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(MERTON_SRC) -o $(MERTON_OBJ)

# Compile Main
$(MAIN_OBJ): $(MAIN_SRC) $(INCLUDE_DIR)/bs.h \
			$(INCLUDE_DIR)/heston.h \
			$(INCLUDE_DIR)/merton.h 
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o $(MAIN_OBJ)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

