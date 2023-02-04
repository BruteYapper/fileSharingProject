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
    std::string tempString {""};
    int temp {0};
    for (size_t i = 0; i < 20; ){ //* let it terminate when the user is done 
        temp = wgetch(win);
        
        
        // mvwprintw(win, 1, 1, to_string(temp).c_str());
        
        if (temp == 127){
            // tempString.at(i) = '\0';
            if (i > 0){
                i--;    
                tempString.pop_back();
            }   
        } else{
            tempString += char(temp);
            i++;
            mvwprintw(win, 1, 1, tempString.c_str());

        }

        mvwprintw(win, 1, i+1, " "); // erases the last character that was deleted on the screen
    
        
        if (tempString[tempString.length()-1] == '\n')
        {
            tempString[tempString.length()-1] = '\0';
            
            for (size_t j = 0; j < tempString.length(); j++)
            {
                IP[j] = tempString[j];
            }
            
            mvwprintw(win, 2, 1, IP);

            break;
        }
    }

    if (IP[0] == '\0'){
        IP = "127.0.0.1";
    }
}


int easyScreen::displayMenu(std::vector<std::string> menu){

    

    
    keypad(win, true);

    werase(win);
    box(win, 0, 0);
    wrefresh(win);


    int choice;
    unsigned short int highlight = 0;
    

    bool runScreen = true;

    do
    {
        switch (choice) // handles user input
        {
        case KEY_UP:
        case 119:
            (highlight != 0)? highlight-- : highlight;
            break;
        
        case KEY_DOWN:
        case 115:
            (highlight != (menu.size()-1))? highlight++ : highlight;
            break;


        case KEY_RIGHT:
        case 10: // enter key
        case 32: //space bar
            runScreen = false;
            break;

        case KEY_LEFT:
            highlight = 0;
            runScreen = false;
            break;

        default:
            break;
        }




        for (size_t i = 0; i < menu.size(); i++) // prings out list
        {
            if (highlight == i){
                wattron(win, A_REVERSE);
                mvwprintw(win, i+1, 1, menu.at(i).c_str());
                wattroff(win, A_REVERSE);
            }
            else
                mvwprintw(win, i+1, 1, menu.at(i).c_str());
        }




        wrefresh(win);



    } while (runScreen && (choice = wgetch(win)));
    



    return highlight;

    // "space bar(key)" is 32 and "enter(key)" is 10

}



easyScreen::~easyScreen(){

    delwin(win);
    delwin(display);

}