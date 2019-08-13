CXX=g++
CFLAGS=-std=c++14

all: sudoku.cpp

sudoku.cpp:
	$(CXX) $(CFLAGS) $@ -o sudoku

.PHONY: test

test: sudoku.cpp
	/bin/sh ./test.sh
	
