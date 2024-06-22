Sudoku Solver
=============
Usage:
------
Compiling:
`$ gcc main.c -o main`
OR
`$ cd java
$ javac Main.java`

### input the sudoku
After compiling run: (c version)
`$ ./main`

And input a 9 digit string for each row of the sudoku ex:
`1: 123456789
2: 123456789
3: 123456789
4: 123456789
5: 123456789
6: 123456789
7: 123456789
8: 123456789
9: 123456789`

OR using the java version:
`$ java sudokuSolver.Main` (in the java directory)


### reading the sudoku from a file with the c version
After compiling run:
`$ ./main <filename>`

Make sure the file has a 9x9 grid of digits and nothing else.

> [!NOTE]
> the java version doesn't support reading from files because i see it as unnecessary.

---

The program will output a solved sudoku if there is a possible solution, it will say there isn't one if the sudoku you provided isn't solvable.


Info:
-----
This is a self-study project, this isn't meant to be groundbreaking, it is in fact quite the opposite. 
