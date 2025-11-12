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
    void addOption(const std::string& option);
    int display();
    int getOptionCount() const { return options.size(); }
    ~Menu();
};

#endif
