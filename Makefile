# Compliation Configs
STANDARD := c++17
CC := g++
CC_FLAGS := -std=$(STANDARD) -Wall -Wextra -pedantic -g

# Output config
OUT_DIR := bin
MAIN:= $(OUT_DIR)/main

# Actions
.PHONY: render clean
render: main
	./$(MAIN) > image.ppm

clean:
	rm -rf $(OUT_DIR)

# Build
main: main.cpp $(OUT_DIR)
	$(CC) $(CC_FLAGS) main.cpp -o $(MAIN)

$(OUT_DIR):
	mkdir $(OUT_DIR)