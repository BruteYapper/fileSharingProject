#pragma once
#include <vector>
#include <string>
#include <ncurses.h>

class easyScreen {
private:
    // vars for the window
    int height, width, startY, startX;
    WINDOW *win;

public:
    // display vector of strings and return index of item selected
    void displayMenu(std::vector<std::string> menu);
    // hides the window
    void hideWindow();
    //constructor for the window
    easyScreen(int height, int width, int startY, int startX);
    // distructor that uses clear() to clear the window
    ~easyScreen();
};