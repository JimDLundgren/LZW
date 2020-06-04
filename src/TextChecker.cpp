#include "ReadFile.hpp"
#include "TextChecker.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

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
    ReadFile fileA(_pathA);
    ReadFile fileB(_pathB);

    fileA.getStream().seekg (0, std::ios::beg);
    std::streampos sizeA = fileA.getStream().tellg();
    fileA.getStream().seekg (0, std::ios::beg);

    fileB.getStream().seekg (0, std::ios::beg);
    std::streampos sizeB = fileB.getStream().tellg();
    fileB.getStream().seekg (0, std::ios::beg);

    if (sizeA != sizeB) {
        std::cerr << "Size differ between the two files:\n"
                  << _pathA << " : " << sizeA << '\n'
                  << _pathB << " : " << sizeB << std::endl;
        return false;
    }

    std::cout << "Texts found to have same length." << std::endl;
    return true;
}

bool TextChecker::checkSameText()
{
    ReadFile fileA(_pathA);
    ReadFile fileB(_pathB);

    std::string lineA;
    std::string lineB;
    while(fileA.getStream() && fileB.getStream()) {
        std::getline(fileA.getStream(), lineA);
        std::getline(fileB.getStream(), lineB);

        if (lineA != lineB) {
            std::cerr << "Text differ between the two files:\n"
                      << _pathA << " : " << lineA << '\n'
                      << _pathB << " : " << lineB << std::endl;
            return false;
        }
    }

    if (fileA.getStream() && !fileB.getStream()) {
        std::cerr << _pathA << " shorter than " << _pathB << std::endl;
        return false;
    }

    if (fileB.getStream() && !fileA.getStream()) {
        std::cerr << _pathB << " shorter than " << _pathA << std::endl;
        return false;
    }

    std::cout << "Texts found to be identical." << std::endl;
    return true;
}
