#pragma once 
#include <iostream>
#include "util/BoardGame_Classes.h"

class DimaondTicTacToe_Board : public Board<char> {
public :
	DimaondTicTacToe_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

private :
    /*bool checkThree(char sym); */
    /*bool checkFive(char sym);*/

    bool checkThreeinrows(char sym);
    bool checkThreeincolumns(char sym);
    bool checkThreeindiagonals(char sym);

    bool checkFourinrows(char sym);
    bool checkFourincolumns(char sym);
    bool checkFourindiagonals(char sym);
        
};

class DimaondPlayer : public Player<char> 
{
public : 

    DimaondPlayer(string n, char s, PlayerType t) : Player(n, s, t) {}
};

class DimaondUI : public UI<char> {

public :
    DimaondUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};
