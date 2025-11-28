#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include"colors.h"
class Menu {
private:
    std::vector<std::string> options;
    int currentSelection;
    
    void clearScreen();
    int getKeyPress();
    
public:
    Menu();
    static bool noOptionChosen;
    void addOption(const std::string& option);
    int display(bool enhanced);
    bool kbhit();
    int displayMenu(bool enhancedMenu);
    int getOptionCount() const;
    ~Menu();
};

#endif
