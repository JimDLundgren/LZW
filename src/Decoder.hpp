#include "BaseCoder.hpp"

// TODO: Need to take in a file path to decode, and
// create an encoded file who's name is based on it.
class Decoder : public BaseCoder
{
public:
    int run() override;
};
