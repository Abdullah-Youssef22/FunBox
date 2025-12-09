#include "WordTicTacToe_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream>
#include <algorithm>

bool WordTicTacToe_board::is_valid_word(const string & word) {
    return find(dictionary.begin(), dictionary.end(), word) != dictionary.end();
}

bool WordTicTacToe_board::check_all_words() {
    for (int i = 0; i < 3; i++) {
        string row_word_1 = "", row_word_2 = "";
        row_word_1 += board[i][0];
        row_word_1 += board[i][1];
        row_word_1 += board[i][2];

        row_word_2 += board[i][2];
        row_word_2 += board[i][1];
        row_word_2 += board[i][0];

        if (row_word_1[0] != blank_symbol && row_word_1[1] != blank_symbol && row_word_1[2] != blank_symbol) {
            if (is_valid_word(row_word_1)) {
                valid_word = row_word_1;
                cout << "Valid word found in row " << i << ": " << row_word_1 << endl;
                return true;
            }
        }
        if (row_word_2[0] != blank_symbol && row_word_2[1] != blank_symbol && row_word_2[2] != blank_symbol) {
            if (is_valid_word(row_word_2)) {
                valid_word = row_word_2;
                cout << "Valid word found in row " << i << ": " << row_word_2 << endl;
                return true;
            }
        }

    }

    for (int j = 0; j < 3; j++) {
        string col_word_1 = "", col_word_2 = "";
        col_word_1 += board[0][j];
        col_word_1 += board[1][j];
        col_word_1 += board[2][j];

        col_word_2 += board[2][j];
        col_word_2 += board[1][j];
        col_word_2 += board[0][j];

        if (col_word_1[0] != blank_symbol && col_word_1[1] != blank_symbol && col_word_1[2] != blank_symbol) {
            if (is_valid_word(col_word_1)) {
                valid_word = col_word_1;
                cout << "Valid word found in column " << j << ": " << col_word_1 << endl;
                return true;
            }
        }
        if (col_word_2[0] != blank_symbol && col_word_2[1] != blank_symbol && col_word_2[2] != blank_symbol) {
            if (is_valid_word(col_word_2)) {
                valid_word = col_word_2;
                cout << "Valid word found in column " << j << ": " << col_word_2 << endl;
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
            valid_word = diag1;
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
            valid_word = diag2;
            cout << "Valid word found in secondary diagonal: " << diag2 << endl;
            return true;
        }
    }

    string diag3 = "";
    diag3 += board[2][2];
    diag3 += board[1][1];
    diag3 += board[0][0];
    if (diag3[0] != blank_symbol && diag3[1] != blank_symbol && diag3[2] != blank_symbol) {
        if (is_valid_word(diag3)) {
            valid_word = diag3;
            cout << "Valid word found in main diagonal: " << diag3 << endl;
            return true;
        }
    }

    string diag4 = "";
    diag4 += board[2][0];
    diag4 += board[1][1];
    diag4 += board[0][2];
    if (diag4[0] != blank_symbol && diag4[1] != blank_symbol && diag4[2] != blank_symbol) {
        if (is_valid_word(diag4)) {
            valid_word = diag4;
            cout << "Valid word found in main diagonal: " << diag4 << endl;
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
    if (n_moves == 9 && !is_win(player))
    {
        display_draw();
    }
    return (n_moves == 9 && !is_win(player));
}

bool WordTicTacToe_board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

void WordTicTacToe_board::desplay_winner(Player<char>* player)
{
    cout << "\n" << GREEN << "***" << player->get_name() << " wins by forming a valid 3 - letter word!(" << valid_word << ")***" << RESET << endl;
    cout << "Press any key to continue...";
    cin.ignore();
    cin.get();
}

void WordTicTacToe_board::display_draw()
{
    cout << YELLOW << "The game ended in a draw!" << RESET << endl;
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

vector<vector<char>> WordTicTacToe_board::get_board_matrix() const {
    vector<vector<char>> matrix(3, vector<char>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = board[i][j];
        }
    }
    return matrix;
}

// ============= WordTicTacToe_AIPlayer Implementation =============

WordTicTacToe_AIPlayer::WordTicTacToe_AIPlayer(string n, char s, WordTicTacToe_board* board)
    : Player<char>(n, s, PlayerType::AI), boardPtr(board) {}

bool WordTicTacToe_AIPlayer::is_valid_word_in_dict(const string& word,
    const vector<string>& dict) {
    if (word.find('.') != string::npos) return false;
    return find(dict.begin(), dict.end(), word) != dict.end();
}

int WordTicTacToe_AIPlayer::count_valid_words_in_board(const vector<vector<char>>& board,
    const vector<string>& dict) {
    int count = 0;

    // Check rows
    for (int i = 0; i < 3; i++) {
        string row = "";
        row += board[i][0];
        row += board[i][1];
        row += board[i][2];
        if (is_valid_word_in_dict(row, dict)) count++;
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        string col = "";
        col += board[0][j];
        col += board[1][j];
        col += board[2][j];
        if (is_valid_word_in_dict(col, dict)) count++;
    }

    // Check diagonals
    string diag1 = "";
    diag1 += board[0][0];
    diag1 += board[1][1];
    diag1 += board[2][2];
    if (is_valid_word_in_dict(diag1, dict)) count++;

    string diag2 = "";
    diag2 += board[0][2];
    diag2 += board[1][1];
    diag2 += board[2][0];
    if (is_valid_word_in_dict(diag2, dict)) count++;

    return count;
}

int WordTicTacToe_AIPlayer::evaluate_board_state(const vector<vector<char>>& board,
    const vector<string>& dict) {
    int score = 0;

    int valid_words = count_valid_words_in_board(board, dict);
    if (valid_words > 0) {
        return 10000; 
    }

   

    return score;
}

int WordTicTacToe_AIPlayer::minimax(vector<vector<char>>& board, int depth,
    bool isMaximizing, int alpha, int beta, int maxDepth) {

    // Check terminal state
    int valid_words = count_valid_words_in_board(board, boardPtr->get_dictionary());
    if (valid_words > 0) {
        return isMaximizing ? -10000 + depth : 10000 - depth;
    }

    // Check if board is full
    bool isFull = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '.') {
                isFull = false;
                break;
            }
        }
        if (!isFull) break;
    }

    if (isFull || depth >= maxDepth) {
        return evaluate_board_state(board, boardPtr->get_dictionary());
    }

    const vector<string>& dict = boardPtr->get_dictionary();

    if (isMaximizing) {
        int maxEval = -10000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '.') {
                    // Try some common letters
                    string letters = "AEIOU";
                    for (char letter : letters) {
                        board[i][j] = letter;
                        int eval = minimax(board, depth + 1, false, alpha, beta, maxDepth);
                        board[i][j] = '.';

                        maxEval = max(maxEval, eval);
                        alpha = max(alpha, eval);
                        if (beta <= alpha) break;
                    }
                }
            }
        }
        return maxEval;
    }
    else {
        int minEval = 10000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '.') {
                    string letters = "AEIOU";
                    for (char letter : letters) {
                        board[i][j] = letter;
                        int eval = minimax(board, depth + 1, true, alpha, beta, maxDepth);
                        board[i][j] = '.';

                        minEval = min(minEval, eval);
                        beta = min(beta, eval);
                        if (beta <= alpha) break;
                    }
                }
            }
        }
        return minEval;
    }
}

WordTicTacToe_AIPlayer::MoveEval WordTicTacToe_AIPlayer::get_best_move() {
    int bestScore = -10000;
    vector<vector<char>> board = boardPtr->get_board_matrix();
    MoveEval bestMove = { 0, 0, 'A', bestScore };

    const vector<string>& dict = boardPtr->get_dictionary();

    string letters = "AEIOUBCDFGHJKLMNPQRSTVWXYZ";

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '.') {
                for (char letter : letters) {
                    board[i][j] = letter;

                    if (count_valid_words_in_board(board, dict) > 0) {
                        board[i][j] = '.';
                        return { i, j, letter, 10000 }; 
                    }

                    int score = minimax(board, 0, false, -10000, 10000, 2);
                    board[i][j] = '.';

                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = { i, j, letter, score };
                    }
                }
            }
        }
    }

    return bestMove;
}

Move<char>* WordTicTacToe_AIPlayer::make_ai_move() {
    MoveEval best = get_best_move();
    cout << "AI " << get_name() << " chooses letter '"
        << best.letter << "' at position ("
        << best.x << ", " << best.y << ")" << endl;
    return new Move<char>(best.x, best.y, best.letter);
}


// ============= WordTicTacToe_UI Implementation =============


WordTicTacToe_UI::WordTicTacToe_UI() :UI<char>("Weclome to FCAI WordTicTacToe Game by Abdallah Youssef", 3) {}

WordTicTacToe_UI::~WordTicTacToe_UI()
{
}

Player<char>* WordTicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating ";
    if (type == PlayerType::HUMAN) cout << "human";
    else if (type == PlayerType::COMPUTER) cout << "computer (random)";
    else if (type == PlayerType::AI) cout << "AI (smart)";
    cout << " player: " << name << "\n";
    return new Player<char>(name, '?', type);
}

WordTicTacToe_AIPlayer* WordTicTacToe_UI::create_ai_player(string& name, char symbol, WordTicTacToe_board* board) {
    return new WordTicTacToe_AIPlayer(name, symbol, board);
}

Move<char>* WordTicTacToe_UI::get_move(Player<char>* player) {
    int x = 0, y = 0;
    char letter = 'A';

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << ", enter your move:" << endl;
        cout << "Enter letter (A-Z): ";
        cin >> letter;
        cout << "Enter position x and y (0-2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // Random move for computer
        letter = 'A' + (rand() % 26);
        x = rand() % 3;
        y = rand() % 3;
        cout << "Computer " << player->get_name() << " chooses letter '"
            << letter << "' at position (" << x << ", " << y << ")" << endl;
    }
    else if (player->get_type() == PlayerType::AI) {
        // Cast to AI player and get best move
        WordTicTacToe_AIPlayer* aiPlayer = dynamic_cast<WordTicTacToe_AIPlayer*>(player);
        if (aiPlayer) {
            Move<char>* aiMove = aiPlayer->make_ai_move();
            return aiMove;
        }
    }

    return new Move<char>(x, y, letter);
}

Player<char>** WordTicTacToe_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];

    cout << "Enter Player 1 name: ";
    string name1;
    getline(cin >> ws, name1);

    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Computer (Random)\n";
    cout << "3. AI (Smart)\n";
    int choice1;
    cin >> choice1;
    PlayerType type1 = (choice1 == 2) ? PlayerType::COMPUTER :
        (choice1 == 3) ? PlayerType::AI : PlayerType::HUMAN;

    cout << "Enter Player 2 name: ";
    string name2;
    getline(cin >> ws, name2);

    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Computer (Random)\n";
    cout << "3. AI (Smart)\n";
    int choice2;
    cin >> choice2;
    PlayerType type2 = (choice2 == 2) ? PlayerType::COMPUTER :
        (choice2 == 3) ? PlayerType::AI : PlayerType::HUMAN;

    players[0] = create_player(name1, 'X', type1);
    players[1] = create_player(name2, 'O', type2);

    return players;
}