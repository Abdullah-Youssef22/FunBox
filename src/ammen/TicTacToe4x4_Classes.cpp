//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <cmath>
#include "../../include/TicTacToe4x4_Classes.h"
#include "../../include/util/util.h"
using namespace std;

//--------------------------------------- X_O_Board Implementation

//======================================================================== 
class Token {
private: 
  int x_pos;
  int y_pos;
public:
  void move(int y, int x) {
    y_pos = y;
    x_pos = x;
  }
  pair<int, int> getPos() const {
    return {y_pos, x_pos};
  }
};


//FORWARD DECLARATIONS
void setInitialPositions();
void putTokensAtPositions();
void findAndUpdateToken(int y, int x, int targetY, int targetX);
Token* getTokenAtPosition(int y, int x);
void debugIsTokenAtYX(int y, int x);
bool checkTargetTokenValidity(int y, int x, char);
bool isTokenAtYX(int y, int x);

typedef vector<pair<int, int>> positionsArray;
positionsArray getOPositions();
positionsArray getXPositions();

Token O1, O2, O3, O4, X1, X2, X3, X4; 
//========================================================================

FourByFour_Board::FourByFour_Board() : Board(4, 4) {
  setInitialPositions();
  putTokensAtPositions();
}

bool FourByFour_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns)) {
        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {         // Apply move
            n_moves++;
            putTokensAtPositions(); 
        }
        return true;
    }
    util::errorInvalidMove();
    return false;
}

bool FourByFour_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
    };

    // Check rows and columns
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; j++) {

            if ((all_equal(board[i][j], board[i][j+1], board[i][j+2]) && board[i][j] == sym) ||
                (all_equal(board[j][i], board[j+1][i], board[j+2][i]) && board[j][i] == sym)) {
                display_winner(player);
                return true;
            }
        }
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; j++) {
            if ((all_equal(board[i][j], board[i+1][j+1], board[i+2][j+2]) && board[i][j] == sym) ||
                (all_equal(board[i][j+2], board[i+1][j+1], board[i+2][j]) && board[i+1][j+1] == sym)) {
                display_winner(player);
                return true;
            }
        }
    }

    return false;
}

bool FourByFour_Board::is_draw(Player<char>* player) {
    if (n_moves == 9 && !is_win(player)) {
		display_draw();
    }

    return (n_moves == 9 && !is_win(player));
}

bool FourByFour_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

void FourByFour_Board::putTokensAtPositions() {
  positionsArray oSpots = getOPositions();
  positionsArray xSpots = getXPositions();
  for (int i = 0; i < board.size(); i++) {
    vector<char>& row = board[i];
    for (int j = 0; j < row.size(); j++) {
      char& cell = row[j];
      cell =  blank_symbol; 
      for (int k = 0; k < 4; k++) {
        if (i == oSpots[k].first && j == oSpots[k].second) {
          cell = 'O';
        } else if (i == xSpots[k].first && j == xSpots[k].second) {
          cell = 'X';
        }
      }
    }
  }
}


void FourByFour_Board::display_winner(Player<char>* player) {
    cout << GREEN << "\nCongratulations " << player->get_name() 
         << "! You have won the game as player " << player->get_symbol() << "!" << RESET << endl;
    cout << "\nGame Over! Press Enter to continue...";
    cin.ignore();
    cin.get();
}
void FourByFour_Board::display_draw() {
    cout << YELLOW << "\nThe game ended in a draw!" << RESET << endl;
    cout << "\nGame Over! Press Enter to continue...";
    cin.ignore();
    cin.get();
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
    int x, y, targetX, targetY;
    char symbol = player->get_symbol(); 
    if (player->get_type() == PlayerType::HUMAN) {
        cout << GREEN << "\nPlayer " << symbol << RESET << ": please enter target token position (row, column): ";
        cin >> y >> x;
        if (!checkTargetTokenValidity(y, x, symbol)) {
          while (true) {
            cout << RED << "** ERROR: please select a valid " << symbol << " token" << RESET;
            cout << "\nPlease select a valid target token (row, column): ";
            cin >> y >> x;
            if (isTokenAtYX(y, x)) {
              break;
            }
          }      
        } 
        cout << "\nWhere do you want to move it? (row, column): ";
        cin >> targetY >> targetX;
        int diffX, diffY, diffYandX;

        diffX = targetX - x;
        diffY = targetY - y;
        diffYandX = abs(diffX) + abs(diffY);

        while (isTokenAtYX(targetY, targetX) || abs(diffX) > 1 || abs(diffY) > 1 || diffYandX > 1) {
          util::errorInvalidMove(); 
          cout << "\nWhere do you want to move it? (row, column): ";
          cin >> targetY >> targetX;
          diffX = targetX - x;
          diffY = targetY - y;
          diffYandX = abs(diffX) + abs(diffY);
        }      
        findAndUpdateToken(y, x, targetY, targetX);
        return new Move<char>(targetX, targetY, symbol);
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
        return new Move<char>(x, y, symbol);
    }
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


// ===================================================

void setInitialPositions(){
  O1.move(0, 0);
  O2.move(0, 2);
  O3.move(3, 1);
  O4.move(3, 3);
  X1.move(0, 1);
  X2.move(0, 3);
  X3.move(3, 0);
  X4.move(3, 2);
}

positionsArray getOPositions() {
  positionsArray arr;

  arr.push_back(O1.getPos());
  arr.push_back(O2.getPos());
  arr.push_back(O3.getPos());
  arr.push_back(O4.getPos());
  return arr;
}
positionsArray getXPositions() {
  positionsArray arr;

  arr.push_back(X1.getPos());
  arr.push_back(X2.getPos());
  arr.push_back(X3.getPos());
  arr.push_back(X4.getPos());
  return arr;
}

bool checkTargetTokenValidity(int y, int x, char symbol) {
  if (symbol == 'O') {
    positionsArray oPos = getOPositions();
    for(auto tok : oPos) {
      if (tok.first == y && tok.second == x) {
        return true;
      } 
    }
    return false;
  } else {
    positionsArray xPos = getXPositions();
    for(auto tok : xPos) {
      if (tok.first == y && tok.second == x) {
        return true;
      } 
    }
    return false;
  }
}

void findAndUpdateToken(int y, int x, int targetY, int targetX) {
  Token* tok = getTokenAtPosition(y, x);
  if (tok != nullptr) {
    tok->move(targetY, targetX);
  }
}

Token* getTokenAtPosition(int y, int x) {
  Token* tokens[] = {&O1, &O2, &O3, &O4, &X1, &X2, &X3, &X4};
  for (Token* token : tokens) {
    auto pos = token->getPos();
    if (pos.first == y && pos.second == x) {
      return token;
    }
  }
  return nullptr;
}

bool isTokenAtYX(int y, int x) {
  const Token* tmptok = getTokenAtPosition(y, x);
  if (tmptok != nullptr) {
    return true;
  } else {
    return false;
  }
}

/////////////////////////////////////////////////////
/// Exception handling 
/// ////////////////////////////////////////////////

void debugIsTokenAtYX(int y, int x) {
  if (isTokenAtYX(y, x)) {
    std::cout << GREEN << "\n** Debug: token found at y x: " << y << " "<< x << RESET << std::endl;
  }
}

