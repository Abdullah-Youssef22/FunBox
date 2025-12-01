
#include <iostream>
#include <string>  
#include <vector>   
#include <memory>   // Required for unique_ptr
#include "../../include/util/BoardGame_Classes.h"
#include "../../include/util/GameLaunchers.h"
#include "../../include/DiamondTicTacToe_Classes.h"
using namespace std;


void GameLaunchers::launch_diamond_tic_tac_toe() {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    
     UI<char>* game_ui = new DimaondUI();

     Board<char>* xo_board = new DimaondTicTacToe_Board();

     Player<char>** players = game_ui->setup_players();

     GameManager<char> x_o_game(xo_board, players, game_ui);

     x_o_game.run();

     delete xo_board;

     for (int i = 0; i < 2; ++i) {
         delete players[i];
     }
     delete[] players;
     delete game_ui;

     cout << "\nGame Over! Press Enter to continue...";
     cin.ignore();
     cin.get();
}
