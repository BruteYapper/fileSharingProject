#pragma once
#include <string>
#include <vector>

class easyFiles {
private:
    std::vector<std::string> currentPaths;
    void fillCurrentPaths(); // fills "currentPaths" vector of strings of the names of files and folders (folders have '/' in front of there name)

public: // TODO: make public work
    // get vector of options
    std::vector<std::string> getCurrentPaths();
    // move up a directory
    bool moveUpDir(); // return true if the move was sucessful // false if it was a file
    // move down a directory
    void moveDownDir();
    // constructor
    easyFiles();



};