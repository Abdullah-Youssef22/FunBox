#include"WordTicTacToe_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream>
#include <algorithm>

bool WordTicTacToe_board::is_valid_word(const string& word) {
    return find(dictionary.begin(), dictionary.end(), word) != dictionary.end();
}

bool WordTicTacToe_board::check_all_words() {
    for (int i = 0; i < 3; i++) {
        string row_word = "";
        row_word += board[i][0];
        row_word += board[i][1];
        row_word += board[i][2];

        if (row_word[0] != blank_symbol && row_word[1] != blank_symbol && row_word[2] != blank_symbol) {
            if (is_valid_word(row_word)) {
                cout << "Valid word found in row " << i << ": " << row_word << endl;
                return true;
            }
        }
    }

    for (int j = 0; j < 3; j++) {
        string col_word = "";
        col_word += board[0][j];
        col_word += board[1][j];
        col_word += board[2][j];

        if (col_word[0] != blank_symbol && col_word[1] != blank_symbol && col_word[2] != blank_symbol) {
            if (is_valid_word(col_word)) {
                cout << "Valid word found in column " << j << ": " << col_word << endl;
                return true;
            }
        }
    }

    string diag1 = "";
    diag1 += board[0][0];
    diag1 += board[1][1];
    diag1 += board[2][2];
    if (diag1[0] != blank_symbol && diag1[1] != blank_symbol && diag1[2] != blank_symbol) {
        if (is_valid_word(diag1)) {
            cout << "Valid word found in main diagonal: " << diag1 << endl;
            return true;
        }
    }

    string diag2 = "";
    diag2 += board[0][2];
    diag2 += board[1][1];
    diag2 += board[2][0];
    if (diag2[0] != blank_symbol && diag2[1] != blank_symbol && diag2[2] != blank_symbol) {
        if (is_valid_word(diag2)) {
            cout << "Valid word found in secondary diagonal: " << diag2 << endl;
            return true;
        }
    }

    return false;
}


WordTicTacToe_board::WordTicTacToe_board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

WordTicTacToe_board::~WordTicTacToe_board()
{
}

bool WordTicTacToe_board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char letter = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3) {
        cout << "Invalid position! Please choose between 0-2 for both x and y." << endl;
        return false;
    }

    if (board[x][y] != blank_symbol) {
        cout << "This cell is already occupied! Choose another one." << endl;
        return false;
    }

    letter = toupper(letter);
    if (letter < 'A' || letter > 'Z') {
        cout << "Invalid letter! Please choose a letter from A to Z." << endl;
        return false;
    }

    board[x][y] = letter;
    n_moves++;

    cout << "Placed letter '" << letter << "' at position (" << x << ", " << y << ")" << endl;
    return true;
}

bool WordTicTacToe_board::is_win(Player<char>* player) {
    if (check_all_words())
    {
		desplay_winner(player);
		return true;
    }
	return false;
}

bool WordTicTacToe_board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool WordTicTacToe_board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

void WordTicTacToe_board::desplay_winner(Player<char>* player)
{
    cout << "\n*** " << player->get_name() << " wins by forming a valid 3-letter word! ***" << endl;
    cout << "Press any character to continue...";
    char end;
    cin >> end;
}

WordTicTacToe_UI::WordTicTacToe_UI():UI<char>("Weclome to FCAI WordTicTacToe Game by Abdallah Youssef", 3) {}

WordTicTacToe_UI::~WordTicTacToe_UI()
{
}


Player<char>* WordTicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << endl;
    return new Player<char>(name, '?', type); 
}
Move<char>* WordTicTacToe_UI::get_move(Player<char>* player) {
    int x, y;
    char letter;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << ", enter your move:" << endl;
        cout << "Enter letter (A-Z): ";
        cin >> letter;
        cout << "Enter position x and y (0-2): ";
        cin >> x >> y;
    }
    else {
        letter = 'A' + (rand() % 26);
        x = rand() % 3;
        y = rand() % 3;
        cout << "Computer " << player->get_name() << " chooses letter '"
            << letter << "' at position (" << x << ", " << y << ")" << endl;
    }

    return new Move<char>(x, y, letter);
}