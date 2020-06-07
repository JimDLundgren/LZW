#include "Decoder.hpp"
#include "Encoder.hpp"
#include "TextChecker.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

// TODO: Use GoogleTest framework for testing.
// TODO: Add more test cases for edge cases and
// checking all code paths (negative tests).

namespace {
class TestDirRAII {
    fs::path _testDir;
    bool _testPassed = false;

public:
    TestDirRAII() : _testDir("TestDir")
    {
        fs::create_directory(_testDir);
    }

    ~TestDirRAII()
    {
        if (_testPassed) {
            fs::remove_all("TestDir");
        } else {
            std::cout << "Preserving test files upon failure." << std::endl;
        }
    }

    std::string string() {
        return _testDir.string();
    }

    void setTestPassed(bool result) {
        _testPassed = result;
    }
};

} //namespace

int main()
{
    TestDirRAII testDir;

    std::string origFile(testDir.string() + "\\OriginalText.txt");
    std::ofstream origFileOfs(origFile);
    if (!origFileOfs.is_open()) {
        throw std::runtime_error(("Unable to open file: " + origFile));
    }

    origFileOfs << "Hello World!" << std::endl;
    origFileOfs << "aAaAaAaAaA" << std::endl;
    origFileOfs << "dnsfiohgu4b7547hfndy875@)*$&^40303jfidsn" << std::endl;
    origFileOfs << "burija" << std::endl;

    origFileOfs.close();

    std::string encFile(testDir.string() + "\\EncodedText.ENC");
    lzw::Encoder enc;
    enc.run(origFile, encFile);

    std::string decFile(testDir.string() + "\\DecodedText.txt");
    lzw::Decoder dec;
    dec.run(encFile, decFile);

    lzw::TextChecker tc(origFile, decFile);
    auto const isSame(tc.checkSame());

    if (isSame) {
        std::cout << "Test Passed" << std::endl;
        testDir.setTestPassed(true);
    } else {
        std::cout << "Test Failed" << std::endl;
        testDir.setTestPassed(false);
        return -1;
    }

    return 0;
}
