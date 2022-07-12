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
