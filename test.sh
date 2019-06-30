#/bin/sh


find . -name "*.txt" -exec sh -c "cat {} | ./sudoku" \;
