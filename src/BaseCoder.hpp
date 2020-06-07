#pragma once

#include <filesystem>
#include <map>
#include <string>

namespace lzw {

class BaseCoder {
public:
    virtual int run(std::string inFile) = 0;
    std::filesystem::path createOutFilePathBasedOnInFile(std::filesystem::path inFilePath
                                                        , std::string extension);
    void printDictionary(std::map<std::string, int> const& dict);
};

} //lzw
