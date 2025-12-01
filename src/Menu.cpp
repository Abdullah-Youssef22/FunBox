#include "../include/util/Menu.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread> 
#include <chrono>
#include <future>



#ifndef _WIN32
    #include <fcntl.h>
    #include <unistd.h>
#endif

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif




bool Menu::noOptionChosen = true;

Menu::Menu() {
    currentSelection = 0;  
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

bool Menu::kbhit() {
#ifdef _WIN32
    return _kbhit() != 0;
#else
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    
    return false;
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
    
    if (key == 13) {
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


int Menu::getOptionCount() const {
  return options.size(); 
}


int Menu::displayMenu(bool enhancedMenu) {
    std::vector<std::string> asciiArt = {
        "⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀⣀⣀⣶⣶⣶⣶⣶⣶⣆⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀ ⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀ ⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀ ⠀⠀⣿⠋⠁⠀⣀⠀⢹⣿⣿⣿⠀⢀⡀⠀⠉⢻⡇⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀ ⠀⠀⢹⣆⡀⠀⠉⠀⣾⡟⠙⣿⡄⠈⠁⠀⣀⣾⠁⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀ ⠀⠀⢠⣿⡟⢯⣭⣾⣿⣀⣀⣻⣿⣮⣽⠛⢿⣧⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀ ⠀⠀⠀⠸⣧⣄⠒⢠⣙⢛⡛⣛⣛⢛⡋⡄⣠⣴⡟⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀ ⢀⣶⣦⡀⠙⠿⣷⣶⣭⣘⣃⣘⣃⣘⣥⣾⡿⠏⣡⣾⠟⠒⠀⠀⠀⠀",
        "⠀⠀⠀ ⠀⠂⠈⠙⠛⢶⣄⠀⠀⠛⡛⠛⠋⣛⠛⠃⠀⢀⣠⡿⠃⠀⠀⢦⡀⠀⠀",
        "⠀⠀ ⡠⠊⠀⠀⣴⠀⠀⠈⡟⠒⡤⠙⠿⠿⠁⠤⢶⠚⠉⠉⠀⢠⠁⠀⠀⠱⣄⠀",
        "⠀ ⢠⠁⠀⠀⠀⣿⡀⣀⣀⡁⠤⡇⢰⣷⣶⡄⣴⢼⠀⠀⢀⣠⢿⠀⠀⠀⠀⢹⡄",
        " ⠰⢿⠀⠀⠀⢠⡉⠉⠀⠀⠀⡄⢺⢸⣿⣿⡇⡗⢺⢰⠈⠉⠀⠘⡆⠀⠀⠀⠀⡇",
        "⠀ ⠈⠳⣄⡀⢸⡇⠀⠀⠀⠀⣡⢚⢸⣿⣿⠇⠗⣆⠆⠀⠀⠀⠀⡇⠀⠀⢀⡴⠃",
        "⠀ ⠀⠀⠈⠃⠘⣷⣤⠀⠀⠀⢹⣾⣶⠒⠒⠀⢳⣧⣤⣄⣠⣄⣾⠃⢴⠆⠉⠀⠀",
        "⠀⠀⠀⠀⠀ ⠀⠈⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⢉⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀ ⠀⠀⢰⠀⢠⡟⠀⠀⠀⠀⢀⢄⠀⠀⠀⢸⡇⠀⠀⠨⡆⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀ ⡘⢀⣜⠇⠀⠀⠀⠀⢸⠸⡀⠀⠀⢸⣿⠀⠀⠀⢡⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀ ⠀⡇⢸⣿⠀⠀⠀⠀⠠⡇⠀⡇⠀⠀⠈⣿⠀⠀⠀⢸⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀ ⠀⠀⠙⠛⠋⠤⠤⠤⠤⠄⠁⠀⠁⠤⠄⠠⠿⠧⠄⠛⠛⠀⠀⠀⠀⠀",
        "⠀⠀⠀ ⠀ ⢀⣴⣶⣦⣄⠲⣶⠀⠀⠀⠀⠀⠀⠀⢠⣷⣶⡶⢂⣠⣴⣶⣤⡀⠀⠀",
        "⠀⠀⠀⠀  ⠸⠿⠿⠿⠿⠧⠠⠄⠀⠀⠀⠀⠀⠀⠤⠤⠤⠐⠿⠿⠿⠿⠿⠿⠃⠀⠀"
    };
    
    int bobOffset = 0;
    bool bobDirection = true;
    
    while(true) {
        clearScreen();
        
        if (!enhancedMenu) {
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



        } else { 

          ///////////////////////////////////////////// NON ASCII VERSION OF MENU
          int choiceWidth = 26; 
          std::cout << "\n\n";
          std::cout << "  " << BLUE << "╔══════════════════════════════════════╗" << RESET << "\n";
          std::cout << BLUE <<       "  ║        FUNBOX GAME COLLECTION        ║" << RESET << "\n";
          std::cout << "  " << BLUE << "╠══════════════════════════════════════╣" << RESET << "\n";


          for (size_t i = 0; i < options.size(); i++) {
              std::string option = options[i];

              // Calculate how much whitespace to append
              int spacesToAdd = choiceWidth - option.length();
              if (spacesToAdd > 0) {
                  // Append spaces to make the option the desired width
                  option.append(spacesToAdd, ' ');
              }

              if (i == currentSelection) {
                  // Highlight the selected option
                  std::cout << BLUE << "  ║  " << CYAN << "  > " << BG_WHITE << BLUE << "  " << option  << RESET << BLUE  << "    ║" << RESET << "\n";
              } else {
                  // Regular option
                  std::cout << BLUE << "  ║       " << WHITE  << option << RESET << BLUE  << "     ║ \n" << RESET ;
              }
          }

          std::cout << BLUE <<  "  ║  " << YELLOW << "Use up/down Keys, Enter to select" << BLUE << "   ║ " << RESET << "\n";
          std::cout << "  " << BLUE << "╚══════════════════════════════════════╝" << RESET << "\n";

          std::vector<int> offsets(asciiArt.size(), 0); 
          int linesFromTop = 14;
          for (int i = 0; i < linesFromTop; i++) offsets[i] = 2;
          for (int i = linesFromTop; i < 19; i++) offsets[i] = 1;

          int lines = asciiArt.size();
          for (size_t i = 0; i < asciiArt.size(); i++) {
              std::cout << WHITE << std::string(offsets[i] * bobOffset, ' ') << asciiArt[i] << "\n" << RESET;
          }


          std::cout.flush();

          if (bobDirection) {
              bobOffset++;
              if (bobOffset >= 2) bobDirection = false;
          } else {
              bobOffset--;
              if (bobOffset <= 0) bobDirection = true;
          }
        }



        
        if (kbhit()) {
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
                    return currentSelection;
            }
        } 
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}




int Menu::display(bool enhanced) {
  int value = Menu::displayMenu(enhanced);
  return value;
}


Menu::~Menu() {}
