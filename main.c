#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#define SIZE 9
#define SUBGRID_SIZE 3

bool is_valid(int arr[SIZE][SIZE]);
bool backtrack(int arr[SIZE][SIZE]);
bool find_empty_space(int arr[SIZE][SIZE], int *row, int *col);

int sudoku[SIZE][SIZE];

int main(void) {
  char strings[SIZE][SIZE];

  printf("Please input strings of 9 digits, using 0 if your slot is empty.");

  for (int i = 0; i < SIZE; i++) {
    printf("%i: ", i + 1);
    fgets(strings[i], SIZE * 3, stdin);
  }

  for (int i = 0; i < SIZE; i++) {
    int col = 0;
    for (int j = 0; j < SIZE && col < SIZE; j++) {
      if (isdigit(strings[i][j])) {
        sudoku[i][col] = strings[i][j] - '0';
        col++;
      }
    }
  }

  if (backtrack(sudoku)) {
    printf("Solved!\n");
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        printf("%d ", sudoku[i][j]);
      }
      printf("\n");
    }
  } else {
    printf("no solution exists.\n");
  }
  return 0;
}

bool is_valid(int arr[SIZE][SIZE]) {
  bool rows[SIZE][SIZE] = {false};
  bool cols[SIZE][SIZE] = {false};
  bool boxes[SIZE][SIZE] = {false};

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (arr[i][j] != 0) {
        int num = arr[i][j] - 1;
        int box_index = (i / SUBGRID_SIZE) * SUBGRID_SIZE + j / SUBGRID_SIZE;

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

bool find_empty_space(int arr[SIZE][SIZE], int *row, int *col) {
  for (*row = 0; *row < SIZE; (*row)++) {
    for (*col = 0; *col < SIZE; (*col)++) {
      if (arr[*row][*col] == 0) {
        return true;
      }
    }
  }
  return false;
}

bool backtrack(int arr[SIZE][SIZE]) {
  int row, col;

  if (!find_empty_space(arr, &row, &col)) {
    return true;
  }

  for (int num = 1; num <= SIZE; num++) {
    arr[row][col] = num;

    if (is_valid(arr)) {
      if (backtrack(arr)) {
        return true;
      }
    }

    arr[row][col] = 0;
  }
  return false;
}
