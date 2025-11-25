#ifndef	INFINITY_TICTACTOE_H
#define	INFINITY_TICTACTOE_H
#include "util/BoardGame_Classes.h"
#include <iostream>
#include<queue>
#include<utility>
using namespace std; 

class Infinity_TicTacToe_Board : public Board<char>{

public :
    Infinity_TicTacToe_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
private:
    bool checking(char sym);
    queue<pair<int, int>> moveQueue;	
};

class Infinity_TicTacToe_Player : public Player<char>
{
public:
    Infinity_TicTacToe_Player(string n, char s, PlayerType t): Player(n, s, t) {}
};

class Infinity_TicTacToe_UI : public  UI<char>
{
public:
    Infinity_TicTacToe_UI();
    Move<char>* get_move(Player<char>* player) override;

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};



#endif INFINITY_TICTACTOE_H