#include "../../include/InfinityTicTacToe_Classes.h"

/**
 * @class Infinity_TicTacToe_Board
 * @brief Represents the board for Infinity Tic Tac Toe.
 *
 * This variant of Tic Tac Toe uses a 3x3 board but introduces
 * special rules: after every 3 moves, the oldest move is removed.
 */
Infinity_TicTacToe_Board::Infinity_TicTacToe_Board()
    : Board<char>(3, 3)
{
    for (auto& row : board)
        for (auto& cell : row)
            cell = '.'; ///< Initialize all cells as empty
}

/**
 * @brief Update the board with a player's move.
 *
 * Handles normal moves, undo moves, and the special "infinity" rule
 * where the oldest move is removed after every 3 moves.
 *
 * @param move Pointer to the Move object containing coordinates and symbol
 * @return true if the move was valid and applied, false otherwise
 */
bool Infinity_TicTacToe_Board::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move
    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    // Undo move
    if (mark == 0)
    {
        if (board[x][y] != '.')
        {
            board[x][y] = '.';
            n_moves--;

            queue<pair<int, int>> temp;
            while (!moveQueue.empty()) {
                auto p = moveQueue.front();
                moveQueue.pop();
                if (!(p.first == x && p.second == y))
                    temp.push(p);
            }
            moveQueue = temp;
        }
        return true;
    }

    // Cell already occupied
    if (board[x][y] != '.')
        return false;

    // Apply move
    board[x][y] = toupper(mark);
    n_moves++;
    counter++;
    moveQueue.push({ x, y });

    // Infinity rule: after every 3 moves, remove oldest
    if (counter % 3 == 0)
    {
        if (checking('X'))
            return true;
        if (checking('O'))
            return true;

        auto oldest = moveQueue.front();
        moveQueue.pop();

        int ox = oldest.first;
        int oy = oldest.second;
        board[ox][oy] = '.';
        n_moves--;
    }
     return true;
}

/**
 * @brief Check if the player has lost.
 * @param player Pointer to the player
 * @return Always returns false (not implemented)
 */
bool Infinity_TicTacToe_Board::is_lose(Player<char>* player)
{
    return false;
}

/**
 * @brief Check if the game is a draw.
 *
 * A draw occurs when 13 moves have been played and no player has won.
 *
 * @param player Pointer to the player
 * @return true if draw, false otherwise
 */
bool Infinity_TicTacToe_Board::is_draw(Player<char>* player)
{
    return counter == 13 && !checking('X') && !checking('O');
    if(counter == 13 && !checking('X') && !checking('O'))
    
        {
            display_draw();
        }
    return counter==13 && !checking('X') && !checking('O');
}

/**
 * @brief Check if the game is over.
 * @param player Pointer to the player
 * @return true if win or draw
 */
bool Infinity_TicTacToe_Board::game_is_over(Player<char>* player)
{
    return is_win(player) || is_draw(player);
}

/**
 * @brief Check if a given symbol has a winning line.
 *
 * @param sym Symbol to check (X or O)
 * @return true if the symbol has 3 in a row, column, or diagonal
 */
bool Infinity_TicTacToe_Board::checking(char sym)
{
    for (int i = 0;i < 3;i++)
    {
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym)
            return true;
        if (board[0][i] == sym && board[1][i] == sym && board[2][i] == sym)
            return true;
    }
    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym)
        return true;
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym)
        return true;

    return false;
}

/**
 * @brief Check if the player has won.
 * @param player Pointer to the player
 * @return true if the player has a winning line
 */
bool Infinity_TicTacToe_Board::is_win(Player<char>* player)
{
    if (checking(player->get_symbol()))
    {
        display_winner(player);
    }
    return checking(player->get_symbol());
}

/**
 * @class Infinity_TicTacToe_UI
 * @brief User interface for Infinity Tic Tac Toe.
 */
void Infinity_TicTacToe_Board::display_winner(Player<char>* player) {
    cout << GREEN << "\nCongratulations " << player->get_name()
        << "! You have won the game as player " << player->get_symbol() << "!" << RESET << endl;
    cout << "\nGame Over! Press Enter to continue...";
    cin.ignore();
    cin.get();
    return;
    
}
void Infinity_TicTacToe_Board::display_draw() {
    cout << YELLOW << "\nThe game ended in draw!" << RESET << endl;
    cout << "\nGame Over! Press Enter to continue...";
    cin.ignore();
    cin.get();
	return;
}





Infinity_TicTacToe_UI::Infinity_TicTacToe_UI()
    : UI<char>("Welcome to Infinity_TicTacToe_UI!", 3) {}

/**
 * @brief Get a move from the player.
 *
 * Human players enter coordinates manually.
 * Computer players choose random coordinates.
 *
 * @param player Pointer to the player
 * @return A new Move object
 */
Move<char>* Infinity_TicTacToe_UI::get_move(Player<char>* player)
{
    int x, y;
    if (player->get_type() == PlayerType::HUMAN)
    {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER)
    {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}

/**
 * @brief Create a new player (human or computer).
 * @param name Player name
 * @param symbol Player symbol (X or O)
 * @param type Player type
 * @return Pointer to the newly created player
 */
Player<char>* Infinity_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type)
{
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Infinity_TicTacToe_Player(name, symbol, type);
}