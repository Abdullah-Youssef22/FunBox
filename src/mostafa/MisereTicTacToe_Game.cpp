
#include "../../include/util/GameLaunchers.h"
#include "../../include/util/BoardGame_Classes.h"
#include "MisereTicTacToe_Classes.h"
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
void GameLaunchers::launch_misere_tic_tac_toe() {
    // Create an instance of the specific UI for X-O using a pointer 
    UI<char>* game_ui = new MisereTicTacToeUI();

    // Create the game board. For X-O, this is an X_O_Board.
    Board<char>* xo_board = new MisereTicTacToeBoard();

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
    cout << "\nGame Over! Press Enter to continue...";
    cin.ignore();
    cin.get();

}
