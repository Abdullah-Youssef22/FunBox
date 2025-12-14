/**
 * @file PyramidTicTacToe_Classes.cpp
 * @brief Implementation of Pyramid Tic-Tac-Toe game classes
 * @author Ammen
 *
 * This file contains the implementation of the Pyramid Tic-Tac-Toe game,
 * which uses a pyramid-shaped board instead of the traditional 3x3 grid.
 * The board has 9 playable positions arranged in a pyramid formation.
 */

 //--------------------------------------- IMPLEMENTATION

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <utility>
#include <vector>
#include "../../include/PyramidTicTacToe_Classes.h"
#include "../../include/util/util.h"

using namespace std;

//--------------------------------------- X_O_Board Implementation

// Forward declaration 
bool isPrintable(int y, int x);
void initPrintableLocations();

/// Static member to store valid playable positions on the pyramid board
std::vector<std::pair<int, int>> Pyramid_Board::printable;

/**
 * @brief Default constructor for Pyramid_Board
 *
 * Initializes a 5x5 board with pyramid-shaped playable positions.
 * The board has 9 valid positions arranged in a pyramid:
 * - Top level (row 2): 1 position
 * - Middle level (row 3): 3 positions
 * - Bottom level (row 4): 5 positions
 *
 * All non-playable positions are marked with '*', and playable positions
 * are initialized with the blank symbol.
 *
 * @note Calls the base Board constructor with dimensions 5x5
 * @see initPrintableLocations()
 */
Pyramid_Board::Pyramid_Board() : Board(5, 5) {
    initPrintableLocations();

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j] = '*';
        }
    }

    for (const std::pair<int, int> p : printable) {
        board[p.first][p.second] = blank_symbol;
    }
}

/**
 * @brief Updates the board with a player's move
 *
 * Validates and places a player's symbol on the board at the specified position.
 * The move is only valid if the target cell is currently blank.
 *
 * @param move Pointer to Move object containing position (x,y) and player symbol
 * @return true if the move was valid and successfully placed
 * @return false if the cell is already occupied
 *
 * @note Automatically converts the symbol to uppercase
 * @note Increments the move counter on successful placement
 */
bool Pyramid_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();
    if (board[x][y] == blank_symbol) {
        n_moves++;
        board[x][y] = toupper(mark);
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief Checks if the specified player has won the game
 *
 * Examines all possible winning combinations on the pyramid board:
 * - Three horizontal lines on the bottom row
 * - One horizontal line on the middle row
 * - One vertical line through the center
 * - Two diagonal lines from bottom corners to top
 * - Two diagonal lines from top to bottom corners
 *
 * @param player Pointer to the Player object to check for winning
 * @return true if the player has three symbols in a row
 * @return false if no winning combination exists
 *
 * @note Total of 9 possible winning combinations are checked
 */
bool Pyramid_Board::is_win(Player<char>* player) {
    const char sym = toupper(player->get_symbol());

    auto check = [&](int r1, int c1, int r2, int c2, int r3, int c3) {
        return board[r1][c1] == sym && 
               board[r2][c2] == sym && 
               board[r3][c3] == sym;
    };

    if (check(4, 0, 4, 1, 4, 2)) {display_winner (player) ; return true; }
    if (check(4,1, 4,2, 4,3)) { display_winner(player); return true;}
    if (check(4,2, 4,3, 4,4)) { display_winner(player); return true;}
    if (check(3,1, 3,2, 3,3)) { display_winner(player); return true;}
    if (check(2,2, 3,2, 4,2)) { display_winner(player); return true;}
    if (check(2,2, 3,1, 4,0)) { display_winner(player); return true;}
    if (check(2,2, 3,3, 4,4)) { display_winner(player); return true;}
    if (check(4,0, 3,1, 2,2)) { display_winner(player); return true;}
    if (check(4, 4, 3, 3, 2, 2)) { display_winner(player); return true; }

    return false;
}

/**
 * @brief Checks if the game has ended in a draw
 *
 * A draw occurs when all 9 playable positions are filled and no player has won.
 *
 * @param player Pointer to the current Player object
 * @return true if the game is a draw (9 moves made and no winner)
 * @return false if the game is not yet a draw
 */
bool Pyramid_Board::is_draw(Player<char>* player) {
    if (n_moves == 9 && !is_win(player)) {
		display_draw();
    }
    return (n_moves == 9 && !is_win(player));
}

/**
 * @brief Checks if the game has reached a terminal state
 *
 * @param player Pointer to the current Player object
 * @return true if the game is won or drawn
 * @return false if the game can continue
 *
 * @see is_win()
 * @see is_draw()
 */
bool Pyramid_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

void Pyramid_Board::display_winner(Player<char>* player) {
    cout << GREEN << "\nCongratulations " << player->get_name()
        << "! You have won the game as player " << player->get_symbol() << "!" << RESET << endl;
    cout << "\nGame Over! Press Enter to continue...";
    cin.ignore();
    cin.get();
}
void Pyramid_Board::display_draw() {
    cout << YELLOW << "\nThe game ended in draw!" << RESET << endl;
    cout << "\nGame Over! Press Enter to continue...";
    cin.ignore();
    cin.get();
}

//--------------------------------------- XO_UI Implementation

/**
 * @brief Default constructor for Pyramid_UI
 *
 * Initializes the user interface with a welcome message and specifies
 * that the game uses a pyramid board with 3 rows (pyramid levels).
 */
Pyramid_UI::Pyramid_UI() : UI<char>("Weclome to pyramid tictactoe game by ammen", 3) {
}

/**
 * @brief Factory method to create a player object
 *
 * Creates either a human or computer player with the specified parameters.
 * Prints confirmation message of player creation.
 *
 * @param name Reference to string containing the player's name
 * @param symbol The symbol assigned to the player ('X' or 'O')
 * @param type PlayerType enum indicating HUMAN or COMPUTER player
 * @return Player<char>* Pointer to newly created Player object
 *
 * @warning Caller is responsible for deallocating the returned Player object
 */
Player<char>* Pyramid_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets a move from the player (human or computer)
 *
 * For human players, prompts for position input via console and validates
 * that the position is within the pyramid's playable area.
 * For computer players, generates random valid positions within the pyramid.
 *
 * @param player Pointer to the Player object making the move
 * @return Move<char>* Pointer to newly created Move object containing the player's move
 *
 * @note Human input is validated to ensure it's within the pyramid shape
 * @note Invalid moves trigger error messages and re-prompt the user
 * @note Computer moves are automatically validated before being returned
 * @warning Caller is responsible for deallocating the returned Move object
 *
 * @see isPrintable()
 */
Move<char>* Pyramid_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move row and column: ";
        cin >> y >> x;
        if (!isPrintable(y, x)) {
            while (true) {
                util::errorInvalidMove();
                cout << "\nPlease enter your move row and column: ";
                cin >> y >> x;
                if (isPrintable(y, x)) {
                    break;
                }
            }
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
        while (!isPrintable(x, y)) {
            x = rand() % player->get_board_ptr()->get_rows();
            y = rand() % player->get_board_ptr()->get_columns();
        }
    }
    return new Move<char>(y, x, player->get_symbol());
}

/**
 * @brief Sets up both players for the game
 *
 * Prompts for player names and types (Human or Computer) for both Player X
 * and Player O. Creates and returns an array of two player objects.
 *
 * @return Player<char>** Array of two Player pointers [Player X, Player O]
 *
 * @note Players[0] is always Player X
 * @note Players[1] is always Player O
 * @warning Caller is responsible for deallocating both the array and the player objects
 *
 * @see create_player()
 * @see get_player_name()
 * @see get_player_type_choice()
 */
Player<char>** Pyramid_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, static_cast<char>('X'), typeX);

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, static_cast<char>('O'), typeO);

    return players;
}

/**
 * @brief Checks if a position is within the pyramid's playable area
 *
 * Validates whether the given coordinates correspond to a valid position
 * in the pyramid structure by checking against the list of printable positions.
 *
 * @param y Row coordinate of the position to check
 * @param x Column coordinate of the position to check
 * @return true if the position is playable (within pyramid boundaries)
 * @return false if the position is outside the pyramid or non-playable
 *
 * @note Uses the static Pyramid_Board::printable vector for validation
 * @see initPrintableLocations()
 */
bool isPrintable(int y, int x) {
    for (const auto& p : Pyramid_Board::printable) {
        if (p.first == y && p.second == x) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Initializes the list of valid playable positions on the pyramid board
 *
 * Populates the Pyramid_Board::printable vector with all 9 valid positions
 * that form the pyramid shape:
 * - Row 2: position (2,2) - pyramid top
 * - Row 3: positions (3,1), (3,2), (3,3) - pyramid middle
 * - Row 4: positions (4,0), (4,1), (4,2), (4,3), (4,4) - pyramid base
 *
 * @note This function should be called once during board initialization
 * @note Modifies the static Pyramid_Board::printable vector
 */
void initPrintableLocations() {
    Pyramid_Board::printable.push_back({ 2, 2 });
    Pyramid_Board::printable.push_back({ 3, 1 });
    Pyramid_Board::printable.push_back({ 3, 2 });
    Pyramid_Board::printable.push_back({ 3, 3 });
    Pyramid_Board::printable.push_back({ 4, 0 });
    Pyramid_Board::printable.push_back({ 4, 1 });
    Pyramid_Board::printable.push_back({ 4, 2 });
    Pyramid_Board::printable.push_back({ 4, 3 });
    Pyramid_Board::printable.push_back({ 4, 4 });
}