#include "othello.h"

Othello::Othello()
{
    board[3][3].heart_state();
    board[3][4].ace_state();
    board[4][3].ace_state();
    board[4][4].heart_state();
    skip_amount = 0;
}

// Display the status of the current game:
// need to be done for part one
void Othello::display_status() const
{
    char heart[] = "\xe2\x99\xa5";
    char ace[] = "\xe2\x99\xa4";
    cout << endl
         << "   Player One: " << heart << "    Player Two: " << ace << endl
         << endl;
    next_mover() == HUMAN ? cout << "           Player One's turn" << endl
                                 << endl
                          : cout << "            Player Two's turn" << endl
                                 << endl;
    cout << B_GREEN << BLACK << "                                      " << RESET << endl;
    cout << B_GREEN << BLACK << "     A   B   C   D   E   F   G   H    " << RESET << endl;
    size_t i;
    for (i = 0; i < 8; i++)
    {
        i > 0 ? cout << B_GREEN << BLACK << "   ├───┼───┼───┼───┼───┼───┼───┼───┤  " << RESET << endl : cout << B_GREEN << BLACK << "   ┌───┬───┬───┬───┬───┬───┬───┬───┐  " << RESET << endl;
        cout << B_GREEN << BLACK << " " << i + 1 << " │ " << board[i][0] << " │ " << board[i][1] << " │ " << board[i][2] << " │ " << board[i][3] << " │ " << board[i][4] << " │ " << board[i][5] << " │ " << board[i][6] << " │ " << board[i][7] << " │  " << RESET << endl;
    }
    cout << B_GREEN << BLACK << "   └───┴───┴───┴───┴───┴───┴───┴───┘  " << RESET << endl;
    cout << B_GREEN << BLACK << "                                      " << RESET << endl;
}

void Othello::compute_moves(std::queue<std::string> &move) const
{
    for (size_t row = 0; row < 8; row++)
    {
        for (size_t col = 0; col < 8; col++)
        {
            if (board[row][col].get_id() == 0)
            {
                if (is_legal(to_move(row, col)))
                {
                    move.push(to_move(row, col));
                }
            }
        }
    }
}

// Evaluate a board position:
// NOTE: positive values are good for the computer.
int Othello::evaluate() const
{
    int total = 0;
    for (size_t row = 0; row < 8; row++)
    {
        for (size_t col = 0; col < 8; col++)
        {
            if (board[row][col].get_id() == 1)
            {
                total++;
            }
            else if (board[row][col].get_id() == 2)
            {
                total--;
            }
        }
    }
    return total;
}
// Return true if the current game is finished:
bool Othello::is_game_over() const
{
    if (skip_amount == 2)
    {
        return 1;
    }
    else
    {
        int total = 0;
        for (size_t row = 0; row < 8; row++)
        {
            for (size_t col = 0; col < 8; col++)
            {
                if (board[row][col].get_id() != 0)
                {
                    total++;
                }
            }
        }
        return (total == 64 ? 1 : 0);
    }
}
Othello *Othello::clone() const
{
    return new Othello(*this);
}

// Restart the game from the beginning:
void Othello::restart()
{
    game::restart();
    for (size_t row = 0; row < 8; row++)
    {
        for (size_t column = 0; column < 8; column++)
        {
            board[row][column].cell_restart();
        }
    }
    board[3][3].heart_state();
    board[3][4].ace_state();
    board[4][3].ace_state();
    board[4][4].heart_state();
    skip_amount = 0;
}
// Have the next player make a specified move:
void Othello::make_move(const string &move)
{
    if (move == "skip")
    {
        skip_amount++;
    }
    else
    {
        int user_peice;
        next_mover() == HUMAN ? user_peice = 1 : user_peice = 2;
        int row = get_row(move);
        int col = get_col(move);
        queue<int> dir = get_dirs(move);
        while (!dir.empty())
        {
            if (dir.front() == 1)
            {
                // up
                if (check_dir(move, "up", user_peice))
                {
                    size_t i = row - 1;
                    while (i >= 0 && board[i][col].get_id() != user_peice && board[i][col].get_id() != 0)
                    {
                        // cout << "flip up" << endl;
                        board[i][col].flip();
                        i--;
                    }
                }
            }
            if (dir.front() == 2)
            {
                // up right
                if (check_dir(move, "up right", user_peice))
                {
                    size_t i = row - 1;
                    size_t j = col + 1;
                    while (i >= 0 && j < 8 && board[i][j].get_id() != user_peice && board[i][j].get_id() != 0)
                    {
                        // cout << "flip up right" << endl;
                        board[i][j].flip();
                        i--;
                        j++;
                    }
                }
            }
            if (dir.front() == 3)
            {
                // right
                if (check_dir(move, "right", user_peice))
                {
                    size_t i = col + 1;
                    while (i < 8 && board[row][i].get_id() != user_peice && board[row][i].get_id() != 0)
                    {
                        // cout << "flip right" << endl;
                        board[row][i].flip();
                        i++;
                    }
                }
            }
            if (dir.front() == 4)
            {
                // down right
                if (check_dir(move, "down right", user_peice))
                {
                    size_t i = row + 1;
                    size_t j = col + 1;
                    while (i < 8 && j < 8 && board[i][j].get_id() != user_peice && board[i][j].get_id() != 0)
                    {
                        // cout << "flip down right" << endl;
                        board[i][j].flip();
                        i++;
                        j++;
                    }
                }
            }
            if (dir.front() == 5)
            {
                // down
                if (check_dir(move, "down", user_peice))
                {
                    size_t i = row + 1;
                    while (i < 8 && board[i][col].get_id() != user_peice && board[i][col].get_id() != 0)
                    {
                        // cout << "flip down" << endl;
                        board[i][col].flip();
                        i++;
                    }
                }
            }
            if (dir.front() == 6)
            {
                // down left
                if (check_dir(move, "down left", user_peice))
                {
                    size_t i = row + 1;
                    size_t j = col - 1;
                    while (i < 8 && j >= 0 && board[i][j].get_id() != user_peice && board[i][j].get_id() != 0)
                    {
                        // cout << "flip down left" << endl;
                        board[i][j].flip();
                        i++;
                        j--;
                    }
                }
            }
            if (dir.front() == 7)
            {
                // left
                if (check_dir(move, "left", user_peice))
                {
                    size_t i = col - 1;
                    while (i >= 0 && board[row][i].get_id() != user_peice && board[row][i].get_id() != 0)
                    {
                        // cout << "flip left" << endl;
                        board[row][i].flip();
                        i--;
                    }
                }
            }
            if (dir.front() == 8)
            {
                // up left
                if (check_dir(move, "up left", user_peice))
                {
                    size_t i = row - 1;
                    size_t j = col - 1;
                    while (i >= 0 && j >= 0 && board[i][j].get_id() != user_peice && board[i][j].get_id() != 0)
                    {
                        // cout << "flip up left" << endl;
                        board[i][j].flip();
                        i--;
                        j--;
                    }
                }
            }
            dir.pop();
        }
        next_mover() == HUMAN ? board[row][col].heart_state() : board[row][col].ace_state();
    }
    game::make_move(move);
}

queue<int> Othello::get_dirs(const std::string &move) const
{
    queue<int> output;
    int row = get_row(move);
    int col = get_col(move);
    int target;
    next_mover() == HUMAN ? target = 2 : target = 1;
    // up
    if (row != 0)
        if (board[row - 1][col].get_id() == target)
            output.push(1);
    // up right
    if (row != 0 && col != 7)
        if (board[row - 1][col + 1].get_id() == target)
            output.push(2);
    // right
    if (col != 7)
        if (board[row][col + 1].get_id() == target)
            output.push(3);
    // down right
    if (row != 7 && col != 7)
        if (board[row + 1][col + 1].get_id() == target)
            output.push(4);
    // bottom
    if (row != 7)
        if (board[row + 1][col].get_id() == target)
            output.push(5);
    // down left
    if (row != 7 && col != 0)
        if (board[row + 1][col - 1].get_id() == target)
            output.push(6);
    // left
    if (col != 0)
        if (board[row][col - 1].get_id() == target)
            output.push(7);

    // up left
    if (row != 0 && col != 0)
        if (board[row - 1][col - 1].get_id() == target)
            output.push(8);

    return output;
}

int Othello::get_col(const string &move) const
{
    return toupper(move[0]) - 'A';
}
int Othello::get_row(const string &move) const
{
    return (move[1] - '0') - 1;
}

// Return true if the given move is legal for the next player:
// need to be done for part one
bool Othello::is_legal(const string &move) const
{
    // if move is a emtpy space then get the directions with the other players peice
    int legal_moves = 0;
    if (move == "skip")
    {
        ++legal_moves;
    }
    else
    {
        queue<int> dir = get_dirs(move);
        int user_peice;
        next_mover() == HUMAN ? user_peice = 1 : user_peice = 2;
        int row = get_row(move);
        int col = get_col(move);
        if (board[row][col].get_id() == 0)
        {
            while (!dir.empty())
            {
                if (dir.front() == 1)
                {
                    // up
                    // cout << "peice found up" << endl;
                    if (check_dir(move, "up", user_peice))
                        ++legal_moves;
                }
                if (dir.front() == 2)
                {
                    // up right
                    // cout << "peice found up right" << endl;
                    if (check_dir(move, "up right", user_peice))
                        ++legal_moves;
                }
                if (dir.front() == 3)
                {
                    // right
                    // cout << "peice found right" << endl;
                    if (check_dir(move, "right", user_peice))
                        ++legal_moves;
                }
                if (dir.front() == 4)
                {
                    // down right
                    // cout << "peice found down right" << endl;
                    if (check_dir(move, "down right", user_peice))
                        ++legal_moves;
                }
                if (dir.front() == 5)
                {
                    // down
                    // cout << "peice found down" << endl;
                    if (check_dir(move, "down", user_peice))
                        ++legal_moves;
                }
                if (dir.front() == 6)
                {
                    // down left
                    // cout << "peice found down left" << endl;
                    if (check_dir(move, "down left", user_peice))
                        ++legal_moves;
                }
                if (dir.front() == 7)
                {
                    // left
                    // cout << "peice found left" << endl;
                    if (check_dir(move, "left", user_peice))
                        ++legal_moves;
                }
                if (dir.front() == 8)
                {
                    // up left
                    // cout << "peice found up left" << endl;
                    if (check_dir(move, "up left", user_peice))
                        ++legal_moves;
                }
                dir.pop();
            }
        }
    }
    return (legal_moves > 0 ? 1 : 0);
}

// write function that returns true if peice exists in given direction
bool Othello::check_dir(const string move, const string dir, int peice) const
{
    int row = get_row(move);
    int col = get_col(move);
    if (dir == "right")
    {
        if (col != 7)
        {
            size_t i = col + 1;
            while (i < 8 && board[row][i].get_id() != 0)
            {
                // cout << "check right" << endl;
                if (board[row][i].get_id() == peice)
                    return 1;
                ++i;
            }
        }
    }
    else if (dir == "left")
    {
        if (col != 0)
        {
            size_t i = col - 1;
            while (i >= 0 && board[row][i].get_id() != 0)
            {
                // cout << "check left" << endl;
                if (board[row][i].get_id() == peice)
                    return 1;
                i--;
            }
        }
    }
    else if (dir == "up")
    {
        if (row != 0)
        {
            size_t i = row - 1;
            while (i >= 0 && board[i][col].get_id() != 0)
            {
                // cout << "check up" << endl;
                if (board[i][col].get_id() == peice)
                    return 1;
                i--;
            }
        }
    }
    else if (dir == "down")
    {
        if (row != 7)
        {
            size_t i = row + 1;
            while (i < 8 && board[i][col].get_id() != 0)
            {
                // cout << "check down" << endl;
                if (board[i][col].get_id() == peice)
                    return 1;
                i++;
            }
        }
    }
    else if (dir == "up left")
    {
        if (row != 0 && col != 0)
        {
            size_t i = row - 1;
            size_t j = col - 1;
            while (i >= 0 && j >= 0 && board[i][j].get_id() != 0)
            {
                // cout << "check up left" << endl;
                if (board[i][j].get_id() == peice)
                    return 1;
                i--;
                j--;
            }
        }
    }
    else if (dir == "up right")
    {
        if (row != 0 && col != 7)
        {
            size_t i = row - 1;
            size_t j = col + 1;
            while (i >= 0 && j < 8 && board[i][j].get_id() != 0)
            {
                // cout << "check up right" << endl;
                if (board[i][j].get_id() == peice)
                    return 1;
                i--;
                j++;
            }
        }
    }
    else if (dir == "down left")
    {
        if (row != 7 && col != 0)
        {
            size_t i = row + 1;
            size_t j = col - 1;
            while (i < 8 && j >= 0 && board[i][j].get_id() != 0)
            {
                // cout << "check down left" << endl;
                if (board[i][j].get_id() == peice)
                    return 1;
                i++;
                j--;
            }
        }
    }
    else if (dir == "down right")
    {
        if (row != 7 && col != 7)
        {
            size_t i = row + 1;
            size_t j = col + 1;
            while (i < 8 && j < 8 && board[i][j].get_id() != 0)
            {
                // cout << "check down right" << endl;
                if (board[i][j].get_id() == peice)
                    return 1;
                i++;
                j++;
            }
        }
    }
}