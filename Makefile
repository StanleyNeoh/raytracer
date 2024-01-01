STANDARD := c++17
CC := g++
CC_FLAGS := -std=$(STANDARD) -Wall -Wextra -pedantic -g


.PHONY: render
render: main
	./main > image.ppm

# Build
main: main.cpp
	$(CC) $(CC_FLAGS) main.cpp -o main

