import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    static final int SUDOKU_SIZE = 9;
    static final int SUBGRID = 3;

    public static void main(String[] args) {
        int[][] sudoku = new int[SUDOKU_SIZE][SUDOKU_SIZE];
        Scanner scanner;

        if (args.length == 1) {
            File file = new File(args[0]);
            try {
                scanner = new Scanner(file);
            } catch (FileNotFoundException e) {
                System.out.println("file not found");
                return;
            }
            if (!getSudoku(scanner, sudoku, true)) {
                System.out.println("File is wrongly formatted");
            }
        } else if (args.length == 0) {
            scanner = new Scanner(System.in);
            getSudoku(scanner, sudoku, false);
        } else {
            System.out.println("usage: sudoku-solver <filename> || sudoku-solver");
            return;
        }

        if (isValid(sudoku)) {
            if (solve(sudoku)) {
                System.out.println("solved!");
                for (int i = 0; i < SUDOKU_SIZE; i++) {
                    for (int j = 0; j < SUDOKU_SIZE; j++) {
                        System.out.printf("%d ", sudoku[i][j]);
                    }
                    System.out.println();
                }
            } else {
                System.out.println("no solution exists");
            }
        } else {
            System.out.println("invalid sudoku");
        }
    }

    public static boolean solve(int[][] sudoku) {
        int[] emptyPos = findEmptySpace(sudoku);

        if (emptyPos == null) {
            return true; // puzzle solved
        }

        int row = emptyPos[0];
        int col = emptyPos[1];

        for (int num = 1; num <= SUDOKU_SIZE; num++) {
            sudoku[row][col] = num;

            if (isValid(sudoku)) {
                if (solve(sudoku)) {
                    return true;
                }
            }

            sudoku[row][col] = 0; // reset on backtrack
        }

        return false; // trigger backtracking
    }


    private static boolean getSudoku(Scanner scanner, int[][] sudoku, boolean isFile) {
        if (!isFile) {
            System.out.println("please input 9 strings of characters that have 9 digits.");
        }
        for (int i = 0; i < SUDOKU_SIZE; i++) {
            String buffer = scanner.nextLine().trim();
            if (!isCorrectSize(buffer)) {
                if (isFile) {
                    return false;
                } else {
                    System.out.println("Please input exactly 9 digits");
                    i--;
                    continue;
                }
            }
            for (int j = 0; j < SUDOKU_SIZE; j++) {
                if (Character.isDigit(buffer.charAt(j))) {
                    sudoku[i][j] = Character.getNumericValue(buffer.charAt(j));
                }
            }
        }
        return true;
    }

    private static boolean isCorrectSize(String buffer) {
        int count = 0;
        for (int index = 0; index < buffer.length(); index++) {
            if (Character.isDigit(buffer.charAt(index))) {
                count++;
            }
        }
        return count == SUDOKU_SIZE;
    }

    public static boolean isValid(int[][] sudoku) {
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

    public static int[] findEmptySpace(int[][] sudoku) {
        for (int row = 0; row < SUDOKU_SIZE; row++) {
            for (int col = 0; col < SUDOKU_SIZE; col++) {
                if (sudoku[row][col] == 0) {
                    return new int[]{row, col};
                }
            }
        }
        return null;
    }
}
