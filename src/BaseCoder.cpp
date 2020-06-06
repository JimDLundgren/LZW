#include "BaseCoder.hpp"

#include <iostream>
#include <stdexcept>

namespace lzw {

void BaseCoder::printDictionary(std::map<std::string, int> const& dict) {
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
