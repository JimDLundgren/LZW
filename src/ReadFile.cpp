#include "ReadFile.hpp"

#include <iostream>
#include <stdexcept>

ReadFile::ReadFile(std::string file){
    _ifs.open(file);
    if (!(_ifs.is_open())) {
        throw std::runtime_error(("Unable to open file: " + file));
    }
}
