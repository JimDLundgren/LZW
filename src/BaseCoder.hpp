#include <map>
#include <string>
#include <iostream>

class BaseCoder
{
public:
    virtual int run() = 0;

    // TODO: Store starting dictonary in a member variable and
    // print that. This print also just checks that the starting
    // letters are in it and prints them...
    // TODO: Move the definition of the function to a cpp file.
    void printStartingDictionary(std::map<std::string, int> const& dict) {
        std::cout << "Starting dictionary content:\n";
        for(int i = 0; i < 256; ++i){
            char temp_c = i;
            std::string temp(1, temp_c);
            std::cout << dict.find(temp)->first << " ";
        }
        std::cout << std::endl;
    }
};
