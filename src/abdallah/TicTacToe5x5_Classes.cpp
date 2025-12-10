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
    player2_score = count_sequences('O');
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
    else if ((sym == 'O' || sym == 'o') && player2_score > player1_score && end()) {
        end();
        return true;
    }

    return false;
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
        if (!game_ended) {
            char x = 'X', o = 'O';
            player1_score = count_sequences(x);
            player2_score = count_sequences(o);
            desplay_scores();
            cout << "Press enter to continue...";
            cin.ignore();
            cin.get();
            game_ended = true;
        }
        return true;
    }
}
/**
 * @brief Displays the current scores and announces the winner or draw.
 */
void TicTacToe5x5_Board::desplay_scores()
{
    cout << "Current Scores:\n";
    if (player1_score > player2_score)
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
Player<char>* TicTacToe5x5_UI::create_player(string& name, char symbol, PlayerType type)
{
    cout << "Creating ";
    if (type == PlayerType::HUMAN) cout << "human";
    else if (type == PlayerType::COMPUTER) cout << "computer (random)";
    else if (type == PlayerType::AI) cout << "AI (smart)";
    cout << " player: " << name << " (" << symbol << ")\n";


    if (type == PlayerType::AI) {
        return new TicTacToe5x5_AIPlayer(name, symbol);
    }
    return new Player<char>(name, symbol, type);
}



/**
 * @brief Gets a move either from user input or computer AI.
 *
 * @param player Pointer to current player.
 * @return Move<char>* Pointer to the created move.
 */
Move<char>* TicTacToe5x5_UI::get_move(Player<char>* player)
{
    int x = 0, y = 0;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 4): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    else if (player->get_type() == PlayerType::AI) {
        TicTacToe5x5_AIPlayer* aiPlayer = dynamic_cast<TicTacToe5x5_AIPlayer*>(player);
        if (aiPlayer) {
            pair<int, int> best = aiPlayer->get_best_move();
            x = best.first;
            y = best.second;
        }
    }

    return new Move<char>(x, y, player->get_symbol());
}
Player<char>** TicTacToe5x5_UI::setup_players()
{
    Player<char>** players = new Player<char>*[2];

    cout << "Enter Player X name: ";
    string nameX;
    getline(cin >> ws, nameX);

    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Computer (Random)\n";
    cout << "3. AI (Smart)\n";
    int choiceX;
    cin >> choiceX;
    PlayerType typeX = (choiceX == 2) ? PlayerType::COMPUTER :
        (choiceX == 3) ? PlayerType::AI : PlayerType::HUMAN;
    players[0] = create_player(nameX, 'X', typeX);

    cout << "Enter Player O name: ";
    string nameO;
    getline(cin >> ws, nameO);

    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Computer (Random)\n";
    cout << "3. AI (Smart)\n";
    int choiceO;
    cin >> choiceO;
    PlayerType typeO = (choiceO == 2) ? PlayerType::COMPUTER :
        (choiceO == 3) ? PlayerType::AI : PlayerType::HUMAN;
    players[1] = create_player(nameO, 'O', typeO);

    return players;
}

// ========== TicTacToe5x5_AIPlayer Implementation ==========

TicTacToe5x5_AIPlayer::TicTacToe5x5_AIPlayer(string n, char s)
    : Player(n, s, PlayerType::AI)
{
}
bool TicTacToe5x5_AIPlayer::is_board_full(const vector<vector<char>>& b, int moves)
{
    return moves >= 24;
}
int TicTacToe5x5_AIPlayer::minimax(vector<vector<char>>& board, int depth, bool isMaximizing,
    char aiSymbol, char oppSymbol, int alpha, int beta, int maxDepth)
{
    int currentMoves = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] != '.') currentMoves++;
        }
    }

    if (depth >= maxDepth || currentMoves == 24)
    {
        int x_score = count_sequences_in_board(board, 'X');
        int o_score = count_sequences_in_board(board, 'O');

        if (aiSymbol == 'X') {
            return x_score - o_score;
        }
        else {
            return o_score - x_score;
        }
    }

    if (isMaximizing) {
        int bestScore = -10000;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (board[i][j] == '.') {
                    board[i][j] = toupper(aiSymbol);
                    int score = minimax(board, depth + 1, false, aiSymbol, oppSymbol,
                        alpha, beta, maxDepth);
                    board[i][j] = '.';

                    bestScore = max(score, bestScore);
                    alpha = max(alpha, score);
                    if (beta <= alpha) break;
                }
            }
        }
        return bestScore;
    }
    else {
        int bestScore = 10000;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (board[i][j] == '.') {
                    board[i][j] = toupper(oppSymbol);
                    int score = minimax(board, depth + 1, true, aiSymbol, oppSymbol,
                        alpha, beta, maxDepth);
                    board[i][j] = '.';

                    bestScore = min(score, bestScore);
                    beta = min(beta, score);
                    if (beta <= alpha) break;
                }
            }
        }
        return bestScore;
    }
}

int TicTacToe5x5_AIPlayer::count_sequences_in_board(const vector<vector<char>>& board, char symbol) {
    int sequences = 0;
    char upper_symbol = toupper(symbol);

    // Horizontal
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == upper_symbol &&
                board[i][j + 1] == upper_symbol &&
                board[i][j + 2] == upper_symbol) {
                sequences++;
            }
        }
    }
    // Vertical
    for (int j = 0; j < 5; ++j) {
        for (int i = 0; i < 3; ++i) {
            if (board[i][j] == upper_symbol &&
                board[i + 1][j] == upper_symbol &&
                board[i + 2][j] == upper_symbol) {
                sequences++;
            }
        }
    }
    // Diagonal 
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == upper_symbol &&
                board[i + 1][j + 1] == upper_symbol &&
                board[i + 2][j + 2] == upper_symbol) {
                sequences++;
            }
        }
    }
    // Diagonal /
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

pair<int, int> TicTacToe5x5_AIPlayer::get_best_move() {
    int bestScore = -1000;
    vector<vector<char>> board = boardPtr->get_board_matrix();
    pair<int, int> bestMove = { -1, -1 };
    char aiSymbol = symbol;
    char oppSymbol = (symbol == 'X') ? 'O' : 'X';

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == '.') {
                board[i][j] = toupper(aiSymbol);
                int score = minimax(board, 0, false, aiSymbol, oppSymbol, -10000, 10000);
                board[i][j] = '.';

                if (score > bestScore) {
                    bestScore = score;
                    bestMove = { i, j };
                }
            }
        }
    }
    return bestMove;
}