// class that utlizes the backtracking algorithm to solve the puzzle
#pragma once
#include "Numbers.h"
#include "Zones.h"
#include <iostream>

class Sudoku {

private:
	int board[9][9] = {
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,}
	};
	int num_filled;
	Numbers* nums;
	Zones* zones;
	std::vector<std::vector<int>> changes;

public:
	Sudoku(Numbers* n, Zones* z) : board(), num_filled(0), nums(n), zones(z), changes() {
	}

	void set_value(int num, int row, int col) {
		board[row][col] = num;
	}

	// attempts to solve the board and returns a boolean to solve()
	bool solve_board(int row = 0, int col = 0) {
	
		if (row > 8) {
			return true;
		}

		if (col > 8) {
			return solve_board(row + 1, 0);
		}

		if (board[row][col] > 0) {
			return solve_board(row, col + 1);
		}

		for (int i = 1; i <= 9; i++) {
			board[row][col] = i;
			changes.push_back(std::vector<int>{i, row, col});

			if (valid(row, col)) {

				if (solve_board(row, col + 1)) {
					return true;
				}
			}

		}

		this->board[row][col] = 0;

		return false;

	}

	// since the solving function needs to return a boolean it is called from this one, rather than being this one 
	std::vector<std::vector<int>> solve() {
		// returns the moves that were done to solve the board (if it is solvable)
		if (solve_board()) { return changes; }
	}

	// checks if a number choice is valid on the sudoku grid
	bool valid(int row, int col) {
		int num = board[row][col];
		int zone_row = (row / 3) * 3, zone_col = (col / 3) * 3;
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				if (zone_row + j != row && zone_col + k != col && board[zone_row + j][zone_col + k] == num) { return false; }
			}
		}
		for (int i = 0; i < 9; i++) {
			if (board[row][i] == num && i != col) {
				return false;
			}
			if (board[i][col] == num && i != row) {
				return false;
			}
		}
		return true;
	}


};
