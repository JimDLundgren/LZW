#include "Decoder.hpp"
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
            // TODO: call encoder
        }
        else if (mode == "decode")
        {
            if (argc != 3) {
                std::cerr << "Need two files as input to compare" << std::endl;
                return -1;
            }
            lzw::Decoder dc;
            dc.run(argv[2]);
        }
        else if (mode == "check")
        {
            if (argc != 4) {
                std::cerr << "Need two files as input to compare" << std::endl;
                return -1;
            }

            lzw::TextChecker tc(argv[2], argv[3]);
            auto const isSame(tc.checkSame());

            if (!isSame) {
                return -1;
            }
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
    }

    return 0;
}
