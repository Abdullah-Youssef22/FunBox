//--------------------------------------- IMPLEMENTATION

#include <cstddef>
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <utility>
#include <vector>
#include "../../include/PyramidTicTacToe_Classes.h"
#include "../../include/util/util.h"

using namespace std;

//--------------------------------------- X_O_Board Implementation

Pyramid_Board::Pyramid_Board() : Board(5, 5) {
    std::vector<std::pair<int, int>> printable = {
        {2, 2},
        {3, 1},
        {3, 2},
        {3, 3},
        {4, 0},
        {4, 1},
        {4, 2},
        {4, 3},
        {4, 4}
    };

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j] = '*';
        }
    }

    for (const std::pair<int, int> p : printable) {
        board[p.first][p.second] = blank_symbol;
    }

}

bool Pyramid_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {         // Apply move
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

bool Pyramid_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }

    // Check diagonals
    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}

bool Pyramid_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Pyramid_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- XO_UI Implementation

Pyramid_UI::Pyramid_UI() : UI<char>("Weclome to pyramid tictactoe game by ammen", 3) {
}

Player<char>* Pyramid_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Pyramid_UI::get_move(Player<char>* player) {
    int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}






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

