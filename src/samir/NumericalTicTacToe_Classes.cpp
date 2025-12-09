//--------------------------------------- IMPLEMENTATION
#include <iostream>
#include <iomanip> 
#include <limits>
#include <cctype>  // for toupper()
#include "../../include/NumericalTicTacToe_Classes.h"

using namespace std;

//--------------------------------------- NumericalTicTacToe_Board Implementation
/**
 * @class NumericalTicTacToe_Board
 * @brief Represents the board for the Numerical Tic Tac Toe game.
 *
 * The board is a 3x3 grid where players place numbers (1–9).
 * Player 1 uses odd numbers, Player 2 uses even numbers.
 * A player wins if any row, column, or diagonal sums to 15.
 */

NumericalTicTacToe_Board::NumericalTicTacToe_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    cout << "debug: NumericalTicTacToe" << endl;
    for (auto& row : board)
        for (auto& cell : row)
            cell = start_symbol;
    
    for (int i = 0; i < 10; i++)
        used_numbers[i] = false;

}
/**
 * @brief Checks if a number is valid for the given player.
 *
 * - Must be between 1 and 9.
 * - Must not have been used before.
 * - Player 1 can only use odd numbers.
 * - Player 2 can only use even numbers.
 *
 * @param player Pointer to the player making the move.
 * @param number The number to validate.
 * @return true if the number is valid, false otherwise.
 */

bool NumericalTicTacToe_Board::is_valid_number(Player<int>* player, int number) {
    if (number < 1 || number > 9)
        return false;

    if (used_numbers[number])
        return false;

    // Player 1 uses odd numbers
    if (player->get_symbol() == 1 && (number % 2 == 0))
        return false;

    // Player 2 uses even numbers
    if (player->get_symbol() == 2 && (number % 2 != 0))
        return false;

    return true;
}

/**
 * @brief Updates the board with a given move.
 *
 * Validates the move before applying it. Marks the number as used.
 *
 * @param move Pointer to the Move<int> object.
 * @return true if the move was successfully applied, false otherwise.
 */

bool NumericalTicTacToe_Board::update_board(Move<int>* move) {
    int r = move->get_x(); 
    int c = move->get_y();
    int num = move->get_symbol();

    if (r < 0 || r >= rows || c < 0 || c >= columns) return false;
    if (board[r][c] != 0) return false;
    if (num < 1 || num > 9) return false;
    if (used_numbers[num]) return false;

    

    board[r][c] = num;
    used_numbers[num] = true;
    return true;
}
/**
 * @brief Checks if any row, column, or diagonal sums to 15.
 *
 * @return true if a winning condition is met, false otherwise.
 */


bool NumericalTicTacToe_Board::check_sum_15() {
    // rows
    for (int i = 0; i < 3; i++) {
        int s = board[i][0] + board[i][1] + board[i][2];
        if (s == 15 && board[i][0] && board[i][1] && board[i][2])
            return true;
    }

    // columns
    for (int j = 0; j < 3; j++) {
        int s = board[0][j] + board[1][j] + board[2][j];
        if (s == 15 && board[0][j] && board[1][j] && board[2][j])
            return true;
    }

    // main diagonal
    int d1 = board[0][0] + board[1][1] + board[2][2];
    if (d1 == 15 && board[0][0] && board[1][1] && board[2][2])
        return true;

    // secondary diagonal
    int d2 = board[0][2] + board[1][1] + board[2][0];
    if (d2 == 15 && board[0][2] && board[1][1] && board[2][0])
        return true;

    return false;
}
/**
 * @brief Determines if the given player has won.
 *
 * @param player Pointer to the Player<int> object.
 * @return true if the player has won, false otherwise.
 */
bool NumericalTicTacToe_Board::is_win(Player<int>* player) {
    // if there is any line = 15
    return check_sum_15();
}
/**
 * @brief Determines if the game is a draw.
 *
 * A draw occurs when the board is full and no winning condition is met.
 *
 * @param player Pointer to the Player<int> object.
 * @return true if the game is a draw, false otherwise.
 */

bool NumericalTicTacToe_Board::is_draw(Player<int>* player) {
    if (check_sum_15())
        return false;

    // check if board is full
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == 0)
                return false;

    return true;
}
/**
 * @brief Checks if the game is over.
 *
 * The game ends if there is a win or a draw.
 *
 * @param player Pointer to the Player<int> object.
 * @return true if the game is over, false otherwise.
 */

bool NumericalTicTacToe_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}
/**
 * @brief Calculates score for a given number.
 *
 * In this implementation, the score is simply the number itself.
 *
 * @param number The number played.
 * @return The score value.
 */

int NumericalTicTacToe_Board::calculate_score(int number) {
    return number;
}
/**
 * @brief Gets the value of a cell.
 *
 * @param r Row index.
 * @param c Column index.
 * @return The number in the cell, or 0 if empty.
 */

int NumericalTicTacToe_Board::get_cell(int r, int c) const {
    return board[r][c];
}
/**
 * @brief Checks if a number has already been used.
 *
 * @param n The number to check.
 * @return true if the number is used, false otherwise.
 */

bool NumericalTicTacToe_Board::is_used(int n) const {
    return used_numbers[n];
}

//--------------------------------------- NumericalTicTacToe_UI Implementation
/**
 * @class NumericalTicTacToe_UI
 * @brief Handles user interaction for the Numerical Tic Tac Toe game.
 *
 * Provides methods to create players and get moves from them.
 */

NumericalTicTacToe_UI::NumericalTicTacToe_UI(NumericalTicTacToe_Board* b)
    : UI<int>("Welcome to FCAI NumericalTicTacToe Game in FUN BOX By SAMIR", 3), board(b) {}

/**
 * @brief Creates a player object.
 *
 * @param name The name of the player.
 * @param symbol The symbol (1 for odd, 2 for even).
 * @param type The type of player (Human or Computer).
 * @return Pointer to the created Player<int> object.
 */

// create_player: symbol هنا = 1 أو 2 (مش رقم اللعبة)
Player<int>* NumericalTicTacToe_UI::create_player(string& name, int symbol, PlayerType type) {
    return new Player<int>(name, symbol, type);
}
/**
 * @brief Sets up the two players for the game.
 *
 * Player 1 uses odd numbers, Player 2 uses even numbers.
 *
 * @return Pointer array of two Player<int> objects.
 */


Player<int>** NumericalTicTacToe_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];

    vector<string> type_options = {"Human", "Computer"};

    // Player 1 (odd numbers)
    string name1 = get_player_name("Player 1 (Odd Numbers)");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 1, type1);

    // Player 2 (even numbers)
    string name2 = get_player_name("Player 2 (Even Numbers)");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 2, type2);

    return players;
}
/**
 * @brief Gets the next move from a player.
 *
 * - If the player is computer: chooses the first available cell and valid number.
 * - If the player is human: prompts for input (row, column, number).
 *
 * @param player Pointer to the Player<int> object.
 * @return Pointer to the created Move<int> object.
 */

Move<int>* NumericalTicTacToe_UI::get_move(Player<int>* player) {
    if (player->get_type() == PlayerType::COMPUTER) {
        // الكمبيوتر يختار أول خانة فاضية ورقم متاح حسب الفردي/الزوجي
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                if (board->get_cell(r, c) == 0) { // خانة فاضية
                    // البحث عن رقم متاح حسب الفردي/الزوجي
                    for (int num = 1; num <= 9; num++) {
                        bool correct_parity =
                            (player->get_symbol() == 1 && num % 2 == 1) ||
                            (player->get_symbol() == 2 && num % 2 == 0);

                        if (correct_parity && !board->is_used(num)) {
                            cout << "Computer plays: " << r << " " << c << " " << num << endl;

                            // تحديث البورد مباشرة لتفادي اختيار نفس الخانة مرة أخرى
                            board->update_board(new Move<int>(r, c, num));

                            // ترجع الـ Move بعد التحديث
                            return new Move<int>(r, c, num);
                        }
                    }
                }
            }
        }

        // لو وصلنا هنا معناه ما فيش تحركات صالحة
        cout << "ERROR: computer found no valid moves.\n";
        return new Move<int>(0, 0, 1);
    }

    // ================================
    // HUMAN PLAYER
    // ================================
    int x, y, number;

    cout << "\nPlayer " << player->get_symbol()
         << " turn. Enter: row col number (e.g. 0 2 7)\n";

    while (true) {
        cout << "Input: ";
        if (!(cin >> x >> y >> number)) {
            cout << "Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (x < 0 || x > 2 || y < 0 || y > 2 || number < 1 || number > 9) {
            cout << "Values out of range. Rows and cols must be 0..2. Number must be 1..9.\n";
            continue;
        }

        return new Move<int>(x, y, number);
    }
}
