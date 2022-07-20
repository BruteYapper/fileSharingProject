#include "../include/easyFiles.h"
// #include <experimental/filesystem>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

// namespace fs = std::experimental::filesystem;
namespace fs = std::filesystem;

void easyFiles::fillCurrentPaths(){
    currentPaths.clear();
    
    for (auto const &dirEntry: fs::directory_iterator{fs::current_path()}){
        std::string name = dirEntry.path().string();
        int lastPos = name.rfind('/');


        if (dirEntry.is_directory()) // puts strings at the top or bottom of the vector
            currentPaths.insert(currentPaths.begin(), name.substr(lastPos, name.length()));
            
        else
            currentPaths.push_back(name.substr(lastPos+1, name.length()));

    }

    currentPaths.insert(currentPaths.begin(), "/..");


}


std::vector<std::string> easyFiles::getCurrentPaths(){

    return currentPaths;

}


bool easyFiles::moveUpDir(std::string file){

    fs::directory_entry nextDir(file);

    if (!nextDir.is_directory()) // not a directory
        return false;
    else if (file.at(0) != '/')
        file = '/' + file;

    fs::current_path(file);
    this->fillCurrentPaths();

    return true;
}


void easyFiles::moveDownDir(){
    fs::path currentPath (fs::current_path());
    int lastPos = currentPath.string().rfind('/');
    
    // std::cout << currentPath.string().substr(0,lastPos) << '\n';
    // std::cout << fs::current_path().string() << '\n';
    fs::current_path(currentPath.string().substr(0,lastPos)); // cuts cpp string at last '/' position and changes location in files system

    this->fillCurrentPaths(); // you don't need the "this->" but it looks cool

}


std::string easyFiles::returnCurrentPath(){
    return fs::current_path().string();
}


easyFiles::easyFiles(){
    fillCurrentPaths();
}
