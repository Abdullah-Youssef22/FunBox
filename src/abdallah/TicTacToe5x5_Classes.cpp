#include "TicTacToe5x5_Classes.h"

TicTacToe5x5_Board::TicTacToe5x5_Board() : Board(5, 5)
{
    
        for (auto& row : board)
            for (auto& cell : row)
                cell = blank_symbol;
    
}

TicTacToe5x5_Board::~TicTacToe5x5_Board()
{

}
bool TicTacToe5x5_Board::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol)) {

        board[x][y] = toupper(mark);
        n_moves++;

        update_scores();

        return true;
    }
    return false;
}

void TicTacToe5x5_Board::update_scores()
{
    player1_score = count_sequences('X');
    player2_score = count_sequences('Y');
}

bool TicTacToe5x5_Board::is_draw(Player<char>* player)
{
    if (n_moves < 24) return false;

    return player1_score == player2_score;
}

bool TicTacToe5x5_Board::is_win(Player<char>* player)
{
    if (n_moves < 24) return false; 

    const char sym = player->get_symbol();

    if ((sym == 'X' || sym == 'x') && player1_score > player2_score) {
        return true;
    }
    else if ((sym == 'Y' || sym == 'y') && player2_score > player1_score) {
        return true;
    }

    return false;
}

bool TicTacToe5x5_Board::game_is_over(Player<char>* player)
{
    return n_moves >= 24;
}

int TicTacToe5x5_Board::count_sequences(char symbol)
{
    int sequences = 0;
    char upper_symbol = toupper(symbol);

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == upper_symbol &&
                board[i][j + 1] == upper_symbol &&
                board[i][j + 2] == upper_symbol) {
                sequences++;
            }
        }
    }

    for (int j = 0; j < 5; ++j) {
        for (int i = 0; i < 3; ++i) {
            if (board[i][j] == upper_symbol &&
                board[i + 1][j] == upper_symbol &&
                board[i + 2][j] == upper_symbol) {
                sequences++;
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == upper_symbol &&
                board[i + 1][j + 1] == upper_symbol &&
                board[i + 2][j + 2] == upper_symbol) {
                sequences++;
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 2; j < 5; ++j) {
            if (board[i][j] == upper_symbol &&
                board[i + 1][j - 1] == upper_symbol &&
                board[i + 2][j - 2] == upper_symbol) {
                sequences++;
            }
        }
    }

    return sequences;
}


TicTacToe5x5_UI::TicTacToe5x5_UI() : UI<char>("Weclome to FCAI X-O Game by Dr El-Ramly", 5) {}

TicTacToe5x5_UI::~TicTacToe5x5_UI()
{
}

Player<char>* TicTacToe5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}
Move<char>* TicTacToe5x5_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 4): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}