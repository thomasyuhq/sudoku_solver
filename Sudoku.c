#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sodoku.h"

void print_board(int *board) {
    assert(board);

    for (int i = 0; i < COLS; ++i) {
        if (i % 3 == 0) {
            printf("+-----+-----+-----+\n");
        }
        for (int j = 0; j < ROWS; ++j) {
            if (j % 3 == 0) {
                printf("|");
            }
            if (j % 3 == 2) {
                printf("%d", board[i * COLS + j]);
            } else {
                printf("%d ", board[i * COLS + j]);
            }
        }
        printf("|\n");
    }
    printf("+-----+-----+-----+\n");
}

bool used_in_col(int *board, int col, int num) {
    assert(board);

    for (int i = 0; i < COLS; ++i) {
        if (board[i * ROWS + col] == num) return true;
    }
    return false;
}

bool used_in_row(int *board, int row, int num) {
    assert(board);

    for (int i = 0; i < ROWS; ++i) {
        if (board[row * ROWS + i] == num) return true;
    }
    return false;
}

bool used_in_box(int *board, int col, int row, int num) {
    assert(board);
  
    for (int i = 0; i < BOX; ++i) {
        for (int j = 0; j < BOX; ++j) {
            if (board[(row + i) * ROWS + col + j] == num) return true;
        }
    }
    return false;
}

bool is_valid(int *board, int col, int row, int num) {
    assert(board);

    return (!used_in_box(board, col - col % 3, row - row % 3, num) &&
            !used_in_col(board, col, num) &&
            !used_in_row(board, row, num) &&
            board[row * ROWS + col] == EMPTY);
}

bool next_available(int *board, int *col, int *row) {
    assert(board);
    assert(col);
    assert(row);

    for ((*row) = 0; (*row) < ROWS; ++(*row)) {
        for ((*col) = 0; (*col) < COLS; ++(*col)) {
            if (board[(*row) * ROWS + (*col)] == EMPTY) return true;
        }
    }
    return false;
}

bool solve(int *board) {
    assert(board);

    int c = 0;
    int r = 0;
    int *col = &c;
    int *row = &r;
    if (!next_available(board, col, row)) return true;
    for (int num = 1; num <= 9; ++num) {
        if (is_valid(board, c, r, num)) {
            board[r * ROWS + c] = num;

            if (solve(board)) return true;
            board[r * ROWS + c] = EMPTY;
        }
    }
    return false;
}

void input(int *board) {
    assert(board);
    while (1) {
        char cmd[10];
        int col;
        int row;
        int num;

        if (scanf("%s", &cmd) == 1) {
            if (!strcmp(cmd, "add")) {
                if (scanf("%d", &col) == 1 &&
                    scanf("%d", &row) == 1 &&
                    scanf("%d", &num) == 1) {
                    if (1 <= col && col <= 9 &&
                        1 <= row && row <= 9 &&
                        1 <= num && num <= 9) {
                        board[(row - 1) * ROWS + (col - 1)] = num;
                        print_board(board);
                    }
                }
            } else if (!strcmp(cmd, "remove")) {
                if (scanf("%d", &col) == 1 &&
                    scanf("%d", &row) == 1) {
                    if (1 <= col && col <= 9 &&
                        1 <= row && row <= 9) {
                        board[(row - 1) * ROWS + (col - 1)] = EMPTY;
                        print_board(board);
                    }
                }
            } else if (!strcmp(cmd, "exit")) {
                print_board(board);
                solve(board);
                printf("\n------solved:------\n");
                print_board(board);
                break;
            }
        }
    }
}

int main(void) {
    int *board = malloc(ROWS * COLS * sizeof(int));
    for (int i = 0; i < COLS; ++i) {
        for (int j = 0; j < ROWS; ++j) {
            board[i * ROWS + j] = EMPTY;
        }
    }
    input(board);
    free(board);
}