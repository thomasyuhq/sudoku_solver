// A module for an interactive sudoku solver using backtracking
#include <stdbool.h>

const int EMPTY = 0;
const int ROWS = 9;
const int COLS = 9;
const int BOX = 3;

// The following is required for all functions: 
//    * board is valid 
//    * 1 <= col <= 9 
//    * 1 <= row <= 9
//    * 1 <= num <= 9 
//    (not asserted)

// Solve (board) takes a board and places a temporary value to all empty 
//   locations such that every location in the board is_valid. 
// time: O(n * n)
bool solve(int *board);

// is_valid (board, col, row, num) determines if the num placed into the 
//   (col, row) location is valid by checking used_in_col, used_in_row, 
//   and used_in_box
// time: O(n)
bool is_valid(int *board, int col, int row, int num);

// used_in_col(board, col, num) determines if a col in a board contains the num
// time: O(n)
bool used_in_col(int *board, int col, int num);

// used_in_row(board, row, num) determines if a row in a board contains the num
// time: O(n)
bool used_in_row(int *board, int row, int num);

// used_in_box(board, col, row, num) determines if the box contains the num from
//   a given col and row beginning locations
// time: O(n)
bool used_in_box(int *board, int col, int row, int num);

// next_available(board, col, row) finds the next EMPTY location in board. If a 
//   location is found, the col and row positions are updated and the function 
//   returns true
// requires: col is a valid pointer 
//           row is a valid pointer
// time: O(n)
bool next_available(int *board, int *col, int *row);

// input(board) takes the input from the used to place or remove numbers in a 
//   board. 
// * To add numbers, user input "add" followed by 3 integers: col, row, num.
//      For example: "add 1 2 3" adds "3" to column 1 row 2 in a board. 
// * To remove numbers, user inputs "remove" followed by 2 integers: col, row. 
//      For example: "remove 4 5" removes the number from column 4 row 5. 
// * To stop inputting, user inputs "exit" and the program solved the prevousily 
//      entered numbers 
//   (no bulletproofing was done)
//   (all pervious "" are used to add emphasis and not to be entered)
// effects: produces output
// time: O(n)
void input(int *board); 

// print_board(board) prints the board in a fancy way.
// effects: produces output
// time: O(n)
void print_board(int *board);