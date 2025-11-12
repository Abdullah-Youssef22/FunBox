#include "../include/Menu.h"
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

Menu::Menu() : currentSelection(0) {
    options = {
        "Play XO",
        "Play SUS",
        "Play Connect 4",
        "Exit"
    };
}

void Menu::addOption(const std::string& option) {
    options.push_back(option);
}

void Menu::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int Menu::getKeyPress() {
#ifdef _WIN32
    int key = _getch();
    if (key == 0 || key == 224) {
        key = _getch();
        switch(key) {
            case 72: return 'w';
            case 80: return 's';
        }
    }
    return key;
#else
    // =============================== linux terminal version
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    // ====================================== ignore this pls :)

    int key = getchar();
    
    if (key == 27) {
        getchar();
        key = getchar();
        switch(key) {
            case 'A': key = 'w'; break;
            case 'B': key = 's'; break;
        }
    }
    // ========================================  
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // just another linux bit to restore
    // ======================================== // the previous terminal settings 
    return key;
#endif
}

int Menu::display() {
    while(true) {
        clearScreen();
        
        std::cout << "\n\n";
        std::cout << "        ╔═══════════════════════════════╗\n";
        std::cout << "        ║     FUNBOX GAME COLLECTION    ║\n";
        std::cout << "        ╚═══════════════════════════════╝\n\n";
        
        for(size_t i = 0; i < options.size(); i++) {
            if(i == currentSelection) {
                std::cout << "        ► ";
            } else {
                std::cout << "          ";
            }
            std::cout << options[i] << "\n";
        }
        
        std::cout << "\n\n        Use ↑↓ or W/S to navigate, Enter to select\n";
        
        int key = getKeyPress();
        
        switch(key) {
            case 'w':
            case 'W':
                currentSelection = (currentSelection - 1 + options.size()) % options.size();
                break;
            case 's':
            case 'S':
                currentSelection = (currentSelection + 1) % options.size();
                break;
            case '\r':
            case '\n':
                clearScreen();
                return currentSelection;
        }
    }
}

Menu::~Menu() {}
