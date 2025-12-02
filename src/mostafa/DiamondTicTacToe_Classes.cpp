#include "../../include/DiamondTicTacToe_Classes.h"



bool insideDiamond(int r, int c) {
    int mid = 2;
    return abs(mid - r) + abs(mid - c) <= 2;
}


DimaondUI::DimaondUI()
    : UI<char>("Welcome to Diamond Tic Tac Toe!", 3)
{}

DimaondTicTacToe_Board::DimaondTicTacToe_Board()
    : Board<char>(5, 5)
{
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            board[r][c] = '#';

            
            int mid = 2;
            if (abs(mid - r) + abs(mid - c) <= 2) {
                board[r][c] = '.';
            }
        }
    }
}


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


Player<char>* DimaondUI::create_player(string& name, char symbol, PlayerType type)
{
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new DimaondPlayer(name, symbol, type);
}


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


bool DimaondTicTacToe_Board::is_lose(Player<char>* player)
{
    return false;
}

bool DimaondTicTacToe_Board::is_draw(Player<char>* player)
{
    
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < columns; c++)
            if (board[r][c] == '.') 
                return false;

    return !is_win(player);
}

bool DimaondTicTacToe_Board::game_is_over(Player<char>* player)
{
    return is_win(player) || is_draw(player);
}


