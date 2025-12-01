#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr
#include "../../include/util/BoardGame_Classes.h"
#include "../../include/util/GameLaunchers.h"
#include "../../include/NumericalTicTacToe_Classes.h"
using namespace std;


void GameLaunchers::launch_numerical_tic_tac_toe() {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    
    NumericalTicTacToe_Board* board = new NumericalTicTacToe_Board();

    UI<int>* game_ui = new NumericalTicTacToe_UI(board);

    Board<int>* numerical_tic_tac_toe_board = new NumericalTicTacToe_Board();


    Player<int>** players = game_ui->setup_players();

    GameManager<int> numerical_tic_tac_toe_game(numerical_tic_tac_toe_board, players, game_ui);

    numerical_tic_tac_toe_game.run();

    // --- Cleanup ---
    delete numerical_tic_tac_toe_board;

    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    delete[] players;
    cout << "\nGame Over! Press Enter to continue...";
    cin.ignore();
    cin.get();

}
