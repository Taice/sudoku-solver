package sudokuSolver;

public class Solver {
    static final int SUDOKU_SIZE = 9;
    static final int SUBGRID = 3;
    int[][] sudoku = new int[SUDOKU_SIZE][SUDOKU_SIZE];

    public Solver(int[][] puzzle) {
        sudoku = puzzle;
    }

    public boolean solve() {
        int[] emptyPos = findEmptySpace();

        if (emptyPos == null) {
            return true; // puzzle solved
        }

        int row = emptyPos[0];
        int col = emptyPos[1];

        for (int num = 1; num <= SUDOKU_SIZE; num++) {
            sudoku[row][col] = num;

            if (isValid()) {
                if (solve()) {
                    return true;
                }
            }

            sudoku[row][col] = 0; // reset on backtrack
        }

        return false; // trigger backtracking
    }

    public boolean isValid() {
        boolean[][] rows = new boolean[SUDOKU_SIZE][SUDOKU_SIZE];
        boolean[][] cols = new boolean[SUDOKU_SIZE][SUDOKU_SIZE];
        boolean[][] boxes = new boolean[SUDOKU_SIZE][SUDOKU_SIZE];

        for (int i = 0; i < SUDOKU_SIZE; i++) {
            for (int j = 0; j < SUDOKU_SIZE; j++) {
                if (sudoku[i][j] != 0) {
                    int num = sudoku[i][j] - 1;
                    int box_index = (i / SUBGRID) * SUBGRID + j / SUBGRID;

                    if (rows[i][num] || cols[j][num] || boxes[box_index][num]) {
                        return false;
                    }

                    rows[i][num] = true;
                    cols[j][num] = true;
                    boxes[box_index][num] = true;
                }
            }
        }
        return true;
    }

    public int[] findEmptySpace() {
        for (int row = 0; row < SUDOKU_SIZE; row++) {
            for (int col = 0; col < SUDOKU_SIZE; col++) {
                if (sudoku[row][col] == 0) {
                    return new int[] { row, col };
                }
            }
        }
        return null;
    }
}
