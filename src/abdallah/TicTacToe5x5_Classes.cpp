#include "TicTacToe5x5_Classes.h"
/**
 * @class TicTacToe5x5_Board
 * @brief Represents a 5x5 TicTacToe board with scoring logic for sequences of 3.
 */

 /**
  * @brief Constructs a 5x5 TicTacToe board and initializes all cells as blank.
  */
TicTacToe5x5_Board::TicTacToe5x5_Board() : Board(5, 5)
{
    
        for (auto& row : board)
            for (auto& cell : row)
                cell = blank_symbol;
    
}

TicTacToe5x5_Board::~TicTacToe5x5_Board()
{

}
/**
 * @brief Updates the board with a new move if valid.
 *
 * @param move Pointer to the Move object containing x, y, and symbol.
 * @return true if the move is valid and applied.
 * @return false if the move is invalid.
 */
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
/**
 * @brief Updates player scores by recounting sequences of X and Y.
 */
void TicTacToe5x5_Board::update_scores()
{
    player1_score = count_sequences('X');
    player2_score = count_sequences('Y');
}
/**
 * @brief Checks if the game ended in a draw.
 *
 * @param player Pointer to the current player.
 * @return true if draw.
 * @return false otherwise.
 */
bool TicTacToe5x5_Board::is_draw(Player<char>* player)
{
    if (!end()) return false;

    return player1_score == player2_score;
}
/**
 * @brief Checks if a given player has won the game.
 *
 * @param player Pointer to the current player.
 * @return true if the player won.
 * @return false otherwise.
 */
bool TicTacToe5x5_Board::is_win(Player<char>* player)
{
    if (!end()) return false; 

    const char sym = player->get_symbol();

    if ((sym == 'X' || sym == 'x') && player1_score > player2_score && end()) {
        end();
		return true;
    }
    else if ((sym == 'Y' || sym == 'y') && player2_score > player1_score && end()) {
		end();
		return true;
    }

}
/**
 * @brief Checks whether the game is over by win or draw.
 *
 * @param player Pointer to the current player.
 * @return true if game is over.
 * @return false otherwise.
 */
bool TicTacToe5x5_Board::game_is_over(Player<char>* player)
{
        return is_win(player) || is_draw(player);

}
/**
 * @brief Determines if the game has reached the end (board full).
 *
 * @return true if the game has ended.
 * @return false otherwise.
 */
bool TicTacToe5x5_Board::end()
{
    if (n_moves < 24) return false;
    else
    {
        char x = 'X', o = 'O';
        player1_score = count_sequences(x);
        player2_score = count_sequences(o);
        desplay_scores();
        cout << "Press enter to continue...";
        cin.ignore();
        cin.get();
        return true;
    }
}
/**
 * @brief Displays the current scores and announces the winner or draw.
 */
void TicTacToe5x5_Board::desplay_scores()
{
    cout << "Current Scores:\n";
    if (player1_score> player2_score)
    {
        cout << GREEN << "Player X: " << player1_score << RESET << "\n";
        cout << RED << "Player O: " << player2_score << RESET << "\n";
        cout << GREEN << "Player X is the winner" << RESET << "\n";
    }
    else if (player2_score > player1_score)
    {
        cout << RED << "Player X: " << player1_score << RESET << "\n";
        cout << GREEN << "Player O: " << player2_score << RESET << "\n";
        cout << GREEN << "Player O is the winner" << RESET << "\n";
    }
    else
    {
		cout << YELLOW << "Player X: " << player1_score << RESET << "\n";
		cout << YELLOW << "Player O: " << player2_score << RESET << "\n";
        cout << YELLOW << "The game is a draw" << RESET << "\n";
    }
}
/**
 * @brief Counts all sequences of 3 identical symbols on the board.
 *
 * @param symbol The symbol ('X' or 'O') to count sequences for.
 * @return int Number of sequences found.
 */

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
/**
 * @class TicTacToe5x5_UI
 * @brief Handles user interface for the 5x5 TicTacToe game.
 */

 /**
  * @brief Constructs the UI and initializes the welcome message.
  */

TicTacToe5x5_UI::TicTacToe5x5_UI() : UI<char>("Weclome to FCAI TicTacToe5x5 Game by Abdallah Youssef", 5) {}

TicTacToe5x5_UI::~TicTacToe5x5_UI()
{
}
/**
 * @brief Creates a new player.
 *
 * @param name Player name.
 * @param symbol Player symbol (X or O).
 * @param type HUMAN or COMPUTER.
 * @return Pointer to the created player.
 */
Player<char>* TicTacToe5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets a move either from user input or computer AI.
 *
 * @param player Pointer to current player.
 * @return Move<char>* Pointer to the created move.
 */
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