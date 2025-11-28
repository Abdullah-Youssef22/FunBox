/**
 * @file XO_Classes.h
 * @brief Defines the X-O (Tic-Tac-Toe) specific classes that extend the generic board game framework.
 *
 * This file provides:
 * - `X_O_Board`: A specialized board class for the Tic-Tac-Toe game.
 * - `XO_UI`: A user interface class tailored to X-O game setup and player interaction.
 */

#ifndef ULTIMATE_CLASSES_H
#define ULTIMATE_CLASSES_H

#include "util/BoardGame_Classes.h"
#include"util/colors.h"
using namespace std;


class Mini_Board : public Board<char> {
private:
    char winner = ' ';  // 'X', 'O', or ' '
    char blank_symbol = ' '; ///< Character used to represent an empty cell on the board.
    
public:
    Mini_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    
    char get_winner() const;
    void set_winner(char w);
    bool is_decided() const; 
};





class Mini_UI : public UI<char> {
public:
    Mini_UI();
    ~Mini_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};


// ====================================================================
//
//
/**
 * @class X_O_Board
 * @brief Represents the Tic-Tac-Toe game board.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for the Tic-Tac-Toe (X-O) game, including
 * move updates, win/draw detection, and display functions.
 *
 * @see Board
 */
class Ultimate_Board : public Board<char> {
private:
    friend class Ultimate_UI;
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.
    Mini_Board* miniBoards[3][3];
    char metaBoard[3][3];
    int activeMiniRow, activeMiniCol;  // -1 = any board
    
    // Helper methods
    int getMiniRow(int globalX) const;
    int getMiniCol(int globalY) const;
    int getLocalX(int globalX) const;
    int getLocalY(int globalY) const;
    
    void updateMetaBoard(int miniRow, int miniCol);
    bool isMiniboardPlayable(int miniRow, int miniCol) const;
    bool checkMetaBoardWin(char symbol) const;


public:
    Ultimate_Board();
    ~Ultimate_Board();  // Delete miniBoards
    
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool game_is_over(Player<char>* player) override;


    char getMetaBoardCell(int row, int col) const;
    Mini_Board* getMiniBoard(int row, int col) const;
    int getActiveMiniRow() const;
    int getActiveMiniCol() const;
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
class Ultimate_UI : public UI<char> {
private:
    void displaySingleMiniBoard(Mini_Board* mini, int miniRow, int miniCol, 
                                bool isActive) const;
    void displayMetaBoard(Ultimate_Board* board) const;
    
public:
    Ultimate_UI();
    
    // Override pure virtual functions
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    
    // Custom display for Ultimate board
    void display_ultimate_board(Ultimate_Board* board) const;
};




#endif // XO_CLASSES_H

