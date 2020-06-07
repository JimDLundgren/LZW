#include "Decoder.hpp"
#include "Encoder.hpp"
#include "TextChecker.hpp"

#include <exception>
#include <iostream>
#include <string>

// TODO: could improve cli with e.g. Boost.Program_options.
int main (int argc, char *argv[])
{
    std::string mode(argv[1]);
    try {
        if (mode == "encode")
        {
            if (argc == 3) {
                lzw::Encoder enc;
                enc.run(argv[2], "");
            } else if (argc == 4) {
                lzw::Encoder enc;
                enc.run(argv[2], argv[3]);
            } else {
                std::cerr << "Incorrect input: One file to encode required, "
                          << "one .ENC output file optional." << std::endl;
                return -1;
            }
        }
        else if (mode == "decode")
        {
            if (argc == 3) {
                lzw::Decoder dec;
                dec.run(argv[2], "");
            } else if (argc == 4) {
                lzw::Decoder dec;
                dec.run(argv[2], argv[3]);
            } else {
                std::cerr << "Incorrect input: One .ENC file to decode required, "
                          << "one output file optional." << std::endl;
                return -1;
            }
        }
        else if (mode == "check")
        {
            if (argc != 4) {
                std::cerr << "Need two files as input to compare" << std::endl;
                return -1;
            }

            lzw::TextChecker tc(argv[2], argv[3]);
            auto const isSame(tc.checkSame());
        }
        else
        {
            std::cerr << "Expected one of the following inputs: "
                      << "encode, decode, or check." << std::endl;
            return -1;
        }
    }
    catch(std::exception const& ex)
    {
        std::cerr << "Caught exception with message:\n"
                  << ex.what() << std::endl;
        return -1;
    }

    return 0;
}
