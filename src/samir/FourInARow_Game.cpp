#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr
#include "../../include/util/BoardGame_Classes.h"
#include "../../include/util/GameLaunchers.h"
#include "../../include/FourInARow_Classes.h"
using namespace std;

/**
 * @brief Main function to run the Four in a Row game.
 *
 * This function orchestrates the game by:
 * - Initializing the random number generator
 * - Creating the Four in a Row specific UI and board
 * - Setting up players using the UI
 * - Running the main game loop through the GameManager
 * - Performing cleanup of dynamically allocated memory
 *
 * @return int Returns 0 on successful execution.
 */
void GameLaunchers::launch_four_in_a_row() {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    // Create an instance of the specific UI for Four in a Row using a pointer 
    UI<char>* game_ui = new FourInARow_UI();

    // Create the game board. For Four in a Row, this is a FourInARow_Board.
    Board<char>* fir_board = new FourInARow_Board();

    // Use the UI to set up the players for the game.
    // The UI returns a dynamically allocated array of Player pointers.
    Player<char>** players = game_ui->setup_players();

    // Create the game manager with the board and the array of players.
    GameManager<char> fir_game(fir_board, players, game_ui);

    // Run the game loop.
    fir_game.run();

    // --- Cleanup ---
    // Delete the dynamically allocated board object.
    delete fir_board;
    // Delete the individual player objects.
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    // Delete the UI object.
    //delete game_ui;

    // Delete the dynamically allocated array of player pointers itself.
    delete[] players;
}
