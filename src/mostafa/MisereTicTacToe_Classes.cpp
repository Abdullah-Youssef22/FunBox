#include "MisereTicTacToe_Classes.h"

MisereTicTacToeBoard::MisereTicTacToeBoard() : Board(3, 3)
{
// Initialize all cells with blank symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = '.';
}


bool MisereTicTacToeBoard::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();
    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == '.' || mark == 0)) {
        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = '.';
        }
        else {         // Apply move
            n_moves++;
            board[x][y] = mark;
        }
        return true;
    }
    return false;
}

bool MisereTicTacToeBoard::is_win(Player<char>* player)
{
    return false; // Winning condition is not applicable here.
}
bool MisereTicTacToeBoard::is_lose(Player<char>* player)
{
    char sym = player->get_symbol();
    return check_three_in_row(sym);
}
bool MisereTicTacToeBoard::is_draw(Player<char>* player)
{
    return n_moves == rows * columns && !check_three_in_row('X') && !check_three_in_row('O');
}
bool MisereTicTacToeBoard::game_is_over(Player<char>* player)
{
    return is_lose(player) || is_draw(player);
}


bool MisereTicTacToeBoard::check_three_in_row(char sym)
{
    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((board[i][0] == sym && board[i][1] == sym && board[i][2] == sym) ||
            (board[0][i] == sym && board[1][i] == sym && board[2][i] == sym))
            return true;
    }
    // Check diagonals
    if ((board[0][0] == sym && board[1][1] == sym && board[2][2] == sym) ||
        (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym))
        return true;
    return false;
}

Move<char>* MisereTicTacToeUI::get_move(Player<char>* player)
{
    int x, y;
    cout << player->get_name() << "'s turn (" << player->get_symbol() << "). Enter your move (row and column): ";
    cin >> x >> y;
    return new Move<char>(x, y, player->get_symbol());
}
Player<char>* MisereTicTacToeUI::create_player(string& name, char symbol,
    PlayerType type)
{
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " with symbol: " << symbol << "\n";
    return new MiserePlayer(name, symbol, type);
}

MisereTicTacToeUI::MisereTicTacToeUI()
	: UI<char>("Welcome to Misère Tic Tac Toe!", 3) {}

