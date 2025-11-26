#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr
#include "../../include/util/BoardGame_Classes.h"
#include "../../include/util/GameLaunchers.h"
#include "../../include/UltimateTicTacToe_Classes.h"
using namespace std;

/**
 * @brief Main function to run the X-O game.
 *
 * This function orchestrates the game by:
 * - Initializing the random number generator
 * - Creating the X-O specific UI and board
 * - Setting up players using the UI
 * - Running the main game loop through the GameManager
 * - Performing cleanup of dynamically allocated memory
 *
 * @return int Returns 0 on successful execution.
 */
void GameLaunchers::launch_ultimate_tic_tac_toe() {
    srand(static_cast<unsigned int>(time(0)));
    
    // Create UI
    Ultimate_UI* ui = new Ultimate_UI();
    
    // Create board
    Ultimate_Board* board = new Ultimate_Board();
    
    // Setup players
    Player<char>** players = ui->setup_players();
    
    // Set board pointers for players
    players[0]->set_board_ptr(board);
    players[1]->set_board_ptr(board);
    

    // we need custom display logic and a custom game loop, thus we dont use the typical game-manager loop
    ui->display_ultimate_board(board);
    
    int currentPlayerIndex = 0;
    while (true) {
        Player<char>* currentPlayer = players[currentPlayerIndex];
        
        // get move
        Move<char>* move = ui->get_move(currentPlayer);
        
        // validate and apply
        while (!board->update_board(move)) {
            delete move;
            move = ui->get_move(currentPlayer);
        }
        
        ui->display_ultimate_board(board);
        
        // check if game over
        if (board->is_win(currentPlayer)) {
            ui->display_message(currentPlayer->get_name() + " WINS THE ULTIMATE GAME!");
            break;
        }
        
        if (board->is_draw(currentPlayer)) {
            ui->display_message("ULTIMATE DRAW!");
            break;
        }
        
        // Switch player
        currentPlayerIndex = 1 - currentPlayerIndex;
        
        delete move;
    }
    
    // Cleanup
    delete board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
    
    cout << "\nGame Over! Press Enter to continue...";
    cin.ignore();
    cin.get();
}
