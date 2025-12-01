#ifndef FOURINAROW_CLASSES_H
#define FOURINAROW_CLASSES_H
#include "util/BoardGame_Classes.h"
#include"util/colors.h"
using namespace std;

class FourInARow_Board : public Board<char> {
private:
    char blank_symbol = ' ';

public:
    FourInARow_Board();
    bool update_board(Move<char>* move);
    void reset_board();
    int calculate_score(char sym);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*) override { return false; };
    char get_board_cell(int row, int col) const;
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
    void print_board() const;
};

class FourInARow_UI : public UI<char> {
public:
    FourInARow_UI();
    ~FourInARow_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    Move<char>* get_move(Player<char>* player);
    Player<char> **setup_players() override;
};

void errorInvalidMove();
void errorNoTokenHere(int y, int x);
void debugPrint(const string& message);

#endif // FOURINAROW_CLASSES_H
