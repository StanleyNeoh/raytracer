# Compliation Configs
STANDARD := c++17
CC := g++
CC_FLAGS := -std=$(STANDARD) -Wall -Wextra -pedantic -g

SRC_DIR := src
BUILD_DIR := build
APP_PATH := $(BUILD_DIR)/app
PPM_PATH := image.ppm

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Actions
all: run

.SILENT:
.PHONY: run clean
run: app
	@echo Executing app
	./$(APP_PATH) > $(PPM_PATH)

clean:
	@echo Cleaning up
	rm -rf $(BUILD_DIR) $(PPM_PATH)

# Build
app: $(OBJS)
	@echo Linking object files to $(APP_PATH)
	$(CC) $(CC_FLAGS) $(OBJS) -o $(APP_PATH)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo Compiling $< to $@
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c $< -o $@
