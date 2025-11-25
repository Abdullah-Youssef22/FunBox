#pragma once
#include "util/BoardGame_Classes.h"
using namespace std;


class SUS_Board : public Board<char> {
private:
    char start_symbol = '.'; 

public:

    SUS_Board(); 

    bool update_board(Move<char>* move);

    bool is_win(Player<char>* player);

    bool is_lose(Player<char>*) { return false; };

    bool is_draw(Player<char>* player);

    bool game_is_over(Player<char>* player);
    int calculate_score(char sym);
};



class SUS_UI : public UI<char> {
public:

    SUS_UI();


    ~SUS_UI() {};


    Player<char>* create_player(string& name, char symbol, PlayerType type);


    virtual Move<char>* get_move(Player<char>* player);
};
