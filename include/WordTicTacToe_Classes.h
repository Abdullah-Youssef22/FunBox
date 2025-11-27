#ifndef WordTicTacToe_Classes_h
#define WordTicTacToe_Classes_h

#include "util/BoardGame_Classes.h"
#include "util/colors.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;
class WordTicTacToe_board : public Board<char>
{
private:
	char blank_symbol = '.';
	vector<string> dictionary ;


	bool load_dictionary();
	bool is_valid_word(const string& word);
	bool check_all_words();
	
public:
	WordTicTacToe_board();
	~WordTicTacToe_board();
	bool update_board(Move<char>* move) ;
	bool is_win(Player<char>* player);
	bool is_lose(Player<char>* player) { return false; };
	bool is_draw(Player<char>* player);
	bool game_is_over(Player<char>* player);
	void desplay_winner(Player<char>* player);
};

class WordTicTacToe_UI : public UI<char>
{
public:
	WordTicTacToe_UI();
	~WordTicTacToe_UI();
	Player<char>* create_player(string& name, char symbol, PlayerType type);
	virtual Move<char>* get_move(Player<char>* player);

};

#endif 



