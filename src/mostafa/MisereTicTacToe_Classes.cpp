#include "../../include/MisereTicTacToe_Classes.h"
#include <iostream>
#include "../../include/InfinityTicTacToe_Classes.h"
#include <util/colors.h>

using namespace std;

/**
 * @class MisereTicTacToeBoard
 * @brief Represents the board for Misère Tic Tac Toe.
 *
 * Misère Tic Tac Toe is a variant where the goal is NOT to win.
 * A player loses if they complete three in a row.
 */
MisereTicTacToeBoard::MisereTicTacToeBoard()
    : Board<char>(3, 3)
{
    for (auto& row : board)
        for (auto& cell : row)
            cell = '.'; ///< Initialize all cells as empty
}

/**
 * @brief Update the board with a player's move.
 *
 * Handles normal moves and undo moves.
 *
 * @param move Pointer to the Move object containing coordinates and symbol
 * @return true if the move was valid and applied, false otherwise
 */
bool MisereTicTacToeBoard::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == '.' || mark == 0)) {

        if (mark == 0) { ///< Undo move
            n_moves--;
            board[x][y] = '.';
        }
        else {           ///< Apply move
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

/**
 * @brief Check if a symbol has three in a row (row, column, or diagonal).
 * @param sym Symbol to check (X or O)
 * @return true if three in a row is found, false otherwise
 */
bool MisereTicTacToeBoard::check_three_in_row(char sym)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym)
            return true;
        if (board[0][i] == sym && board[1][i] == sym && board[2][i] == sym)
            return true;
    }
    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym)
        return true;
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym)
        return true;

    return false;
}

/**
 * @brief Check if the player has won.
 *
 * In Misère Tic Tac Toe, winning is not the goal.
 * This function always returns false.
 *
 * @param player Pointer to the player
 * @return false
 */
bool MisereTicTacToeBoard::is_win(Player<char>* player)
{
    return false;
}

/**
 * @brief Check if the player has lost.
 *
 * A player loses if they complete three in a row.
 *
 * @param player Pointer to the player
 * @return true if the player has three in a row, false otherwise
 */
bool MisereTicTacToeBoard::is_lose(Player<char>* player)
{
    char s = player->get_symbol();
    if (check_three_in_row(s))
    {
        cout << RED << player->get_name() << " YOU DIED" << RESET << "\n";
    }
    return check_three_in_row(s);
}

/**
 * @brief Check if the game is a draw.
 *
 * A draw occurs when all cells are filled and no player has three in a row.
 *
 * @param player Pointer to the player
 * @return true if draw, false otherwise
 */
bool MisereTicTacToeBoard::is_draw(Player<char>* player)
{
    return n_moves == rows * columns && !check_three_in_row('X') && !check_three_in_row('O');
}

/**
 * @brief Check if the game is over.
 *
 * The game ends when a player loses or when the game is a draw.
 *
 * @param player Pointer to the player
 * @return true if the game is finished
 */
bool MisereTicTacToeBoard::game_is_over(Player<char>* player)
{
    return is_lose(player) || is_draw(player);
}

/**
 * @class MisereTicTacToeUI
 * @brief User interface for Misère Tic Tac Toe.
 */
MisereTicTacToeUI::MisereTicTacToeUI()
    : UI<char>("Welcome to Misère Tic Tac Toe!", 3)
{
}

/**
 * @brief Get a move from the player.
 *
 * Human players enter coordinates manually.
 * Computer players choose random coordinates.
 *
 * @param player Pointer to the player
 * @return A new Move object
 */
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

/**
 * @brief Create a new player (human or computer).
 * @param name Player name
 * @param symbol Player symbol (X or O)
 * @param type Player type
 * @return Pointer to the newly created player
 */
Player<char>* MisereTicTacToeUI::create_player(string& name, char symbol, PlayerType type)
{
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new MiserePlayer(name, symbol, type);
}