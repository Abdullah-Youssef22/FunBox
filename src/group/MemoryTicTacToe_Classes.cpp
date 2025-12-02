#include <iostream>
#include <iomanip>
#include <cctype>  
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include "../../include/MemoryTicTacToe_Classes.h"
using namespace std;


MemoryTicTacToeBoard::MemoryTicTacToeBoard() : Board(3, 3), memory_board(3, vector<char>(3, blank_symbol)) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool MemoryTicTacToeBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();
    mark = toupper(mark);
    if (x < 0 || x >= rows || y < 0 || y >= columns ||
        board[x][y] != blank_symbol) {
        return false;
    }
	memory_board[x][y] = mark;
    board[x][y] = memory_symbol;
    n_moves++;
    return true;
}


bool MemoryTicTacToeBoard::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((all_equal(memory_board[i][0], memory_board[i][1], memory_board[i][2]) && memory_board[i][0] == sym) ||
            (all_equal(memory_board[0][i], memory_board[1][i], memory_board[2][i]) && memory_board[0][i] == sym))
        {
            display_winner(player);
            return true;
        }
    }

    // Check diagonals
    if ((all_equal(memory_board[0][0], memory_board[1][1], memory_board[2][2]) && memory_board[1][1] == sym) ||
        (all_equal(memory_board[0][2], memory_board[1][1], memory_board[2][0]) && memory_board[1][1] == sym))
    {
        display_winner(player);
        return true;
    }

    return false;
}

bool MemoryTicTacToeBoard::is_draw(Player<char>* player) {

    if (n_moves == 9 && !is_win(player))
    {
        display_draw();
    }
    return n_moves == 9 && !is_win(player);
}

bool MemoryTicTacToeBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

void MemoryTicTacToeBoard::display_winner(Player<char>* player)
{
    reveal_final_board();

    cout << "\nFinal Board Revealed!\n";
    cout << GREEN << "\n Congratulations! " << player->get_name()
        << " You win the Memory Tic Tac Toe game! " << RESET << endl;
    cout << "Press any key to continue...";
    cin.ignore();  
    cin.get();     
}

void MemoryTicTacToeBoard::display_draw()
{
    reveal_final_board();
    cout << "\nFinal Board Revealed!\n";
    cout << YELLOW << "\nThe game ended in a draw!" << RESET << endl;
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();     
}

MemoryTicTacToeUI::MemoryTicTacToeUI() : UI<char>("Welcome to FCAI Memory Tic Tac Toe Game by Abdallah Youssef", 3) {}

Player<char>* MemoryTicTacToeUI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* MemoryTicTacToeUI::get_move(Player<char>* player) {
    int x, y;
    cout << "Player " << player->get_name() << ", enter your move (row and column): ";
    cin >> x >> y;
    return new Move<char>(x, y, player->get_symbol());
}


void MemoryTicTacToeBoard::reveal_final_board() {

    cout << "\nCurrent Board:\n";
    cout << "-------------\n";
    for (int i = 0; i < rows; ++i) {
        cout << "| ";
        for (int j = 0; j < columns; ++j) {
            cout << memory_board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}