#include <fstream>
#include <string>

class ReadFile {
    std::ifstream _ifs;

public:
    ReadFile(std::string file);
    std::ifstream& getStream() { return _ifs; }
};
