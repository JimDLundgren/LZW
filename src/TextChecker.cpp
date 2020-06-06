#include "TextChecker.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace lzw {

TextChecker::TextChecker(std::string pathA, std::string pathB)
    : _pathA(pathA), _pathB(pathB)
    {}

bool TextChecker::checkSame() {
    auto const isLengthSame = checkSameLength();
    auto const isTextSame = checkSameText();

    if (isLengthSame && isTextSame) {
        return true;
    }
    return false;
}

bool TextChecker::checkSameLength()
{
    std::ifstream fileA(_pathA);
    if (!(fileA.is_open())) {
        throw std::runtime_error(("Unable to open file: " + _pathA));
    }

    std::ifstream fileB(_pathB);
    if (!(fileB.is_open())) {
        throw std::runtime_error(("Unable to open file: " + _pathB));
    }

    fileA.seekg (0, std::ios::beg);
    std::streampos sizeA = fileA.tellg();
    fileA.seekg (0, std::ios::beg);

    fileB.seekg (0, std::ios::beg);
    std::streampos sizeB = fileB.tellg();
    fileB.seekg (0, std::ios::beg);

    if (sizeA != sizeB) {
        std::cout << "Size differ between the two files:\n"
                  << _pathA << " : " << sizeA << '\n'
                  << _pathB << " : " << sizeB << std::endl;
        return false;
    }

    std::cout << "Texts found to have same length." << std::endl;
    return true;
}

bool TextChecker::checkSameText()
{
    std::ifstream fileA(_pathA);
    if (!(fileA.is_open())) {
        throw std::runtime_error(("Unable to open file: " + _pathA));
    }

    std::ifstream fileB(_pathB);
    if (!(fileB.is_open())) {
        throw std::runtime_error(("Unable to open file: " + _pathB));
    }

    std::string lineA;
    std::string lineB;
    while(fileA && fileB) {
        std::getline(fileA, lineA);
        std::getline(fileB, lineB);

        if (lineA != lineB) {
            std::cout << "Text differ between the two files:\n"
                      << _pathA << " : " << lineA << '\n'
                      << _pathB << " : " << lineB << std::endl;
            return false;
        }
    }

    if (fileA && !fileB) {
        std::cout << _pathA << " shorter than " << _pathB << std::endl;
        return false;
    }

    if (fileB && !fileA) {
        std::cout << _pathB << " shorter than " << _pathA << std::endl;
        return false;
    }

    std::cout << "Texts found to be identical." << std::endl;
    return true;
}

} // lzw
