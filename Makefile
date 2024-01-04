# Compliation Configs
STANDARD := c++17
CC := g++
CC_FLAGS := -std=$(STANDARD) -Wall -Wextra -pedantic -g

SRC_DIR := src
BUILD_DIR := build
MAIN_PATH := $(BUILD_DIR)/main
PPM_PATH := image.ppm

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Actions
all: render

.SILENT:
.PHONY: render clean
render: main
	@echo Beginning render
	./$(MAIN_PATH) > $(PPM_PATH)

clean:
	@echo Cleaning up
	rm -rf $(BUILD_DIR) $(PPM_PATH)

# Build
main: $(OBJS)
	@echo Linking object files to $(MAIN_PATH)
	$(CC) $(CC_FLAGS) $(OBJS) -o $(MAIN_PATH)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo Compiling $< to $@
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c $< -o $@
