//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "../../include/TicTacToe4x4_Classes.h"

using namespace std;

//--------------------------------------- X_O_Board Implementation

FourByFour_Board::FourByFour_Board() : Board(4, 4) {
  cout << GREEN << "** Debug: inside 4x4 board constructor" << RESET << endl;
  for (int i = 0; i < board.size(); i++) {
    vector<char>& row = board[i];
    for (int j = 0; j < row.size(); j++) {
      char& cell = row[j];
      if (i == 0) {
        if (j%2 == 0) {
          cell = 'O';
        } else {
          cell = 'X';
        }
      } else if (i == 3) {
        if (j%2 == 1) {
          cell = 'O';
        } else {
          cell = 'X';
        }
      } else {
        cell =  blank_symbol; 
      }
    }
  }

}

bool FourByFour_Board::update_board(Move<char>* move) {
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

bool FourByFour_Board::is_win(Player<char>* player) {
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

bool FourByFour_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool FourByFour_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- XO_UI Implementation

FourByFour_UI::FourByFour_UI() : UI<char>("Weclome to 4x4 tic tac toe game by Ammen", 3) {}

Player<char>* FourByFour_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* FourByFour_UI::get_move(Player<char>* player) {
    int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move row and column (0 to 3): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}


Player<char> **FourByFour_UI::setup_players() {
  Player<char> **players = new Player<char> *[2];
  vector<string> type_options = {"Human", "Computer"};

  string nameX = get_player_name("Player X");
  PlayerType typeX = get_player_type_choice("Player X", type_options);
  players[0] = create_player(nameX, static_cast<char>('X'), typeX);

  string nameO = get_player_name("Player O");
  PlayerType typeO = get_player_type_choice("Player O", type_options);
  players[1] = create_player(nameO, static_cast<char>('O'), typeO);

  return players;
}


//========================================================================

class Token {
private: 
  int x_pos;
  int y_pos;
public:
  Token();
  ~Token();

  void setXpos(int x) {
    x_pos = x;
  }
  void setYpos(int y) {
    y_pos = y;
  }
  int getXpos() {
    return x_pos;
  }
  int getYpos() {
    return y_pos;
  }
};
