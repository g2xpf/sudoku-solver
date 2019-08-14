#/bin/sh

find . -name "*.txt" -exec sh -c "echo {}: && cat {} | ./sudoku" \;
