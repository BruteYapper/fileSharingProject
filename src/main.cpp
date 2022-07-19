// #include <experimental/filesystem> // this works if your on an older version
#include "../include/easyFiles.h"
#include "../include/easyScreens.h"
#include <string>
#include <vector>
#include <ncurses.h>
#include <iostream>

using namespace std;


void host(int, int);
void receive();



int main()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);


    int yMax, xMax;

    getmaxyx(stdscr, yMax, xMax);

    easyScreen firstWindow(10, 20, 3, 5, false);

    
    if (firstWindow.displayMenu({"Host", "Receive"}) == 0){
        firstWindow.hideWindow();
        host(yMax, xMax);
    }
    else{
        firstWindow.hideWindow();
        receive();
    }
    

    // getch();
    endwin();
    return 0;
}



void host(int y, int x){

    easyScreen searchFiles(y-2, x/2, 1, 1, true);

    searchFiles.displayMenu({"nice", "ok", "cool", "bed time!"});

    // while(true){

    // }


}

void receive(){

}