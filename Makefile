# Compliation Configs
STANDARD := c++17
CC := g++
CC_FLAGS := -std=$(STANDARD) -Wall -Wextra -pedantic -g

# Output config
OUT_DIR := bin
MAIN_PATH := $(OUT_DIR)/main
PPM_PATH := image.ppm

# Actions
.PHONY: render clean
render: main
	./$(MAIN_PATH) > $(PPM_PATH)

clean:
	rm -rf $(OUT_DIR) $(PPM_PATH)

# Build
main: main.cpp $(OUT_DIR)
	$(CC) $(CC_FLAGS) main.cpp -o $(MAIN_PATH)

$(OUT_DIR):
	mkdir $(OUT_DIR)