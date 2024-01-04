# Compliation Configs
STANDARD := c++17
CC := g++
CC_FLAGS := -std=$(STANDARD) -Wall -Wextra -pedantic -g

SRC_DIR := src
BUILD_DIR := build
MAIN_PATH := $(BUILD_DIR)/main
PPM_PATH := image.ppm

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

# Actions
.PHONY: render clean
render: main
	./$(MAIN_PATH) > $(PPM_PATH)

clean:
	rm -rf $(OUT_DIR) $(PPM_PATH)

# Build
main: $(BUILD_DIR) $(SRCS)
	$(CC) $(CC_FLAGS) $(SRCS) -o $(MAIN_PATH)
	
$(BUILD_DIR):
	mkdir $(BUILD_DIR)
