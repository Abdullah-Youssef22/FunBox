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

Mini_Board::Mini_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}



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

bool Mini_Board::is_lose(Player<char>* player) {
    return false;
}

bool Mini_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player) || is_decided();
}




char Mini_Board::get_winner() const {
    return winner;
}

void Mini_Board::set_winner(char w) {
    winner = w;
}

bool Mini_Board::is_decided() const {
    return winner != blank_symbol;
}



///////////////////////////////////////////////////////////////////////////////////
///Ultimate Board 
////////////////////////////////////////////////////////////////////////////////// 

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


Ultimate_Board::~Ultimate_Board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            delete miniBoards[i][j];
        }
    }
}

///////////////////////////////////
// Helpers 
int Ultimate_Board::getMiniRow(int globalX) const {
    return globalX / 3;
}
int Ultimate_Board::getMiniCol(int globalY) const {
    return globalY / 3;
}
int Ultimate_Board::getLocalX(int globalX) const {
    return globalX % 3;
}
int Ultimate_Board::getLocalY(int globalY) const {
    return globalY % 3;
}



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



/////////////////////////////////// logic 1
// imma keep this in commit hist
// bool Ultimate_Board::update_board(Move<char>* move) {
//     int globalX = move->get_x();
//     int globalY = move->get_y();
//     char symbol = move->get_symbol();
//
//     // Validate global coordinates
//     if (globalX < 0 || globalX >= 9 || globalY < 0 || globalY >= 9) {
//         cout << RED << "\n** ERROR: Invalid coordinates! Must be 0-8.\n" << RESET;
//         return false;
//     }
//
//     int miniRow = getMiniRow(globalX);
//     int miniCol = getMiniCol(globalY);
//
//
//
//     if (!isMiniboardPlayable(miniRow, miniCol)) {
//         if (activeMiniRow != -1 && activeMiniCol != -1) {
//             cout <<  RED << "** ERROR: You must play in mini-board (" << activeMiniRow << ", " << activeMiniCol << ")!\n" << RESET;
//         } else {
//             cout << RED << "** ERROR: This mini-board is already decided!\n" << RESET;
//         }
//         return false;
//     }
//
//
//
//     // after all the bounds checking and error handling above 
//     // now that we've verified the move is valid 
//     int localX = getLocalX(globalX);
//     int localY = getLocalY(globalY);
//
//     Move<char> localMove(localX, localY, symbol);
//
//     // NOTE: the update_board method returns a boolean flag but also applies the move 
//     // which is a poor design choice imo but we have to deal with it
//     if (!miniBoards[miniRow][miniCol]->update_board(&localMove)) {
//         cout << "Invalid move in mini-board!\n";
//         return false;
//     }
//
//     // update meta-board if mini-board is now decided
//     updateMetaBoard(miniRow, miniCol);
//
//     // set next active mini-board based on where the move was made
//     activeMiniRow = localX;
//     activeMiniCol = localY;
//
//     // If that mini-board is decided, any board becomes playable
//     // thus we set the -1 flag
//     if (miniBoards[activeMiniRow][activeMiniCol]->is_decided()) {
//         activeMiniRow = -1;
//         activeMiniCol = -1;
//     }
//
//
//
//     board[globalX][globalY] = symbol;
//     n_moves++;  
//     return true;
// }
//

//////////////////////////////// Logic 2 
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
    } else {
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
///////////////////////////////// end of logic 2







/////////////////////////  
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





bool Ultimate_Board::is_win(Player<char>* player) {
    return checkMetaBoardWin(player->get_symbol());
}

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

bool Ultimate_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/////////////////////////////////////////////////////////////
/// getters
Mini_Board* Ultimate_Board::getMiniBoard(int row, int col) const {
    return miniBoards[row][col];
}
char Ultimate_Board::getMetaBoardCell(int row, int col) const {
    return metaBoard[row][col];
}
int Ultimate_Board::getActiveMiniRow() const {
    return activeMiniRow;
}
int Ultimate_Board::getActiveMiniCol() const {
    return activeMiniCol;
}
/////////////////////////////////////////////////////////////





Ultimate_UI::Ultimate_UI() : UI<char>("=== Ultimate Tic-Tac-Toe game ===", 3) {}

Player<char>* Ultimate_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}



Move<char>* Ultimate_UI::get_move(Player<char>* player) {
    Ultimate_Board* ultimateBoard = dynamic_cast<Ultimate_Board*>(player->get_board_ptr());
    
    int globalX, globalY;
    
    if (player->get_type() == PlayerType::HUMAN) {
        int activeRow = ultimateBoard->getActiveMiniRow();
        int activeCol = ultimateBoard->getActiveMiniCol();
        
        if (activeRow != -1 && activeCol != -1) {
            cout << RED << "\n** You must play in mini-board (" << activeRow << ", " << activeCol << ") **\n" << RESET;
        } else {
            cout << GREEN << "\n** You can play in any available mini-board **\n" << RESET;
        }
        
        cout << "Player: "<< player->get_name() << " (" << player->get_symbol() << "), enter global position (row col, 0-8): ";
        cin >> globalX >> globalY;
    } else {
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






void Ultimate_UI::displaySingleMiniBoard(Mini_Board* mini, int miniRow, int miniCol, bool isActive) const {
    vector<vector<char>> matrix = mini->get_board_matrix();
    
    // Display with highlighting if active
    if (isActive) {
        cout << " *** ACTIVE *** \n";
    }
    
    cout << " Mini[" << miniRow << "][" << miniCol << "]\n";
    cout << " " << matrix[0][0] << " | " << matrix[0][1] << " | " << matrix[0][2] << "\n";
    cout << "-----------\n";
    cout << " " << matrix[1][0] << " | " << matrix[1][1] << " | " << matrix[1][2] << "\n";
    cout << "-----------\n";
    cout << " " << matrix[2][0] << " | " << matrix[2][1] << " | " << matrix[2][2] << "\n";
    
    char winner = mini->get_winner();
    if (winner != ' ') {
        cout << " WINNER: " << winner << "\n";
    }
}




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
                cout << " *ACTIVE*";
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
                cout << "  Winner:" << winner << "    ";
            } else {
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

