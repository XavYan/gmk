CC=g++
CFLAGS=-g -Wall -Wextra -std=c++17
all: src/main.cpp
	$(CC) $(CFLAGS) -o main src/main.cpp


.PHONY: clean

clean:
	rm -rf build/*.o
