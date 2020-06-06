#include "BaseCoder.hpp"

namespace lzw {

class Decoder : public BaseCoder {
public:
    int run(std::string inFile) override;
};

} // lzw
