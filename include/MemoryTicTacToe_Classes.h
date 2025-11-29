#ifndef MemoryTicTacToe_CLASSES_H
#define MemoryTicTacToe_CLASSES_H

#include "util/BoardGame_Classes.h"
#include"util/colors.h"
#include <vector>
using namespace std;


class MemoryTicTacToeBoard : public Board<char> {
private:
    char blank_symbol = '.';
    char memory_symbol = '!';
    vector<vector<char>> memory_board;
public:
    MemoryTicTacToeBoard();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
    void display_winner(Player<char>* player);
    void display_draw();
    void reveal_final_board();
};


class MemoryTicTacToeUI : public UI<char> {
public:
    MemoryTicTacToeUI();
    ~MemoryTicTacToeUI() {}
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};

#endif 
