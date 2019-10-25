CC=g++
CFLAGS=-g -Wall -Wextra -std=c++17
all: ./main.cpp
	$(CC) $(CFLAGS) -o gmk ./main.cpp


.PHONY: clean

clean:
	rm -rf build/*.o
