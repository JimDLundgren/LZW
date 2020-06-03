#include "ReadFile.hpp"

#include <iostream>

ReadFile::ReadFile(std::string file){
    _ifs.open(file);
    if (!(_ifs.is_open()))
    {
        std::cerr << "Unable to open input file" << std::endl;
    }
}
