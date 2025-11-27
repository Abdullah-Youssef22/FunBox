#include "../../include/MisereTicTacToe_Classes.h"
#include <iostream>
#include "../../include/InfinityTicTacToe_Classes.h"

using namespace std;


MisereTicTacToeBoard::MisereTicTacToeBoard()
    : Board<char>(3, 3)
{
    for (auto& row : board)
        for (auto& cell : row)
            cell = '.';
}

bool MisereTicTacToeBoard::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == '.' || mark == 0)) {

        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = '.';
        }
        else {         // Apply move
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}




bool MisereTicTacToeBoard::check_three_in_row(char sym)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym)
            return true;
        //====================================================================== 
        if (board[0][i] == sym && board[1][i] == sym && board[2][i] == sym)
            return true;
        //======================================================================  
    }
    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym)
        return true;
        //========================================================================== 
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym)
        return true;
	    //==========================================================================  

	return false;
}

bool MisereTicTacToeBoard::is_win(Player<char>* player)
{
	return false; // False because in misere_Tic_Tac_Toe, winning is not the goal
}

bool MisereTicTacToeBoard::is_lose(Player<char>* player)
{
    char s = player->get_symbol();
    return check_three_in_row(s);

}
bool MisereTicTacToeBoard::is_draw(Player<char>* player)
{
    return n_moves == rows * columns && !check_three_in_row('X') && !check_three_in_row('O');
}

bool MisereTicTacToeBoard::game_is_over(Player<char>* player)
{

    return is_lose(player) || is_draw(player);

}

MisereTicTacToeUI::MisereTicTacToeUI()
    : UI<char>("Welcome to Misère Tic Tac Toe!", 3)
{}

Move<char>* MisereTicTacToeUI::get_move(Player<char>* player)
{
    int x, y;
    if (player->get_type() == PlayerType::HUMAN)
    {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER)
    {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}

Player<char>* MisereTicTacToeUI::create_player(string& name, char symbol, PlayerType type)
{
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new MiserePlayer(name, symbol, type);
}
