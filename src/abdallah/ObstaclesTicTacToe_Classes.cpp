#include <iostream>
#include <iomanip>
#include <cctype>  
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include "../../include/ObstaclesTicTacToe_Classes.h"
using namespace std;

ObstaclesTicTacToeBoard::ObstaclesTicTacToeBoard() : Board(6, 6) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

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

bool ObstaclesTicTacToeBoard::is_win(Player<char>* player) {
    const char sym = toupper(player->get_symbol());

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == sym && board[i][j + 1] == sym &&
                board[i][j + 2] == sym && board[i][j + 3] == sym) {
                return true;
            }
        }
    }

    for (int j = 0; j < 6; ++j) {
        for (int i = 0; i < 3; ++i) {
            if (board[i][j] == sym && board[i + 1][j] == sym &&
                board[i + 2][j] == sym && board[i + 3][j] == sym) {
                return true;
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == sym && board[i + 1][j + 1] == sym &&
                board[i + 2][j + 2] == sym && board[i + 3][j + 3] == sym) {
                return true;
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 3; j < 6; ++j) {
            if (board[i][j] == sym && board[i + 1][j - 1] == sym &&
                board[i + 2][j - 2] == sym && board[i + 3][j - 3] == sym) {
                return true;
            }
        }
    }

    return false;
}

bool ObstaclesTicTacToeBoard::is_draw(Player<char>* player) {
   

	return n_moves == 36 && !is_win(player);
}


ObstaclesTicTacToeUI::ObstaclesTicTacToeUI() : UI<char>("Weclome to FCAI Obstacles Tic Tac Toe Game by Abdallah Youssef", 6) {}

Player<char>* ObstaclesTicTacToeUI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

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

bool ObstaclesTicTacToeBoard::game_is_over(Player<char>* player) {
	handle_game_end(player);    
    return game_ended;
}

void ObstaclesTicTacToeBoard::handle_game_end(Player<char>* current_player) {
    if (!game_ended) {
        if (is_win(current_player)) {
            display_winner(current_player);
        }
        else if (is_draw(current_player)) {
            display_draw();
        }
        cout << "Enter any character to exit the game: ";
        char exit_char;
        cin >> exit_char;
        game_ended = true;
    }
}

void ObstaclesTicTacToeBoard::display_winner(Player<char>* player) {
    cout << GREEN << "Congratulations! " << player->get_name()
        << " You win the Obstacles Tic Tac Toe game!" << RESET << endl;
}

void ObstaclesTicTacToeBoard::display_draw() {
    cout << YELLOW << "The game ended in a draw!" << RESET << endl;
}