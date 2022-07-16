#include "../include/easyScreens.h"
#include <ncurses.h>


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


easyScreen::~easyScreen(){

    delwin(win);

}