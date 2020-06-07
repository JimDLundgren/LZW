#include "BaseCoder.hpp"

#include <chrono>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

namespace lzw {

std::filesystem::path
BaseCoder::createOutFilePathBasedOnInFile(fs::path inFilePath, std::string extension)
{
    // The output file has the same name as the input file, but of type
    // "extension". If a file with the same name as the output file already
    // exists, append the current time (since epoch) to its name.
    fs::path outFilePath = inFilePath.parent_path();
    outFilePath /= inFilePath.stem();
    outFilePath += extension;

    if (fs::exists(outFilePath)) {
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        );
        auto count = ms.count();
        outFilePath = inFilePath.parent_path();
        outFilePath /= inFilePath.stem();
        outFilePath += ("_" + std::to_string(count));
        outFilePath += extension;
    }

    return outFilePath;
}

void BaseCoder::printDictionary(std::map<std::string, int> const& dict)
{
    if (dict.size() < 256) {
        throw std::runtime_error("Dictionary should at least contain 256 words (ASCII)");
    }

    std::cout << "Dictionary content:\n";
    for(int i = 0; i < dict.size(); ++i){
        for(auto const& [key, val] : dict) {
            if (val == i) {
                std::cout << key << " ";
            }
        }
    }
    std::cout << std::endl;
}

} // lzw
