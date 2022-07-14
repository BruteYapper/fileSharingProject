#include "../include/easyFiles.h"
// #include <experimental/filesystem>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

// namespace fs = std::experimental::filesystem;
namespace fs = std::filesystem;

void easyFiles::fillCurrentPaths(){
    
    
    for (auto const &dirEntry: fs::directory_iterator{fs::current_path()}){
        std::string name = dirEntry.path().string();
        int lastPos = name.rfind('/');


        if (dirEntry.is_directory()) // puts strings at the top or bottom of the vector
            currentPaths.insert(currentPaths.begin(), name.substr(lastPos, name.length()));
            
        else
            currentPaths.push_back(name.substr(lastPos+1, name.length()));

    }


}



std::vector<std::string> easyFiles::getCurrentPaths(){

    return currentPaths;

}





void easyFiles::moveDownDir(){
    fs::path currentPath (fs::current_path());
    int lastPos = currentPath.string().rfind('/');
    
    // std::cout << currentPath.string().substr(0,lastPos) << '\n';
    // std::cout << fs::current_path().string() << '\n';
    fs::current_path(currentPath.string().substr(0,lastPos)); // cuts cpp string at last '/' position and changes location in files system

    this->fillCurrentPaths(); // you don't need the "this->" but it looks cool

}


easyFiles::easyFiles(){
    fillCurrentPaths();
}
