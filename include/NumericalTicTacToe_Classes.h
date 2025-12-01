#pragma once
#include "util/BoardGame_Classes.h"
using namespace std;

class NumericalTicTacToe_Board : public Board<int> {
private:
    int start_symbol = 0; 
    bool used_numbers[10]; // 1 to 9 to track used digits

public:

    NumericalTicTacToe_Board();

    bool update_board(Move<int>* move) override;

    bool is_win(Player<int>* player) override;

    bool is_lose(Player<int>* player) override { return false; }

    bool is_draw(Player<int>* player) override;

    bool game_is_over(Player<int>* player) override;

    int calculate_score(int number);

    bool is_valid_number(Player<int>* player, int number);

    bool check_sum_15();

    int get_cell(int r, int c) const;
    
    bool is_used(int n) const;


};


class NumericalTicTacToe_UI : public UI<int> {
private:
    NumericalTicTacToe_Board* board;
public:

    NumericalTicTacToe_UI(NumericalTicTacToe_Board* b);

    ~NumericalTicTacToe_UI() {}

    Player<int>* create_player(string& name, int symbol, PlayerType type) override;

    Player<int>** setup_players() override;

    Move<int>* get_move(Player<int>* player) override;
};

