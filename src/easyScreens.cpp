#include "../include/easyScreens.h"
#include <ncurses.h>
#include <vector>
#include <string>

using namespace std;

easyScreen::easyScreen(int height, int width, int startY, int startX)
    : height{height}, width{width}, startY {startY}, startX {startX} {


    if (dirOn == true){
        win = newwin(height-3, width, startY-3, startX);
        // display = newwin(3, width, startY, startX);
    }
    else{
        win = newwin(height, width, startY, startX);
    }
    box(win, 0, 0);
    // box(display, 0, 0);
    refresh();
    wrefresh(win);


}



void easyScreen::hideWindow(){
    wclear(win);
    wrefresh(win);
}





// void easyScreen::topDirectoryBarDraw(std::string dir){
//     mvwprintw(display, 1, 1, dir.c_str());
//     mvwprintw(display, 2, 1, string(width/2, '=').c_str());

// }


int easyScreen::displayMenu(std::vector<std::string> menu){

    

    
    keypad(win, true);

    int choice;
    unsigned short int heighlight = 0;
    

    bool runScreen = true;

    do
    {
        switch (choice)
        {
        case KEY_UP:
        case 119:
            (heighlight != 0)? heighlight-- : heighlight;
            break;
        
        case KEY_DOWN:
        case 115:
            (heighlight != (menu.size()-1))? heighlight++ : heighlight;
            break;





        case 10: // enter key
            runScreen = false;
            break;

        case 32: //space bar
            runScreen = false;
            break;


        default:
            break;
        }




        for (size_t i = 0; i < menu.size(); i++)
        {
            if (heighlight == i){
                wattron(win, A_REVERSE);
                mvwprintw(win, i+1, 1, menu.at(i).c_str());
                wattroff(win, A_REVERSE);
            }
            else
                mvwprintw(win, i+1, 1, menu.at(i).c_str());
        }

        // if (dirOn){
        //     this->topDirectoryBarDraw("test");
        //     wrefresh(display);
        // }


        wrefresh(win);



    } while (runScreen && (choice = wgetch(win)));
    



    return heighlight; //TODO: make this return the index of the option selected

    // "space bar(key)" is 32 and "enter(key)" is 10

}



easyScreen::~easyScreen(){

    delwin(win);

}