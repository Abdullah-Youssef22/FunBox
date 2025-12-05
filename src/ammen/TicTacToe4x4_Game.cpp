#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr
#include "../../include/util/BoardGame_Classes.h"
#include "../../include/util/GameLaunchers.h"
#include "../../include/TicTacToe4x4_Classes.h"

void GameLaunchers::launch_4x4_tic_tac_toe() {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    // Create an instance of the specific UI for X-O using a pointer 
    UI<char>* game_ui = new FourByFour_UI();

    // Create the game board. For X-O, this is an X_O_Board.
    Board<char>* xo_board = new FourByFour_Board();

    // Use the UI to set up the players for the game.
    // The UI returns a dynamically allocated array of Player pointers.
    Player<char>** players = game_ui->setup_players();

    // Create the game manager with the board and the array of players.
    GameManager<char> x_o_game(xo_board, players, game_ui);

    // Run the game loop.
    x_o_game.run();

    // --- Cleanup ---
    // Delete the dynamically allocated board object.
    delete xo_board;

    // Delete the individual player objects.
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    // Delete the dynamically allocated array of player pointers itself.
    delete[] players;
    delete game_ui;
    
}
