#include "../../include/DiamondTicTacToe_Classes.h"

/**
 * @brief Check if a cell is inside the diamond-shaped playable area.
 * @param r Row index
 * @param c Column index
 * @return true if the cell is inside the diamond, false otherwise
 */
bool insideDiamond(int r, int c) {
    int mid = 3; 
    return abs(mid - r) + abs(mid - c) <= 3;
}
/**
 * @brief Verify if a cell is valid for a move.
 * @param x Row index
 * @param y Column index
 * @return true if the cell is inside the board, inside the diamond, and empty
 */

bool DimaondTicTacToe_Board::is_valid_cell(int x, int y)
{
    return x >= 0 && x < rows &&
        y >= 0 && y < columns &&
        insideDiamond(x, y) &&
        board[x][y] == '.';

}

DimaondUI::DimaondUI() : UI("Welcome to Diamond Tic Tac Toe!", 3) {}

DimaondTicTacToe_Board::DimaondTicTacToe_Board() : Board(7, 7) {
    for (int r = 0; r < 7; r++) {
        for (int c = 0; c < 7; c++) {
            if (insideDiamond(r, c)) {
                board[r][c] = '.';  // Valid diamond cell
            }
            else {
                board[r][c] = '#';  // Out of bounds
            }
        }
    }
}


/**
 * @brief Update the board with a player's move.
 * @param move Pointer to the move object containing coordinates and symbol
 * @return true if the move was valid and applied, false otherwise
 */

bool DimaondTicTacToe_Board::update_board(Move<char>* move)
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
            board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}
/**
 * @brief Get a move from a player (human or computer).
 * @param player Pointer to the player object
 * @return A new Move object containing coordinates and symbol
 */

Move<char>* DimaondUI::get_move(Player<char>* player)
{
    int x, y;
    if (player->get_type() == PlayerType::HUMAN)
    {
        cout << "\nPlease enter your move x and y (0 to 4): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER)
    {
        DimaondTicTacToe_Board* b =
            dynamic_cast<DimaondTicTacToe_Board*>(player->get_board_ptr());

        do {
            x = rand() % b->get_rows();
            y = rand() % b->get_columns();
        } while (!b->is_valid_cell(x, y));
    }

    return new Move<char>(x, y, player->get_symbol());
}

/**
 * @brief Create a new player (human or computer).
 * @param name Player name
 * @param symbol Player symbol (X or O)
 * @param type Player type (HUMAN or COMPUTER)
 * @return Pointer to the newly created player
 */

Player<char>* DimaondUI::create_player(string& name, char symbol, PlayerType type)
{
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new DimaondPlayer(name, symbol, type);
}
/**
 * @brief Check if there are three consecutive symbols in any row.
 * @param sym Symbol to check (X or O)
 * @return true if found, false otherwise
 */

bool DimaondTicTacToe_Board::checkThreeinrows(char sym)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns - 2; j++)
        {
            if (!insideDiamond(i, j) ||
                !insideDiamond(i, j + 1) ||
                !insideDiamond(i, j + 2))
                continue;

            if (board[i][j] == sym &&
                board[i][j + 1] == sym &&
                board[i][j + 2] == sym)
                return true;
        }
    }
    return false;
}
/**
 * @brief Check if there are three consecutive symbols in any column.
 * @param sym Symbol to check (X or O)
 * @return true if found, false otherwise
 */

bool DimaondTicTacToe_Board::checkThreeincolumns(char sym)
{
    for (int i = 0; i < rows - 2; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (!insideDiamond(i, j) ||
                !insideDiamond(i + 1, j) ||
                !insideDiamond(i + 2, j))
                continue;

            if (board[i][j] == sym &&
                board[i + 1][j] == sym &&
                board[i + 2][j] == sym)
                return true;
        }
    }
    return false;
}
/**
 * @brief Check if there are three consecutive symbols in any diagonal.
 * @param sym Symbol to check (X or O)
 * @return true if found, false otherwise
 */

bool DimaondTicTacToe_Board::checkThreeindiagonals(char sym)
{
    // main diagonal
    for (int i = 0; i < rows - 2; i++)
    {
        for (int j = 0; j < columns - 2; j++)
        {
            if (!insideDiamond(i, j) ||
                !insideDiamond(i + 1, j + 1) ||
                !insideDiamond(i + 2, j + 2))
                continue;

            if (board[i][j] == sym &&
                board[i + 1][j + 1] == sym &&
                board[i + 2][j + 2] == sym)
                return true;
        }
    }

    // anti diagonal
    for (int i = 0; i < rows - 2; i++)
    {
        for (int j = 2; j < columns; j++)
        {
            if (!insideDiamond(i, j) ||
                !insideDiamond(i + 1, j - 1) ||
                !insideDiamond(i + 2, j - 2))
                continue;

            if (board[i][j] == sym &&
                board[i + 1][j - 1] == sym &&
                board[i + 2][j - 2] == sym)
                return true;
        }
    }

    return false;
}


/**
 * @brief Check if there four consecutive symbols in any column.
 * @param sym Symbol to check (X or O)
 * @return true if found, false otherwise
 */

bool DimaondTicTacToe_Board::checkFourincolumns(char sym)
{
    for (int i = 0; i < rows - 3; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (!insideDiamond(i, j) ||
                !insideDiamond(i + 1, j) ||
                !insideDiamond(i + 2, j) ||
                !insideDiamond(i + 3, j))

                continue;
            if (board[i][j] == sym && board[i + 1][j] == sym && board[i + 2][j]== sym && board[i + 3][j] == sym)
            {
                return true;
            }
        }
    }
    return false;
}
/**
 * @brief Check if four are three consecutive symbols in any row.
 * @param sym Symbol to check (X or O)
 * @return true if found, false otherwise
 */


bool DimaondTicTacToe_Board::checkFourinrows(char sym)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns - 3; j++)
        {
            if (!insideDiamond(i, j) ||
                !insideDiamond(i, j + 1) ||
                !insideDiamond(i, j + 2) ||
                !insideDiamond(i, j + 3))
                continue;
            if (board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym && board[i][j + 3] == sym)
            {
                return true;
            }
        }
    }
    return false;
}
/**
 * @brief Check if there are four consecutive symbols in any digonal.
 * @param sym Symbol to check (X or O)
 * @return true if found, false otherwise
 */

bool DimaondTicTacToe_Board::checkFourindiagonals(char sym)
{
    for (int i = 0; i <= rows - 4; i++)
    {
        for (int j = 0; j <= columns - 4; j++)
        {
            if (!insideDiamond(i, j) ||
                !insideDiamond(i + 1, j + 1) ||
                !insideDiamond(i + 2, j + 2) ||
                !insideDiamond(i + 3, j + 3))

                continue;
            if (board[i][j] == sym &&board[i + 1][j + 1] == sym &&board[i + 2][j + 2] == sym &&board[i + 3][j + 3] == sym)
            {
                return true;
            }
        }
    }


    for (int i = 0; i <= rows - 4; i++)
    {
        for (int j = 3; j < columns; j++)
        {
            if (!insideDiamond(i, j) ||
                !insideDiamond(i + 1, j - 1) ||
                !insideDiamond(i + 2, j - 2) ||
                !insideDiamond(i + 3, j - 3))
                continue;
            if (board[i][j] == sym && board[i + 1][j - 1] == sym &&board[i + 2][j - 2] == sym &&board[i + 3][j - 3] == sym)
            {
                return true;
            }
        }
    }

    return false;
}
/**
 * @brief Determine if a player has won the game.
 * Winning requires 3 in a line plus 4 in another line.
 * @param player Pointer to the player
 * @return true if the player has won, false otherwise
 */

bool DimaondTicTacToe_Board::is_win(Player<char>* player)
{
    char sym = player->get_symbol();

    bool three_row = checkThreeinrows(sym);

    bool three_col = checkThreeincolumns(sym);

    bool three_diag = checkThreeindiagonals(sym);

    bool four_row = checkFourinrows(sym);

    bool four_col = checkFourincolumns(sym);

    bool four_diag = checkFourindiagonals(sym);

    if (three_row && (four_col || four_diag))
    {
        return true;
    }

    if (three_col && (four_row || four_diag))
    {
        return true;
    }

    if (three_diag && (four_row || four_col))
    {
        return true;
    }

    return false;
}


/**
 * @brief Determine if a player has lost the game.
 * Currently always returns false.
 * @param player Pointer to the player
 * @return false
 */

bool DimaondTicTacToe_Board::is_lose(Player<char>* player)
{
    return false;
}
/**
 * @brief Check if the game is a draw.
 * @param player Pointer to the player
 * @return true if all cells are filled and no win condition is met
 */

bool DimaondTicTacToe_Board::is_draw(Player<char>* player)
{
    
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < columns; c++)
            if (board[r][c] == '.') 
                return false;

    return !is_win(player);
}

/**
 * @brief Check if the game is over (win or draw).
 * @param player Pointer to the player
 * @return true if the game is finished
 */

bool DimaondTicTacToe_Board::game_is_over(Player<char>* player)
{
    return is_win(player) || is_draw(player);
}