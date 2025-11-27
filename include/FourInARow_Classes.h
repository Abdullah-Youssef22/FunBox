/**
 * @file FourInARow_Classes.h
 * @brief Defines the FourInARow (Connect Four) specific classes that extend the generic board game framework.
 *
 * This file provides:
 * - `FourInARow_Board`: A specialized board class for the Connect Four game.
 * - `FourInARow_UI`: A user interface class tailored to Connect Four game setup and player interaction.
 */

#ifndef FOURINAROW_CLASSES_H
#define FOURINAROW_CLASSES_H
#include "util/BoardGame_Classes.h"
#include"util/colors.h"
using namespace std;

/**
 * @class FourInARow_Board
 * @brief Represents the Connect Four game board.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for the Connect Four game, including
 * move updates, win/draw detection, and display functions.
 *
 * @see Board
 */
class FourInARow_Board : public Board<char> {
private:
    char blank_symbol = ' '; ///< Character used to represent an empty cell on the board.

public:
    /**
     * @brief Default constructor that initializes a 6*7 Connect Four board.
     */
    FourInARow_Board();
    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object containing move coordinates and symbol.
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<char>* move);
    void reset_board();
    /**
     * @brief Checks if the given player has won the game.
     * @param player Pointer to the player being checked.
     * @return true if the player has a winning line, false otherwise.
     */
    int calculate_score(char sym);
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked.
     * @return Always returns false (not used in FourInARow logic).
     */

    bool is_lose(Player<char>*) override { return false; };
    /**
     * @brief Retrieves the symbol at a specific cell on the board.
     * @param row Row index of the cell.
     * @param col Column index of the cell.
     * @return Character symbol at the specified cell.
     */

    char get_board_cell(int row, int col) const;

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if all cells are filled and no player has won, false otherwise.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player);

    void print_board() const;
   
};


/**
 * @class XO_UI
 * @brief User Interface class for the X-O (Tic-Tac-Toe) game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * X-O specific functionality for player setup and move input.
 *
 * @see UI
 */
class FourInARow_UI : public UI<char> {
public:
    /**
     * @brief Constructs an XO_UI object.
     *
     * Initializes the base `UI<char>` class with the welcome message "FCAI X-O".
     */
    FourInARow_UI();

    /**
     * @brief Destructor for XO_UI.
     */
    ~FourInARow_UI() {};

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O') assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<char>` object representing the player's action.
     */
    Move<char>* get_move(Player<char>* player);


    Player<char> **setup_players() override;
};

//--------------------------------------- Exception handling / Debug

void errorInvalidMove();
void errorNoTokenHere(int y, int x);
void debugPrint(const string& message);

#endif // FOURINAROW_CLASSES_H
