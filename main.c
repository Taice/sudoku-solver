// TODO:
// [] complete is_valid function
// [] make backtracking algorithm

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

int sudoku[9][9];

int main(void) {
  char strings[9][27];

  printf("Please input a comma-separated string of 9 digits for each row, "
         "passing 0 if your slot is empty:\n");

  for (int i = 0; i < 9;
       i++) { // Change loop index from 1-9 to 0-8 to match array indexing
    printf("%i: ", i + 1);
    fgets(strings[i], 27, stdin);
  }

  for (int i = 0; i < 9; i++) {
    int col = 0; // Initialize column index
    for (int j = 0; j < 27 && col < 9; j++) {
      if (isdigit(strings[i][j])) {
        // Convert character to integer
        sudoku[i][col] =
            strings[i][j] - '0'; // Correct character to integer conversion
        col++;                   // Move to next column
      }
    }
  }

  return 0;
}

bool is_valid(char arr[9][9]) {
  // check if number in column or row
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (sudoku[row][col] != 0) {
        for (int k = 0; k < 9; k++) {
          if (k != col && sudoku[row][col] == sudoku[row][k]) {
            return false;
          }
          if (k != row && sudoku[row][col] == sudoku[k][col]) {
            return false;
          }
        }
      }
    }
  }
  int boxes[3][3][3];
  // TODO:
  // [] make small boxes
  // [] check if number in respective small box

  return true;
}
