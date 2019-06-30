CXX=g++

all: sudoku.cpp

sudoku.cpp:
	$(CXX) $@ -o sudoku

.PHONY: test

test: sudoku.cpp
	/bin/sh ./test.sh
	
