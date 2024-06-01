#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 9
#define SUBGRID_SIZE 3

int file_sudoku(const char *filename);
void input_sudoku();
bool is_valid(int arr[SIZE][SIZE]);
bool backtrack(int arr[SIZE][SIZE]);
bool find_empty_space(int arr[SIZE][SIZE], int *row, int *col);

int sudoku[SIZE][SIZE];

int main(int argc, char **argv) {
  if (argc == 1) {
    input_sudoku();
  } else if (argc == 2) {
    if (file_sudoku(argv[1]) == 1) {
      return 1;
    }
  } else {
    fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
    return 1;
  }

  if (is_valid(sudoku)) {
    if (backtrack(sudoku)) {
      printf("Solved!\n");
      for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
          printf("%d ", sudoku[i][j]);
        }
        printf("\n");
      }
    } else {
      printf("No solution exists.\n");
    }
    return 0;
  } else {
    printf("invalid sudoku");
    return 0;
  }
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

void input_sudoku() {
  printf("Please input 9 strings of 9 digits each, using 0 for empty slots.\n");

  for (int i = 0; i < SIZE; i++) {
    printf("%d: ", i + 1);
    char buffer[SIZE + 2];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      fprintf(stderr, "Error reading input\n");
      exit(EXIT_FAILURE);
    }

    for (int j = 0; j < SIZE; j++) {
      if (isdigit(buffer[j])) {
        sudoku[i][j] = buffer[j] - 0;
      } else {
        fprintf(stderr, "Invalid character in input\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}
int file_sudoku(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (fscanf(file, "%1d", &sudoku[i][j]) != 1) {
        fprintf(stderr, "Invalid input format in file\n");
        fclose(file);
        return 1;
      }
    }
  }
  fclose(file);
}
