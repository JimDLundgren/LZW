#include "TextChecker.hpp"

#include <iostream>
#include <string>

// TODO: decide whether to use use exceptions or cerr + error code.

int main (int argc, char *argv[])
{
    // TODO: could improve cli with e.g. Boost.Program_options.
    std::string mode(argv[1]);
    if (mode == "encode") {
        // TODO: call encoder
    } else if (mode == "decode") {
        // TODO: call decoder
    } else if (mode == "check") {
        if (argc != 4) {
            std::cerr << "Need two files as input to compare" << std::endl;
            return -1;
        }
        TextChecker tc("InputText\\OriginalText.txt", "InputText\\DecodedText.txt");
        tc.checkSameLength();
        tc.checkSameText();
    } else {
        std::cerr << "Expected one of the following first input: "
                  << "encode, decode, or check." << std::endl;
        return -1;
    }

    return 0;
}
