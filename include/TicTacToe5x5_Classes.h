#ifndef TicTacToe5x5_Classes_h
#define TicTacToe5x5_Classes_h

#include "util/BoardGame_Classes.h"
#include "util/colors.h"
using namespace std;

class TicTacToe5x5_Board : public Board<char> 
{ 
private:
	char blank_symbol = '.';
	int player1_score = 0 ;
	int player2_score = 0;
	int count_sequences(char symbol);
public:
	TicTacToe5x5_Board();
	~TicTacToe5x5_Board();
	bool update_board(Move<char>* move);
	bool is_win(Player<char>* player);
	bool is_lose(Player<char>* player) { return false; };
	bool is_draw(Player<char>* player) ;
	bool game_is_over(Player<char>* player);
	void set_score(Player<char>* player);
	void get_score(Player<char>* player);
	void update_scores();
	void desplay_scores();
	bool end();
};

class TicTacToe5x5_UI : public UI<char> 
{
public:
	TicTacToe5x5_UI();
	~TicTacToe5x5_UI();
	Player<char>* create_player(string& name, char symbol, PlayerType type);
	virtual Move<char>* get_move(Player<char>* player);

};
#endif
