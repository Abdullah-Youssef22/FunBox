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
    
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    #endif
}

void Menu::addOption(const std::string& option) {
    options.push_back(option);
}

void Menu::clearScreen() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    
    FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
#else
    system("clear");
#endif
}

int Menu::getKeyPress() {
#ifdef _WIN32
    int key = _getch();
    
    // Handle arrow keys (they send two bytes: 224 then the key code)
    if (key == 0 || key == 224) {
        key = _getch();
        switch(key) {
            case 72: return 'w';  // Up arrow
            case 80: return 's';  // Down arrow
        }
    }
    
    // ADDED: Handle both \r and \n for Enter key
    if (key == 13) {  // 13 is \r on Windows
        return '\n';
    }
    
    return key;
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    int key = getchar();
    
    if (key == 27) {
        getchar();
        key = getchar();
        switch(key) {
            case 'A': key = 'w'; break;
            case 'B': key = 's'; break;
        }
    }
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return key;
#endif
}

int Menu::display() {
    while(true) {
        clearScreen();
        
        std::cout << "\n\n";
        std::cout << "  " << BLUE << "======================================" << RESET << "\n";
        std::cout << "      " << CYAN << "FUNBOX GAME COLLECTION" << RESET << "\n";
        std::cout << "  " << BLUE << "======================================" << RESET << "\n\n";

        for (size_t i = 0; i < options.size(); i++) {
            if (i == currentSelection) {
                std::cout << "    " << BRIGHT_GREEN << "--> " << options[i] << RESET << "\n";
            }
            else {
                std::cout << "        " << WHITE << options[i] << RESET << "\n";
            }
        }

        std::cout << "\n  " << YELLOW << "Use W/S or Arrow Keys, Enter to select" << RESET << "\n";
        std::cout << "  " << BLUE << "======================================" << RESET << "\n";

        
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
               /* clearScreen();*/
                return currentSelection;
        }
    }
}
Menu::~Menu() {}
