#pragma once

#include "BaseCoder.hpp"

namespace lzw {

class Encoder : public BaseCoder {
public:
    int run(std::string inFile, std::string outFile = "") override;
};

} // lzw
