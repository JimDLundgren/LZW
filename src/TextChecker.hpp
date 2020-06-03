#include <string>

class TextChecker {
public:
    TextChecker(std::string pathA, std::string pathB);
    void checkSameText();
    void checkSameLength();

private:
    std::string _pathA;
    std::string _pathB;
};
