#include "../include/easyScreens.h"
#include <ncurses.h>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

easyScreen::easyScreen(int height, int width, int startY, int startX, bool dirOn)
    : height{height}, width{width}, startY {startY}, startX {startX}, dirOn{dirOn} {


    if (dirOn == true){
        win = newwin(height-3, width, startY+3, startX);
        display = newwin(3, width, startY+1, startX);
    }
    else{
        win = newwin(height, width, startY, startX);
    }
    box(win, 0, 0);
    refresh();
    wrefresh(win);
    if(dirOn){
        box(display, 0, 0);
        wrefresh(display);
    }


}



void easyScreen::hideWindow(){
    wclear(win);
    wrefresh(win);
}





void easyScreen::topDirectoryBarDraw(std::string dir){
    wclear(display);
    box(display, 0, 0);
    mvwprintw(display, 1, 1, dir.c_str());
    refresh();
    wrefresh(display);

}


void easyScreen::getIP(char* IP){
    wmove(win, 1, 1);

 //TODO: make this functon get a series of inputs from user and put them in the passed in array

    for (size_t i = 0; IP[i] != '\n'; i++){ //* let it terminate when teh user is done ()
        IP[i] = wgetch(win);
    }

    
}


int easyScreen::displayMenu(std::vector<std::string> menu){

    

    
    keypad(win, true);

    werase(win);
    box(win, 0, 0);
    wrefresh(win);


    int choice;
    unsigned short int heighlight = 0;
    

    bool runScreen = true;

    do
    {
        switch (choice) // handles user input
        { // TODO: add short cuts to moving up and down directories
        case KEY_UP:
        case 119:
            (heighlight != 0)? heighlight-- : heighlight;
            break;
        
        case KEY_DOWN:
        case 115:
            (heighlight != (menu.size()-1))? heighlight++ : heighlight;
            break;



        case 10: // enter key
        case 32: //space bar
            runScreen = false;
            break;


        default:
            break;
        }




        for (size_t i = 0; i < menu.size(); i++) // prings out list
        {
            if (heighlight == i){
                wattron(win, A_REVERSE);
                mvwprintw(win, i+1, 1, menu.at(i).c_str());
                wattroff(win, A_REVERSE);
            }
            else
                mvwprintw(win, i+1, 1, menu.at(i).c_str());
        }




        wrefresh(win);



    } while (runScreen && (choice = wgetch(win)));
    



    return heighlight;

    // "space bar(key)" is 32 and "enter(key)" is 10

}



easyScreen::~easyScreen(){

    delwin(win);
    delwin(display);

}