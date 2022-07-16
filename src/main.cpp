// #include <experimental/filesystem> // this works if your on an older version
#include "../include/easyFiles.h"
#include "../include/easyScreens.h"
#include <string>
#include <vector>
#include <ncurses.h>

using namespace std;




int main()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    easyScreen main(10, 20, 3, 5);

    main.displayMenu({"nice", "sweet"});


    getch();
    endwin();
    return 0;
}



