#ifndef MISERE_TICTACTOE_H
#define MISERE_TICTACTOE_H

#include "util/BoardGame_Classes.h"
#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////////
// Misère Tic Tac Toe Board
///////////////////////////////////////////////////////////////

class MisereTicTacToeBoard : public Board<char> {
public:
    MisereTicTacToeBoard();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

private:
    bool check_three_in_row(char sym);
};

///////////////////////////////////////////////////////////////
// Player for Misère Tic Tac Toe
///////////////////////////////////////////////////////////////

class MiserePlayer : public Player<char> {
public:
    MiserePlayer(string n, char s, PlayerType t)
        : Player(n, s, t) {
    }
};

// UI for Misere Tic Tac Toe

class MisereTicTacToeUI : public UI<char> {
public:
    MisereTicTacToeUI();

    Move<char>* get_move(Player<char>* player) override;

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif // MISERE_TICTACTOE_H
