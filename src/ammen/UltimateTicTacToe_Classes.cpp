/**
 * @file UltimateTicTacToe_Classes.cpp
 * @brief Implementation of Ultimate Tic-Tac-Toe game classes
 *
 * This file contains the implementation of Ultimate Tic-Tac-Toe, a complex
 * variant where players compete on a 9x9 board divided into 9 mini-boards (3x3 each).
 * Winning a mini-board claims that square on the meta-board. The objective is to
 * win three mini-boards in a row on the meta-board.
 */

 //--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "../../include/UltimateTicTacToe_Classes.h"
#include "../../include/util/util.h"
using namespace std;

///////////////////////////////////////////////////////////////////
///MINI BOARD 
///////////////////////////////////////////////////////////////////

/**
 * @brief Default constructor for Mini_Board
 *
 * Initializes a standard 3x3 Tic-Tac-Toe board with all cells set to blank_symbol.
 * Each mini-board is part of the larger Ultimate Tic-Tac-Toe game.
 *
 * @note Calls the base Board constructor with dimensions 3x3
 */
Mini_Board::Mini_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

/**
 * @brief Updates the mini-board with a player's move
 *
 * Validates and places a player's symbol on the mini-board at the specified position.
 * Performs bounds checking, occupancy checking, and ensures the mini-board is not
 * already decided (won or drawn).
 *
 * @param move Pointer to Move object containing position (x,y) and player symbol
 * @return true if the move was valid and successfully placed
 * @return false if coordinates are invalid, cell is occupied, or board is already decided
 *
 * @note Increments the move counter on successful placement
 * @see is_decided()
 */
bool Mini_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    // validate
    if (x < 0 || x >= 3 || y < 0 || y >= 3) {
        return false;
    }

    // check if cell is empty
    if (board[x][y] != blank_symbol) {
        return false;
    }

    // check if we already played this board
    if (is_decided()) {
        return false;
    }

    board[x][y] = symbol;
    n_moves++;

    return true;
}

/**
 * @brief Checks if the specified player has won this mini-board
 *
 * Examines all possible winning combinations: three horizontal rows,
 * three vertical columns, and two diagonals.
 *
 * @param player Pointer to the Player object to check for winning
 * @return true if the player has three symbols in a row
 * @return false if no winning combination exists
 */
bool Mini_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == sym && board[1][j] == sym && board[2][j] == sym) {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym) {
        return true;
    }
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym) {
        return true;
    }

    return false;
}

/**
 * @brief Checks if the mini-board has ended in a draw
 *
 * A draw occurs when all 9 cells are filled and neither player has won.
 * Creates temporary player objects to verify no winner exists.
 *
 * @param player Pointer to the current Player object
 * @return true if the board is full with no winner
 * @return false if the game is not yet a draw or someone has won
 */
bool Mini_Board::is_draw(Player<char>* player) {
    // return (n_moves == 9 && !is_win(player));
    /// ===================================== // NOTE: test both those methods later to check
    ///
    // Draw only if board is full and no winner
    if (n_moves == 9 && !is_win(player)) {
        // Need to check both players didn't win
        // Create temporary players to check
        Player<char> tempX("", 'X', PlayerType::HUMAN);
        Player<char> tempO("", 'O', PlayerType::HUMAN);

        if (!is_win(&tempX) && !is_win(&tempO)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Checks if the specified player has lost this mini-board
 *
 * @param player Pointer to the Player object to check
 * @return false Always returns false (not used in current implementation)
 *
 * @note This method is not currently utilized in the game logic
 */
bool Mini_Board::is_lose(Player<char>* player) {
    return false;
}

/**
 * @brief Checks if the mini-board game has reached a terminal state
 *
 * @param player Pointer to the current Player object
 * @return true if the board is won, drawn, or already decided
 * @return false if the game can continue
 *
 * @see is_win()
 * @see is_draw()
 * @see is_decided()
 */
bool Mini_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player) || is_decided();
}

/**
 * @brief Gets the winner of this mini-board
 *
 * @return char The winning player's symbol ('X', 'O'), 'D' for draw, or blank_symbol if undecided
 */
char Mini_Board::get_winner() const {
    return winner;
}

/**
 * @brief Sets the winner of this mini-board
 *
 * @param w The winner symbol to set ('X', 'O', or 'D' for draw)
 *
 * @note Once set, the mini-board is considered decided and no further moves can be made
 */
void Mini_Board::set_winner(char w) {
    winner = w;
}

/**
 * @brief Checks if this mini-board has been decided
 *
 * A mini-board is decided when it has been won by either player or ended in a draw.
 *
 * @return true if the mini-board has a winner or is drawn
 * @return false if the mini-board is still in play
 */
bool Mini_Board::is_decided() const {
    return winner != blank_symbol;
}

///////////////////////////////////////////////////////////////////////////////////
///Ultimate Board 
////////////////////////////////////////////////////////////////////////////////// 

/**
 * @brief Default constructor for Ultimate_Board
 *
 * Initializes the 9x9 global board and creates 9 mini-boards in a 3x3 arrangement.
 * Also initializes the meta-board that tracks mini-board winners.
 *
 * @note Sets activeMiniRow and activeMiniCol to -1, indicating no active board initially
 * @note Allocates memory for 9 Mini_Board objects
 */
Ultimate_Board::Ultimate_Board() :Board(9, 9), activeMiniRow(-1), activeMiniCol(-1) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            miniBoards[i][j] = new Mini_Board();
            metaBoard[i][j] = blank_symbol;
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = blank_symbol;
        }
    }
}

/**
 * @brief Destructor for Ultimate_Board
 *
 * Deallocates memory for all 9 mini-boards.
 */
Ultimate_Board::~Ultimate_Board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            delete miniBoards[i][j];
        }
    }
}

///////////////////////////////////
// Helpers 

/**
 * @brief Converts global row coordinate to mini-board row index
 *
 * @param globalX Global row coordinate (0-8)
 * @return int Mini-board row index (0-2)
 */
int Ultimate_Board::getMiniRow(int globalX) const {
    return globalX / 3;
}

/**
 * @brief Converts global column coordinate to mini-board column index
 *
 * @param globalY Global column coordinate (0-8)
 * @return int Mini-board column index (0-2)
 */
int Ultimate_Board::getMiniCol(int globalY) const {
    return globalY / 3;
}

/**
 * @brief Converts global row coordinate to local row within a mini-board
 *
 * @param globalX Global row coordinate (0-8)
 * @return int Local row coordinate within mini-board (0-2)
 */
int Ultimate_Board::getLocalX(int globalX) const {
    return globalX % 3;
}

/**
 * @brief Converts global column coordinate to local column within a mini-board
 *
 * @param globalY Global column coordinate (0-8)
 * @return int Local column coordinate within mini-board (0-2)
 */
int Ultimate_Board::getLocalY(int globalY) const {
    return globalY % 3;
}

/**
 * @brief Checks if a mini-board is currently playable
 *
 * A mini-board is playable if:
 * - It hasn't been decided (won or drawn) AND
 * - Either no active board is set (-1, -1) OR
 * - It is the currently active board OR
 * - The currently active board is already decided
 *
 * @param miniRow Mini-board row index (0-2)
 * @param miniCol Mini-board column index (0-2)
 * @return true if the mini-board can accept moves
 * @return false if the mini-board is decided or not currently active
 *
 * @note The -1 flag for activeMiniRow/Col means no board has been chosen yet
 */
bool Ultimate_Board::isMiniboardPlayable(int miniRow, int miniCol) const {

    // If no active board is set, any undecided board is playable
    if (miniBoards[miniRow][miniCol]->is_decided()) {
        return false;
    }
    // this is for when all the miniboards are playable. 
    // the -1 flag thingy means no board has been chosen yet.
    if (activeMiniRow == -1 && activeMiniCol == -1) {
        return true;
    }

    // check if the requested col/row are in the active board, in which case
    // they are obviously playable 
    if (miniRow == activeMiniRow && miniCol == activeMiniCol) {
        return true;
    }

    // if the active board is is_decided 
    // aka the active board has been won already and is finished 
    // in that case then whatever other undecided board is playable and 
    // we return true
    if (miniBoards[activeMiniRow][activeMiniCol]->is_decided()) {
        return true;
    }

    return false;
}

/**
 * @brief Updates the meta-board after a mini-board is decided
 *
 * Checks if the specified mini-board has been won or drawn, and updates
 * the corresponding cell in the meta-board accordingly.
 * Sets the mini-board's winner to 'X', 'O', or 'D' (draw).
 *
 * @param miniRow Mini-board row index (0-2)
 * @param miniCol Mini-board column index (0-2)
 *
 * @note Creates temporary player objects to check winning conditions
 */
void Ultimate_Board::updateMetaBoard(int miniRow, int miniCol) {
    Mini_Board* mini = miniBoards[miniRow][miniCol];

    Player<char> playerX("", 'X', PlayerType::HUMAN);

    if (mini->is_win(&playerX)) {
        metaBoard[miniRow][miniCol] = 'X';
        mini->set_winner('X');
        return;
    }

    Player<char> playerO("", 'O', PlayerType::HUMAN);
    if (mini->is_win(&playerO)) {
        metaBoard[miniRow][miniCol] = 'O';
        mini->set_winner('O');
        return;
    }

    if (mini->is_draw(&playerX)) {
        metaBoard[miniRow][miniCol] = 'D';
        mini->set_winner('D');
    }
}

///////////////////////////////////

/**
 * @brief Updates the ultimate board with a player's move
 *
 * Validates global coordinates, determines which mini-board to play in,
 * enforces active board rules, updates the appropriate mini-board,
 * and updates the meta-board if a mini-board becomes decided.
 *
 * @param move Pointer to Move object containing global position (x,y) and player symbol
 * @return true if the move was valid and successfully placed
 * @return false if move is invalid (out of bounds, wrong mini-board, already decided, etc.)
 *
 * @note Global coordinates must be 0-8
 * @note Active board rules: players must continue in the board determined by opponent's last move
 * @note Prints error messages for invalid moves
 * @see isMiniboardPlayable()
 * @see updateMetaBoard()
 */
bool Ultimate_Board::update_board(Move<char>* move) {
    int globalX = move->get_x();
    int globalY = move->get_y();
    char symbol = move->get_symbol();

    if (globalX < 0 || globalX >= 9 || globalY < 0 || globalY >= 9) {
        cout << RED << "\n** ERROR: Invalid coordinates! Must be 0-8.\n" << RESET;
        return false;
    }

    int miniRow = getMiniRow(globalX);
    int miniCol = getMiniCol(globalY);

    // if no active board set, this becomes the active board
    if (activeMiniRow == -1 && activeMiniCol == -1) {
        activeMiniRow = miniRow;
        activeMiniCol = miniCol;
    }

    // play in active board unless it's decided
    if (!miniBoards[activeMiniRow][activeMiniCol]->is_decided()) {
        if (miniRow != activeMiniRow || miniCol != activeMiniCol) {
            cout << RED << "** ERROR: You must finish mini-board (" << activeMiniRow << ", " << activeMiniCol << ") first!\n" << RESET;
            return false;
        }
    }
    else {
        // active board is decided, this move sets new active board
        if (miniBoards[miniRow][miniCol]->is_decided()) {
            cout << RED << "** ERROR: This mini-board is already decided!\n" << RESET;
            return false;
        }
        activeMiniRow = miniRow;
        activeMiniCol = miniCol;
    }

    int localX = getLocalX(globalX);
    int localY = getLocalY(globalY);

    Move<char> localMove(localX, localY, symbol);

    if (!miniBoards[miniRow][miniCol]->update_board(&localMove)) {
        cout << "Invalid move in mini-board!\n";
        return false;
    }

    // update meta-board if mini-board is now decided
    updateMetaBoard(miniRow, miniCol);


    board[globalX][globalY] = symbol;
    n_moves++;
    return true;
}

/////////////////////////  

/**
 * @brief Checks if a player has won on the meta-board
 *
 * Examines the meta-board for three in a row of the specified symbol.
 * Checks all rows, columns, and diagonals.
 *
 * @param symbol The player's symbol to check ('X' or 'O')
 * @return true if the symbol has three in a row on the meta-board
 * @return false if no winning combination exists
 */
bool Ultimate_Board::checkMetaBoardWin(char symbol) const {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (metaBoard[i][0] == symbol &&
            metaBoard[i][1] == symbol &&
            metaBoard[i][2] == symbol) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        if (metaBoard[0][j] == symbol &&
            metaBoard[1][j] == symbol &&
            metaBoard[2][j] == symbol) {
            return true;
        }
    }

    // Check diagonals
    if (metaBoard[0][0] == symbol &&
        metaBoard[1][1] == symbol &&
        metaBoard[2][2] == symbol) {
        return true;
    }

    if (metaBoard[0][2] == symbol &&
        metaBoard[1][1] == symbol &&
        metaBoard[2][0] == symbol) {
        return true;
    }

    return false;
}
/////////////////////////////////////////

/**
 * @brief Checks if the specified player has won the ultimate game
 *
 * @param player Pointer to the Player object to check for winning
 * @return true if the player has won three mini-boards in a row on the meta-board
 * @return false if no winning combination exists
 *
 * @see checkMetaBoardWin()
 */
bool Ultimate_Board::is_win(Player<char>* player) {
    return checkMetaBoardWin(player->get_symbol());
}

/**
 * @brief Checks if the ultimate game has ended in a draw
 *
 * A draw occurs when all mini-boards are decided (won or drawn)
 * and neither player has won three mini-boards in a row.
 *
 * @param player Pointer to the current Player object
 * @return true if all mini-boards are decided with no winner
 * @return false if the game is still ongoing or someone has won
 */
bool Ultimate_Board::is_draw(Player<char>* player) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!miniBoards[i][j]->is_decided()) {
                return false;  // Game still ongoing cuz there are undecided miniboards
            }
        }
    }

    // if not then the game ended, did someone win?
    if (checkMetaBoardWin('X') || checkMetaBoardWin('O')) {
        return false;
    }

    // if not then no one won, we draw
    return true;
}

/**
 * @brief Checks if the ultimate game has reached a terminal state
 *
 * @param player Pointer to the current Player object
 * @return true if the game is won or drawn
 * @return false if the game can continue
 *
 * @see is_win()
 * @see is_draw()
 */
bool Ultimate_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/////////////////////////////////////////////////////////////
/// getters

/**
 * @brief Gets a pointer to a specific mini-board
 *
 * @param row Mini-board row index (0-2)
 * @param col Mini-board column index (0-2)
 * @return Mini_Board* Pointer to the requested mini-board
 */
Mini_Board* Ultimate_Board::getMiniBoard(int row, int col) const {
    return miniBoards[row][col];
}

/**
 * @brief Gets the value of a cell in the meta-board
 *
 * @param row Meta-board row index (0-2)
 * @param col Meta-board column index (0-2)
 * @return char The cell value ('X', 'O', 'D' for draw, or blank_symbol)
 */
char Ultimate_Board::getMetaBoardCell(int row, int col) const {
    return metaBoard[row][col];
}

/**
 * @brief Gets the row index of the currently active mini-board
 *
 * @return int Active mini-board row (0-2), or -1 if no board is active
 */
int Ultimate_Board::getActiveMiniRow() const {
    return activeMiniRow;
}

/**
 * @brief Gets the column index of the currently active mini-board
 *
 * @return int Active mini-board column (0-2), or -1 if no board is active
 */
int Ultimate_Board::getActiveMiniCol() const {
    return activeMiniCol;
}
/////////////////////////////////////////////////////////////

/**
 * @brief Default constructor for Ultimate_UI
 *
 * Initializes the user interface with a welcome message and specifies
 * that the game uses a 3x3 meta-board structure.
 */
Ultimate_UI::Ultimate_UI() : UI<char>("=== Ultimate Tic-Tac-Toe game ===", 3) {}

/**
 * @brief Factory method to create a player object
 *
 * Creates either a human or computer player with the specified parameters.
 * Prints confirmation message of player creation.
 *
 * @param name Reference to string containing the player's name
 * @param symbol The symbol assigned to the player ('X' or 'O')
 * @param type PlayerType enum indicating HUMAN or COMPUTER player
 * @return Player<char>* Pointer to newly created Player object
 *
 * @warning Caller is responsible for deallocating the returned Player object
 */
Player<char>* Ultimate_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets a move from the player (human or computer)
 *
 * For human players, displays which mini-board is active and prompts for
 * global position input. For computer players, generates random valid
 * positions within playable mini-boards.
 *
 * @param player Pointer to the Player object making the move
 * @return Move<char>* Pointer to newly created Move object containing the player's move
 *
 * @note Human input: global row and column (0-8)
 * @note Computer moves are randomly generated within playable mini-boards
 * @note Displays active board information with color coding (RED for required, GREEN for open)
 * @warning Caller is responsible for deallocating the returned Move object
 *
 * @see isMiniboardPlayable()
 */
Move<char>* Ultimate_UI::get_move(Player<char>* player) {
    Ultimate_Board* ultimateBoard = dynamic_cast<Ultimate_Board*>(player->get_board_ptr());

    int globalX, globalY;

    if (player->get_type() == PlayerType::HUMAN) {
        int activeRow = ultimateBoard->getActiveMiniRow();
        int activeCol = ultimateBoard->getActiveMiniCol();

        if (activeRow != -1 && activeCol != -1) {
            cout << RED << "\n** You must play in mini-board (" << activeRow << ", " << activeCol << ") **\n" << RESET;
        }
        else {
            cout << GREEN << "\n** You can play in any available mini-board **\n" << RESET;
        }

        cout << "Player: " << player->get_name() << " (" << player->get_symbol() << "), enter global position (row col, 0-8): ";
        cin >> globalX >> globalY;
    }
    else {
        // computer player

        do {
            globalX = rand() % 9;
            globalY = rand() % 9;
        } while (!ultimateBoard->isMiniboardPlayable(
            ultimateBoard->getMiniRow(globalX),
            ultimateBoard->getMiniCol(globalY)));

        cout << "Computer plays: " << globalX << " " << globalY << endl;
    }

    return new Move<char>(globalX, globalY, player->get_symbol());
}

/**
 * @brief Displays a single mini-board with its status
 *
 * Shows the 3x3 grid of a mini-board, highlights if it's active,
 * and displays the winner if decided.
 *
 * @param mini Pointer to the Mini_Board to display
 * @param miniRow Row index of this mini-board in the 3x3 arrangement
 * @param miniCol Column index of this mini-board in the 3x3 arrangement
 * @param isActive Whether this is the currently active mini-board
 *
 * @note Uses "*** ACTIVE ***" marker for the active board
 */
void Ultimate_UI::displaySingleMiniBoard(Mini_Board* mini, int miniRow, int miniCol, bool isActive) const {
    vector<vector<char>> matrix = mini->get_board_matrix();

    // Display with highlighting if active
    if (isActive) {
        cout << BLUE << " *** ACTIVE *** \n" << RESET;
    }

    cout << " Mini[" << miniRow << "][" << miniCol << "]\n";
    cout << " " << matrix[0][0] << " | " << matrix[0][1] << " | " << matrix[0][2] << "\n";
    cout << "-----------\n";
    cout << " " << matrix[1][0] << " | " << matrix[1][1] << " | " << matrix[1][2] << "\n";
    cout << "-----------\n";
    cout << " " << matrix[2][0] << " | " << matrix[2][1] << " | " << matrix[2][2] << "\n";

    char winner = mini->get_winner();
    if (winner != ' ') {
        cout << GREEN << " WINNER: " << winner << "\n" << RESET;
    }
}

/**
 * @brief Displays the meta-board showing mini-board winners
 *
 * Shows a 3x3 grid representing which mini-boards have been won
 * or drawn. Each cell shows 'X', 'O', 'D' (draw), or blank_symbol.
 *
 * @param board Pointer to the Ultimate_Board
 *
 * @note This provides a high-level view of the overall game state
 */
void Ultimate_UI::displayMetaBoard(Ultimate_Board* board) const {
    cout << "\n=== META-BOARD ===\n";
    cout << "  " << board->getMetaBoardCell(0, 0) << " | "
        << board->getMetaBoardCell(0, 1) << " | "
        << board->getMetaBoardCell(0, 2) << "\n";
    cout << " -----------\n";
    cout << "  " << board->getMetaBoardCell(1, 0) << " | "
        << board->getMetaBoardCell(1, 1) << " | "
        << board->getMetaBoardCell(1, 2) << "\n";
    cout << " -----------\n";
    cout << "  " << board->getMetaBoardCell(2, 0) << " | "
        << board->getMetaBoardCell(2, 1) << " | "
        << board->getMetaBoardCell(2, 2) << "\n";
    cout << "=============================================\n\n";
}

/**
 * @brief Displays the complete ultimate board state
 *
 * Shows the meta-board followed by all 9 mini-boards arranged in a 3x3 grid.
 * Each mini-board is displayed side-by-side with its neighbors, and the
 * active board is marked. Winners for each mini-board are shown below.
 *
 * @param board Pointer to the Ultimate_Board to display
 *
 * @note This provides a comprehensive view of the entire game state
 * @note Active mini-board is marked with "*ACTIVE*"
 * @note Mini-board winners are displayed below each board
 *
 * @see displayMetaBoard()
 */
void Ultimate_UI::display_ultimate_board(Ultimate_Board* board) const {
    displayMetaBoard(board);

    int activeRow = board->getActiveMiniRow();
    int activeCol = board->getActiveMiniCol();

    // display mini-boards in a 3x3 grid
    for (int miniRow = 0; miniRow < 3; miniRow++) {
        cout << "\n";
        for (int miniCol = 0; miniCol < 3; miniCol++) {
            cout << "  Mini[" << miniRow << "][" << miniCol << "]";
            if (miniRow == activeRow && miniCol == activeCol) {
                cout << BLUE << " *ACTIVE*" << RESET;
            }
            cout << "    ";
        }
        cout << "\n";

        // display 3 rows of each mini-board side by side
        for (int localRow = 0; localRow < 3; localRow++) {
            for (int miniCol = 0; miniCol < 3; miniCol++) {
                Mini_Board* mini = board->getMiniBoard(miniRow, miniCol);
                vector<vector<char>> matrix = mini->get_board_matrix();

                cout << "  " << matrix[localRow][0] << " | "
                    << matrix[localRow][1] << " | "
                    << matrix[localRow][2] << "    ";
            }
            cout << "\n";

            if (localRow < 2) {
                for (int miniCol = 0; miniCol < 3; miniCol++) {
                    cout << " -----------   ";
                }
                cout << "\n";
            }
        }

        // show winner for each mini-board
        for (int miniCol = 0; miniCol < 3; miniCol++) {
            char winner = board->getMiniBoard(miniRow, miniCol)->get_winner();
            if (winner != ' ') {
                cout << GREEN << "  Winner:" << winner << "    " << RESET;
            }
            else {
                cout << "              ";
            }
        }
        cout << "\n";

        if (miniRow < 2) {
            cout << "\n========================================\n";
        }
    }
    cout << "\n";
}