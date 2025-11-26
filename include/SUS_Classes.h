#pragma once
#include "util/BoardGame_Classes.h"
using namespace std;


class SUS_Board : public Board<char> {
private:
    char start_symbol = '.'; 
    bool winner_printed = false;
    SUS_UI* ui_ptr;
public:

    SUS_Board(SUS_UI* ui);
    
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

    Player<char> **setup_players() override;

    virtual Move<char>* get_move(Player<char>* player);
};
