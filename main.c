#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 9
#define SUBGRID_SIZE 3

int file_sudoku(const char *filename, int sudoku[SIZE][SIZE]);
void input_sudoku(int sudoku[SIZE][SIZE]);
bool is_valid(int sudoku[SIZE][SIZE]);
bool backtrack(int sudoku[SIZE][SIZE]);
bool find_empty_space(int sudoku[SIZE][SIZE], int *row, int *col);

int main(int argc, char **argv) {
  int sudoku[SIZE][SIZE];
  if (argc == 1) {
    input_sudoku(sudoku);
  } else if (argc == 2) {
    if (file_sudoku(argv[1], sudoku) == 1) {
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

bool is_valid(int sudoku[SIZE][SIZE]) {
  bool rows[SIZE][SIZE] = {false};
  bool cols[SIZE][SIZE] = {false};
  bool boxes[SIZE][SIZE] = {false};

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (sudoku[i][j] != 0) {
        int num = sudoku[i][j] - 1;
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

bool find_empty_space(int sudoku[SIZE][SIZE], int *row, int *col) {
  for (*row = 0; *row < SIZE; (*row)++) {
    for (*col = 0; *col < SIZE; (*col)++) {
      if (sudoku[*row][*col] == 0) {
        return true;
      }
    }
  }
  return false;
}

bool backtrack(int sudoku[SIZE][SIZE]) {
  int row, col;

  if (!find_empty_space(sudoku, &row, &col)) {
    return true;
  }

  for (int num = 1; num <= SIZE; num++) {
    sudoku[row][col] = num;

    if (is_valid(sudoku)) {
      if (backtrack(sudoku)) {
        return true;
      }
    }

    sudoku[row][col] = 0;
  }
  return false;
}

void input_sudoku(int sudoku[SIZE][SIZE]) {
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

int file_sudoku(const char *filename, int sudoku[SIZE][SIZE]) {
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
  return 0;
}
