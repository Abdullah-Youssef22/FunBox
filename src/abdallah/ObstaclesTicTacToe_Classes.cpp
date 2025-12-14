#include <iostream>
#include <iomanip>
#include <cctype>  
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include "../../include/ObstaclesTicTacToe_Classes.h"
using namespace std;

/**
 * @class ObstaclesTicTacToeBoard
 * @brief Represents the board for Obstacles Tic Tac Toe.
 *
 * This variant uses a 6x6 board. When a player places 'O',
 * two random empty cells are converted into obstacles.
 */
ObstaclesTicTacToeBoard::ObstaclesTicTacToeBoard() : Board(6, 6) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol; ///< Initialize all cells as blank
}

/**
 * @brief Update the board with a player's move.
 *
 * If the move is valid, applies the symbol. If the symbol is 'O',
 * two random empty cells are turned into obstacles.
 *
 * @param move Pointer to the Move object containing coordinates and symbol
 * @return true if the move was valid and applied, false otherwise
 */
bool ObstaclesTicTacToeBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();
    mark = toupper(mark);

    if (x < 0 || x >= rows || y < 0 || y >= columns ||
        board[x][y] != blank_symbol) {
        return false;
    }

    board[x][y] = toupper(mark);
    n_moves++;

    // Special rule: placing 'O' adds two obstacles
    if (mark == 'O') {
        vector<pair<int, int>> empty_cells;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] == blank_symbol) {
                    empty_cells.push_back({ i, j });
                }
            }
        }

        if (empty_cells.size() >= 2) {
            int random_index1 = rand() % empty_cells.size();
            int random_row1 = empty_cells[random_index1].first;
            int random_col1 = empty_cells[random_index1].second;
            board[random_row1][random_col1] = obstacle_symbol;

            empty_cells.erase(empty_cells.begin() + random_index1);

            int random_index2 = rand() % empty_cells.size();
            int random_row2 = empty_cells[random_index2].first;
            int random_col2 = empty_cells[random_index2].second;
            board[random_row2][random_col2] = obstacle_symbol;

            n_moves += 2;
        }
    }
    return true;
}

/**
 * @brief Check if the player has won.
 *
 * A player wins if they have four consecutive symbols in a row,
 * column, or diagonal.
 *
 * @param player Pointer to the player
 * @return true if the player has won, false otherwise
 */
bool ObstaclesTicTacToeBoard::is_win(Player<char>* player) {
    const char sym = toupper(player->get_symbol());

    // Check rows
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == sym && board[i][j + 1] == sym &&
                board[i][j + 2] == sym && board[i][j + 3] == sym) {
                display_winner(player);
                return true;
            }
        }
    }

    // Check columns
    for (int j = 0; j < 6; ++j) {
        for (int i = 0; i < 3; ++i) {
            if (board[i][j] == sym && board[i + 1][j] == sym &&
                board[i + 2][j] == sym && board[i + 3][j] == sym) {
                display_winner(player);
                return true;
            }
        }
    }

    // Check main diagonals
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == sym && board[i + 1][j + 1] == sym &&
                board[i + 2][j + 2] == sym && board[i + 3][j + 3] == sym) {
                display_winner(player);
                return true;
            }
        }
    }

    // Check anti-diagonals
    for (int i = 0; i < 3; ++i) {
        for (int j = 3; j < 6; ++j) {
            if (board[i][j] == sym && board[i + 1][j - 1] == sym &&
                board[i + 2][j - 2] == sym && board[i + 3][j - 3] == sym) {
                display_winner(player);
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Check if the game is a draw.
 *
 * A draw occurs when all cells are filled and no player has won.
 *
 * @param player Pointer to the player
 * @return true if draw, false otherwise
 */
bool ObstaclesTicTacToeBoard::is_draw(Player<char>* player) {
    if (n_moves == 36 && !is_win(player)) {
        display_draw();
    }
    return n_moves == 36 && !is_win(player);
}

/**
 * @class ObstaclesTicTacToeUI
 * @brief User interface for Obstacles Tic Tac Toe.
 */
ObstaclesTicTacToeUI::ObstaclesTicTacToeUI()
    : UI<char>("Weclome to FCAI Obstacles Tic Tac Toe Game by Abdallah Youssef", 6) {}

/**
 * @brief Create a new player (human or computer).
 * @param name Player name
 * @param symbol Player symbol (X or O)
 * @param type Player type
 * @return Pointer to the newly created player
 */
Player<char>* ObstaclesTicTacToeUI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
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
Move<char>* ObstaclesTicTacToeUI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 5): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}

/**
 * @brief Check if the game is over.
 * @param player Pointer to the player
 * @return true if win or draw
 */
bool ObstaclesTicTacToeBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/**
 * @brief Display the winner message.
 * @param player Pointer to the winning player
 */
void ObstaclesTicTacToeBoard::display_winner(Player<char>* player)
{
    cout << GREEN << "Congratulations! " << player->get_name()
        << " You win the Obstacles Tic Tac Toe game!" << RESET << endl;
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

/**
 * @brief Display the draw message.
 */
void ObstaclesTicTacToeBoard::display_draw()
{
    cout << YELLOW << "The game ended in a draw!" << RESET << endl;
    cout << "Press any key to continue...";
    cin.ignore();
    cin.get();
}