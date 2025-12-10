//--------------------------------------- IMPLEMENTATION
#include <vector>
#include <string>
#include <cstdlib> // rand
#include <ctime>   // لو هتعمل srand(time(nullptr));

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "../../include/FourInARow_Classes.h"

using namespace std;

//--------------------------------------- FourInARow Implementation

//======================================================================== FourByFour_UI


//FORWARD DECLARATIONS
void errorNoTokenHere(int y, int x);
void errorInvalidMove();
void debugPrint(const string& message);


//========================================================================
void FourInARow_Board::reset_board() {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            board[r][c] = blank_symbol;
    n_moves = 0; 
}

FourInARow_Board::FourInARow_Board() : Board(6, 7) {//6 rows, 7 columns
  reset_board();
}

bool FourInARow_Board::update_board(Move<char>* move) {
    if (!move) return false;

    int col = move->get_y();               
    char mark = static_cast<char>(toupper(move->get_symbol()));


    if (col < 0 || col >= columns) return false;


    for (int r = rows - 1; r >= 0; --r) {
        if (board[r][col] == blank_symbol) {
            board[r][col] = mark;
            ++n_moves;
            return true;
        }
    }


    return false;
}
int FourInARow_Board::calculate_score(char sym) {
    sym = static_cast<char>(toupper(sym));
    int count = 0;

    const int dr[4] = {0, 1, 1, 1};
    const int dc[4] = {1, 0, 1, -1};

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {


            if (toupper(board[r][c]) != sym) continue;

            for (int d = 0; d < 4; ++d) {
                bool ok = true;

                for (int k = 1; k < 4; ++k) {
                    int nr = r + dr[d] * k;
                    int nc = c + dc[d] * k;

                    if (nr < 0 || nr >= rows || nc < 0 || nc >= columns)
                    {
                        ok = false;
                        break;
                    }


                    if (toupper(board[nr][nc]) != sym) {
                        ok = false;
                        break;
                    }
                }

                if (ok) ++count;
            }
        }
    }
    return count;
}

/*
 is_win:
 Return true immediately if the player has at least one 4-in-a-row.
*/
bool FourInARow_Board::is_win(Player<char>* player) {
    if (!player) return false;
    char sym = static_cast<char>(toupper(player->get_symbol()));
    if (calculate_score(sym) > 0)
    {
        cout<<GREEN << "=====================================\n"
             << "  the winner is player: " << sym << "\n"
             << "=====================================\n" << RESET;
        cout << "\nGame Over! Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
    return calculate_score(sym) > 0;
}

/*
 is_draw:
 True when board is full and nobody has a winning 4-in-a-row.
*/
bool FourInARow_Board::is_draw(Player<char>* player) {
    if (n_moves < rows * columns) { return false; }

    if (n_moves < rows * columns && !is_win(player))
    {
        cout << YELLOW << "=====================================\n"
            << "  it's a draw! \n"
            << "=====================================\n" << RESET;
        cout << "\nGame Over! Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
    return (calculate_score('X') == 0 && calculate_score('O') == 0);
}

/*
 game_is_over:
 True if either win or draw.

bool FourInARow_Board::game_is_over(Player<char>* player) {

    return is_win(player) || is_draw(player);
}*/
void FourInARow_Board::print_board() const {
    cout << "       ";
    for (int c = 0; c < columns; ++c) cout << c << "   ";
    cout << endl;
    for (int r = 0; r < rows; ++r) {
        cout << "   -----------------------------------\n";
        cout << " " << r << " |";
        for (int c = 0; c < columns; ++c) {
            cout << " " << board[r][c] << " |";
        }
        cout << endl;
    }
    cout << "   -----------------------------------\n";
}

bool FourInARow_Board::game_is_over(Player<char>* player) {
    if (calculate_score('X') > 0) {
        cout << "=====================================\n";
        cout << "  the winner is player X 🥳\n";
        cout << "=====================================\n";
        return true;
    }

    if (calculate_score('O') > 0) {
        cout << "=====================================\n";
        cout << "  the winner is player O 🥳\n";
        cout << "=====================================\n";
        return true;
    }

    if (is_draw(player)) {
        cout << "=====================================\n";
        cout << "  it's a draw! 🤝\n";
        cout << "=====================================\n";
        return true;
    }

    return false;
}



char FourInARow_Board::get_board_cell(int row, int col) const {
    return board[row][col];
}

//========================================================================
// FourInARow_UI Methods
FourInARow_UI::FourInARow_UI() : UI<char>("Welcome to Four in a Row game by SAMIR", 3) {
    srand(static_cast<unsigned>(time(nullptr))); 
}

Player<char>* FourInARow_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* FourInARow_UI::get_move(Player<char>* player) {
    if (!player) return nullptr; 

    Board<char>* board_ptr = player->get_board_ptr();
    auto* fir = dynamic_cast<FourInARow_Board*>(board_ptr);
    if (!fir) {
        cout << "Internal error: board is not FourInARow_Board\n";
        return nullptr;
    }

    int rows = board_ptr->get_rows();
    int columns = board_ptr->get_columns();
    int column = -1;
    char symbol = player->get_symbol();

    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << GREEN << "\nPlayer " << symbol << RESET 
             << ": please enter the column (0-" << columns-1 << ") to drop your token: ";
        cin >> column;

        if (column < 0 || column >= columns) {
            cout << RED << "** ERROR: invalid column" << RESET << endl;
            return nullptr;
        }

        int row = -1;
        for (int r = rows - 1; r >= 0; --r) {
            if (fir->get_board_cell(r, column) == ' ') {
                row = r;
                break;
            }
        }

        if (row == -1) {
            cout << RED << "** ERROR: column full" << RESET << endl;
            return nullptr;
        }

        return new Move<char>(row, column, symbol);
    } 

   
    else if (player->get_type() == PlayerType::COMPUTER) {
        int row = -1;
        do {
            column = rand() % columns;
            for (int r = rows - 1; r >= 0; --r) {
                if (fir->get_board_cell(r, column) == ' ') {
                    row = r;
                    break;
                }
            }
        } while (row == -1);

        return new Move<char>(row, column, symbol);
    }

    
    return nullptr;
}

Player<char> **FourInARow_UI::setup_players() {
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


/////////////////////////////////////////////////////
/// Exception handling 
/// ////////////////////////////////////////////////
void errorInvalidMove() {
  cout << RED << "\n** ERROR: invalid move, please re-enter your move" << RESET;
}

void errorNoTokenHere(int y, int x) {
  cout << RED << "** ERROR: no token at row " << y << " column " << x << RESET;
} 

void debugPrint(const string& message) {
    cout << GREEN << "** Debug: " << message << RESET << endl;
}
