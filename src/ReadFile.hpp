#include <fstream>
#include <string>

class ReadFile {
public:
    ReadFile(std::string file);
    std::ifstream& getStream() { return _ifs; }

private:
    std::ifstream _ifs;
};
