// #include <iostream> 
// #include <string>  
// #include <vector>   
// #include <memory>  
#include "../include/Menu.h"
#include "../include/GameLaunchers.h"
#include <ctime>
#include <iostream>

int main() {
    srand(static_cast<unsigned int>(time(0)));
    Menu mainMenu;
    // ======== we use the "add option" method to add a new game 
    //  ======   this way we don't touch the Menu.cpp file.
    mainMenu.addOption("Play XYZ"); 
    // we add our now options IN ORDER here. dont add options after "Exit" because it's the last option
  
    mainMenu.addOption("Exit"); 
    // ===============
    bool running = true;

    while (running) {
        int selection = mainMenu.display();

        switch (selection) {
            case 0: GameLaunchers::launch_xo_game(); break;
            // case 1: GameLaunchers::launch_sus_game(); break; // we uncomment this
            // case 2: GameLaunchers::launch_connect4_game(); break; // and this, once we finished makign the games
            // case 3, 4, 5 ... etc ... same as above

            case 9: running = false; break; // last case for exit
            default: std::cout << "Invalid selection\n"; break;
        }
    }
}
