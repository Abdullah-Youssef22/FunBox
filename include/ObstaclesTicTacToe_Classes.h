
#ifndef ObstaclesTicTacToe_CLASSES_H
#define ObstaclesTicTacToe_CLASSES_H

#include "util/BoardGame_Classes.h"
#include"util/colors.h"
using namespace std;


class ObstaclesTicTacToeBoard : public Board<char> {
private:
    char blank_symbol = '.'; 
	char obstacle_symbol = '#';
    bool game_ended = false;
public:
    ObstaclesTicTacToeBoard();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player) { return false; };
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
	void display_winner(Player<char>* player);
	void display_draw();
    void handle_game_end(Player<char>* current_player);  

};


class ObstaclesTicTacToeUI : public UI<char> {
public:
    ObstaclesTicTacToeUI();
    ~ObstaclesTicTacToeUI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};

#endif 
