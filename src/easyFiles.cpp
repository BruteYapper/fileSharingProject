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
            currentPaths.insert(currentPaths.begin(), name.substr(lastPos, name.length())); // if it is a directory it leaves the '/'
            
        else
            currentPaths.push_back(name.substr(lastPos+1, name.length()));

    }

    currentPaths.insert(currentPaths.begin(), "/..");


}


std::vector<std::string> easyFiles::getCurrentPaths(){

    return currentPaths;

}


std::string easyFiles::moveDownDir(std::string file){


    if (file.at(0) == '/'){ // checks if it's a directory
        fs::current_path(file.substr(1, file.size()-1)); // this can't have a '/' in front of the name
        this->fillCurrentPaths();
        return "folder";
    }
    else{
        std::string currentPath = fs::current_path();
        return  currentPath + "/" + file;
    }


}


void easyFiles::moveUpDir(){
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
