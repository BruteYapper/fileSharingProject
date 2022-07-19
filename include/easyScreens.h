#pragma once
#include <vector>
#include <string>
#include <ncurses.h>

class easyScreen {
private:
    // vars for the window
    int height, width, startY, startX; 
    WINDOW *win;
    WINDOW *display; //TODO: implament this window at the top of the application~
    bool dirOn;
    // sets a bool to true and handles displaying a string at the top


public:
    void topDirectoryBarDraw(std::string dir);
    // display vector of strings and return index of item selected
    int displayMenu(std::vector<std::string> menu);
    // hides the window
    void hideWindow();
    //constructor for the window
    easyScreen(int height, int width, int startY, int startX, bool dirOn); // TODO: figrue out how to give the last param a default value
    // distructor that uses clear() to clear the window
    ~easyScreen();
};