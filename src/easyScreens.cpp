#include "../include/easyScreens.h"
#include <ncurses.h>
#include <vector>
#include <string>

using namespace std;

easyScreen::easyScreen(int height, int width, int startY, int startX)
    : height{height}, width{width}, startY {startY}, startX {startX} {

    win = newwin(height, width, startY, startX);
    box(win, 0, 0);
    refresh();
    wrefresh(win);


}



void easyScreen::hideWindow(){
    wclear(win);
    wrefresh(win);
}


int easyScreen::displayMenu(std::vector<std::string> menu){

    for (size_t i = 0; i < menu.size(); i++)
    {
        mvwprintw(win, i+1, 1, menu.at(i).c_str());
    }
    
    wrefresh(win);


    return 0; //TODO: make this return the index of the option selected

}



easyScreen::~easyScreen(){

    delwin(win);

}