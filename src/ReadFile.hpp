#include <fstream>
#include <string>

namespace lzw {

class ReadFile {
    std::ifstream _ifs;

public:
    ReadFile(std::string file);
    std::ifstream& getStream() { return _ifs; }
};

} // lzw
