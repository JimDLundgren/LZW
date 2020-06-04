#include <string>

class TextChecker {
    std::string _pathA;
    std::string _pathB;

public:
    TextChecker(std::string pathA, std::string pathB);
    bool checkSame();

private:
    bool checkSameLength();
    bool checkSameText();
};
