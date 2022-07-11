#include <experimental/filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem;

int main()
{
    fs::path p {"main.cpp"};
    std::cout << "Current path is " << fs::current_path() << "\n";
    std::cout << "Absolute path for " << p << " is " << fs::absolute(p) << "\n";
    
    for (auto const &dirEntry: fs::directory_iterator{fs::current_path()}){
        std::cout << dirEntry << '\n';
    }

    std::cout << "====================================\n";
    
    fs::current_path(fs::current_path()+="/test");


    for (auto const &dirEntry: fs::directory_iterator{fs::current_path()}){
        std::cout << dirEntry << '\n';
    }


    return 0;
}