// #include <experimental/filesystem> // this works if your on an older version
#include "../include/easyFiles.h"
#include "../include/easyScreens.h"
#include "../include/fileTransfer.h"
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

    easyScreen firstWindow(10, 20, 3, 5);

    
    if (firstWindow.displayMenu({"Send", "Receive"}) == 0){
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



void host(int y, int x){ // handles the host window

    char IPaddress [20]; 
    {
        easyScreen getIPAddress(y-2, x/2, 1, 1, false);
        echo();
        getIPAddress.getIP(IPaddress); 
        noecho();
    }
    easyScreen secondWindow(y-2, x/2, 1, 1, true);
    easyFiles currentPath;

    std::vector<std::string> visibleFiles = currentPath.getCurrentPaths();
    // int pathInt = secondWindow.displayMenu(visibleFiles);
    int pathInt;


    secondWindow.topDirectoryBarDraw(currentPath.returnCurrentPath());
    while (true){ // main logic of finding the file

        visibleFiles = currentPath.getCurrentPaths(); // returns a vector of strings of all files and folders in current file.
        

        


        pathInt = secondWindow.displayMenu(visibleFiles);


        if (pathInt == 0){ // handles moving up and down directories
            currentPath.moveUpDir();
            secondWindow.topDirectoryBarDraw(currentPath.returnCurrentPath());
        } else{
            if (currentPath.moveDownDir(visibleFiles.at(pathInt)) != "folder"){

                fileTransfer wifi;
                wifi.setUpClientSocket(IPaddress); // client sends and host receives
                                
                wifi.sendFileClient(currentPath.moveDownDir(visibleFiles.at(pathInt)).c_str());

            }
            
            secondWindow.topDirectoryBarDraw(currentPath.returnCurrentPath());
        }

        

    }

    // secondWindow.hideWindow();


}

void receive(){ 
    fileTransfer wifi;
    wifi.setUpHostSocket();
    wifi.getFileHost();
    printf("Done");
}