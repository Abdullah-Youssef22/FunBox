//--------------------------------------- IMPLEMENTATION
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>  // for toupper()
#include "../../include/SUS_Classes.h"

using namespace std;

//--------------------------------------- SUS_Board Implementation

/**
 * @class SUS_Board
 * @brief Represents the game board for the SUS game.
 *
 * Inherits from Board and manages moves, scoring, and game state.
 */
SUS_Board::SUS_Board() : Board(3, 3) {

    move_order.resize(3, vector<int>(3, -1));
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = start_symbol;
}

/**
 * @brief Sets up the players for the SUS game.
 *
 * Prompts for player names and types (Human/Computer).
 *
 * @return Pointer array of two Player<char> objects.
 */
Player<char>** SUS_UI::setup_players() {
    Player<char>** players = new Player<char> *[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameS = get_player_name("Player S");
    PlayerType typeS = get_player_type_choice("Player S", type_options);
    players[0] = create_player(nameS, static_cast<char>('S'), typeS);

    string nameU = get_player_name("Player U");
    PlayerType typeU = get_player_type_choice("Player U", type_options);
    players[1] = create_player(nameU, static_cast<char>('U'), typeU);
    return players;
}

/**
 * @brief Updates the board with a given move.
 *
 * Validates the move, applies it if valid, or undoes it if mark == 0.
 *
 * @param move Pointer to the Move<char> object.
 * @return true if the move was successfully applied or undone, false otherwise.
 */
bool SUS_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == start_symbol || mark == 0)) {

        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = start_symbol;
        }
        else {         // Apply move
            move_order[x][y] = n_moves;
            board[x][y] = toupper(mark);
            n_moves++;
        }
        return true;
    }

    return false;
}

/**
 * @brief Calculates the score for a given symbol.
 *
 * Checks all rows, columns, and diagonals for the "SUS" pattern.
 * Only counts if the last move in the pattern belongs to the given symbol.
 *
 * @param sym The symbol ('S' or 'U') to calculate score for.
 * @return The score for the given symbol.
 */
int SUS_Board::calculate_score(char sym) {
    int score = 0;

    auto check_SUS = [&](int r1, int c1, int r2, int c2, int r3, int c3) {
        if (board[r1][c1] == 'S' &&
            board[r2][c2] == 'U' &&
            board[r3][c3] == 'S') {

            // Determine which move was placed last
            /* which move was placed last?? */
            int last_move = max({ move_order[r1][c1],
                                move_order[r2][c2],
                                move_order[r3][c3] });

            if (move_order[r1][c1] == last_move && board[r1][c1] == sym) score++;
            else if (move_order[r2][c2] == last_move && board[r2][c2] == sym) score++;
            else if (move_order[r3][c3] == last_move && board[r3][c3] == sym) score++;
        }
        };

    // Check rows
    for (int i = 0; i < rows; ++i) {
        check_SUS(i, 0, i, 1, i, 2);
    }

    // Check columns  
    for (int i = 0; i < columns; ++i) {
        check_SUS(0, i, 1, i, 2, i);
    }

    // Check diagonals
    check_SUS(0, 0, 1, 1, 2, 2);
    check_SUS(0, 2, 1, 1, 2, 0);

    return score;
}

/**
 * @brief Determines if the given player has won.
 *
 * A player wins if their score is greater than the opponent's score
 * after all moves are played.
 *
 * @param player Pointer to the Player<char> object.
 * @return true if the player has won, false otherwise.
 */
bool SUS_Board::is_win(Player<char>* player) {

    if (n_moves < rows* columns)
        return false;

    int score_S = calculate_score('S');
    int score_U = calculate_score('U');
    if (!displayed)
    {
        display_scores();
    }
    if (player->get_symbol() == 'S') {
        return score_S > score_U;
    }
    else {
        return score_U > score_S;
    }

}

/**
 * @brief Determines if the game is a draw.
 *
 * A draw occurs when all cells are filled and no player has won.
 *
 * @param player Pointer to the Player<char> object.
 * @return true if the game is a draw, false otherwise.
 */
bool SUS_Board::is_draw(Player<char>* player) {

    return (n_moves == rows * columns && !is_win(player));
}

/**
 * @brief Checks if the game is over.
 *
 * The game is over if either a player has won or the game is a draw.
 *
 * @param player Pointer to the Player<char> object.
 * @return true if the game is over, false otherwise.
 */
bool SUS_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

void SUS_Board::display_scores() {

    int score_S = calculate_score('S');
    int score_U = calculate_score('U');
    cout << "\nScores:\n";
    if (score_S > score_U) {

        cout << GREEN << "Player S: " << score_S << RESET << "\n";
        cout << RED << "Player U: " << score_U << RESET << "\n";
        cout << GREEN << "Player S is the winner!" << RESET << "\n";
    }

    else if (score_U > score_S) {
        cout << RED << "Player S: " << score_S << RESET << "\n";
        cout << GREEN << "Player U: " << score_U << RESET << "\n";
        cout << GREEN << "Player U is the winner!" << RESET << "\n";
    }
    else
    {
        cout << YELLOW << "Player S: " << score_S << RESET << "\n";
        cout << YELLOW << "Player U: " << score_U << RESET << "\n";
        cout << YELLOW << "The game is a draw!" << RESET << "\n";
    }
    cout << "\nGame Over! Press Enter to continue...";
    cin.ignore();
    cin.get();
    displayed = true;
}






//--------------------------------------- SUS_UI Implementation

/**
 * @class SUS_UI
 * @brief Handles user interaction for the SUS game.
 *
 * Provides methods to create players and get moves from them.
 */
SUS_UI::SUS_UI() : UI<char>("Weclome to FCAI SUS Game in FUN BOX By SAMIR", 3) {}

/**
 * @brief Creates a player object.
 *
 * @param name The name of the player.
 * @param symbol The symbol ('S' or 'U') assigned to the player.
 * @param type The type of player (Human or Computer).
 * @return Pointer to the created Player<char> object.
 */
Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets the next move from a player.
 *
 * If the player is human, prompts for input.
 * If the player is computer, generates a random move.
 *
 * @param player Pointer to the Player<char> object.
 * @return Pointer to the created Move<char> object.
 */
Move<char>* SUS_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x access and y access (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}
