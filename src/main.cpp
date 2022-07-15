// #include <experimental/filesystem> // this works if your on an older version
#include "../include/easyFiles.h"
#include <string>
#include <vector>
#include <ncurses.h>

using namespace std;

int printList(WINDOW, vector<string>);


int main()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    int height, width, startY, startX;
    getmaxyx(stdscr, height, width);

    WINDOW *win = newwin(10, 20, 2, 5);
    box(win, 0, 0);

    mvwprintw(win, 1, 1, "Send"); //TODO: turn window into class that deals with it's self
    mvwprintw(win, 2, 1, "Receive");

    refresh();
    wgetch(win);

    getch();
    endwin();
    return 0;
}





int printList(WINDOW *win, vector<string> items){
    char ch;
    do
    {
        /* code */
    } while (ch = wgetch(win));
    

}