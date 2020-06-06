#include <map>
#include <string>

namespace lzw {

class BaseCoder {
public:
    virtual int run(std::string inFile) = 0;
    void printDictionary(std::map<std::string, int> const& dict);
};

} //lzw
