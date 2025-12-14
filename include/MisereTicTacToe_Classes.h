#ifndef MISERE_TICTACTOE_H
#define MISERE_TICTACTOE_H

#include "util/BoardGame_Classes.h"
#include <iostream>
#include <utility>

using namespace std;

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

class MiserePlayer : public Player<char> {
public:
    MiserePlayer(string n, char s, PlayerType t)
        : Player(n, s, t) {
    }
};

// AI Player class
class MisereAIPlayer : public Player<char> {
private:
    int minimax(vector<vector<char>>& board, int depth, bool isMaximizing,
        char aiSymbol, char oppSymbol, int alpha, int beta);

    static bool check_three_in_row_static(const vector<vector<char>>& b, char sym);
    static bool is_board_full(const vector<vector<char>>& b);

public:
    MisereAIPlayer(string n, char s);
    pair<int, int> get_best_move();
};

// UI for Misere Tic Tac Toe
class MisereTicTacToeUI : public UI<char> {
public:
    MisereTicTacToeUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Player<char>** setup_players() override;
};

#endif // MISERE_TICTACTOE_H
