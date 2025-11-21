// #include <iostream> 
// #include <string>  
// #include <vector>   
// #include <memory>  
#include "../include/util/Menu.h"
#include "../include/util/GameLaunchers.h"
#include <ctime>
#include <iostream>

int main() {
    srand(static_cast<unsigned int>(time(0)));
    Menu mainMenu;
    // ===== INDIVIDUAL GAMES:
    mainMenu.addOption("1) Play SUS");
    mainMenu.addOption("2) Four-in-a-row");
    mainMenu.addOption("3) 5 x 5 Tic Tac Toe");
    mainMenu.addOption("4) Word Tic-tac-toe");
    mainMenu.addOption("5) Misere Tic Tac Toe");
    mainMenu.addOption("6) Diamond Tic-Tac-Toe");
    mainMenu.addOption("7) 4 x 4 Tic-Tac-Toe");
    mainMenu.addOption("8) Pyramid Tic-Tac-Toe");

    // ===== GROUP GAMES:
    mainMenu.addOption("9) Numerical Tic-Tac-Toe");
    mainMenu.addOption("10) Obstacles Tic-Tac-Toe");
    mainMenu.addOption("11) Infinity Tic-Tac-Toe");

    // ===== BONUS GROUP GAMES:
    mainMenu.addOption("12) Ultimate Tic Tac Toe");
    mainMenu.addOption("13) Memory Tic-Tac-Toe");

    // ===== exit option: do not move 
    mainMenu.addOption("Exit"); 
    // ===============
    bool running = true;

    while (running) {
        int selection = mainMenu.display();

        if (selection == mainMenu.getOptionCount() - 1) {
            running = false;
        }
        else {
            switch (selection) {
              // ===== INDIVIDUAL GAMES:
              case 0:  GameLaunchers::launch_sus_game(); break;
              case 1:  GameLaunchers::launch_four_in_a_row(); break;
              case 2:  GameLaunchers::launch_5x5_tic_tac_toe(); break;
              case 3:  GameLaunchers::launch_word_tic_tac_toe(); break;
              case 4:  GameLaunchers::launch_misere_tic_tac_toe(); break;
              case 5:  GameLaunchers::launch_diamond_tic_tac_toe(); break;
              case 6:  GameLaunchers::launch_4x4_tic_tac_toe(); break;
              case 7:  GameLaunchers::launch_pyramid_tic_tac_toe(); break;

              // ===== GROUP GAMES:
              case 8:  GameLaunchers::launch_numerical_tic_tac_toe(); break;
              case 9:  GameLaunchers::launch_obstacles_tic_tac_toe(); break;
              case 10: GameLaunchers::launch_infinity_tic_tac_toe(); break;

              // ===== BONUS GROUP GAMES:
              case 11: GameLaunchers::launch_ultimate_tic_tac_toe(); break;
              case 12: GameLaunchers::launch_memory_tic_tac_toe(); break;

              default: std::cout << "Invalid selection\n"; break;
            }
        }
    }
}
