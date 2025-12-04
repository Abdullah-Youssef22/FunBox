//--------------------------------------- IMPLEMENTATION
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>  // for toupper()
#include "../../include/SUS_Classes.h"

using namespace std;

//--------------------------------------- SUS_Board Implementation

SUS_Board::SUS_Board() : Board(3, 3) {

    move_order.resize(3, vector<int>(3, -1)); 
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = start_symbol;
}

Player<char> **SUS_UI::setup_players() {
  Player<char> **players = new Player<char> *[2];
  vector<string> type_options = {"Human", "Computer"};

  string nameS = get_player_name("Player S");
  PlayerType typeS = get_player_type_choice("Player S", type_options);
  players[0] = create_player(nameS, static_cast<char>('S'), typeS);

  string nameU = get_player_name("Player U");
  PlayerType typeU = get_player_type_choice("Player U", type_options);
  players[1] = create_player(nameU, static_cast<char>('U'), typeU);
  return players;
}

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

int SUS_Board::calculate_score(char sym) {
    int score = 0;
    
    auto check_SUS = [&](int r1, int c1, int r2, int c2, int r3, int c3) {
        if (board[r1][c1] == 'S' && 
            board[r2][c2] == 'U' && 
            board[r3][c3] == 'S') {
            
            /* which move was placed last?? */
            int last_move = max({move_order[r1][c1], 
                                move_order[r2][c2], 
                                move_order[r3][c3]});
            
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


bool SUS_Board::is_win(Player<char>* player) {

    if (n_moves < rows * columns)
        return false;

    int score_S = calculate_score('S');
    int score_U = calculate_score('U');

    if (player->get_symbol() == 'S')
        return score_S > score_U;
    else
        return score_U > score_S;
}


bool SUS_Board::is_draw(Player<char>* player) {
    return (n_moves == rows * columns && !is_win(player));
}


bool SUS_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}


//--------------------------------------- SUS_UI Implementation

SUS_UI::SUS_UI() : UI<char>("Weclome to FCAI SUS Game in FUN BOX By SAMIR", 3) {}

Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

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
