#include <iostream>
#include <cctype>
#include <stack>
#include "game.h"
#include "cell.h"
#include "colors.h"
// #include "stack"
using namespace std;

class Othello : public main_savitch_14::game
{
public:
	// protected:
	Othello();
	// Compute all the moves that the next player can make:
	void compute_moves(std::queue<std::string> &moves) const;
	// Display the status of the current game:
	void display_status() const;
	// Evaluate a board position:
	// NOTE: positive values are good for the computer.
	int evaluate() const;
	// Return true if the current game is finished:
	bool is_game_over() const;
	// Return true if the given move is legal for the next player:
	bool is_legal(const std::string &move) const;
	Othello *clone() const;
	// Restart the game from the beginning:
	void restart();
	queue<int> get_dirs(const std::string &move) const;
	bool check_dir(const string move, const string dir, int peice) const;
	// Have the next player make a specified move:
	void make_move(const string &move);
	int get_row(const string &move) const;
	int get_col(const string &move) const;
	// void set_skip(int num) { skip_amount = num; }
	string to_move(const int row, const int col) const{return char(col + 'A') + to_string(row + 1);}

private:
	int skip_amount;
	Cell board[8][8];
};
