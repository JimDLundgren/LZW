#include "Encoder.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

void addToDictionary(std::map<std::string, int>& wordMap, std::string str, char* ptr,
                     int& counter, int& mapCounter, std::ofstream& outputFile)
{
  if (wordMap.find(str) != wordMap.end()) {
    // If str is in the dictionary, increase the pointer before dereferencing
    // it, adding the next input character to str.
    str += *(++ptr);

    // Increase counter - if we add enough characters to str we want to skip
    // the corresponding next few characters in the input text, i.e. skip a
    // few iterations in the for-loop Decoder::run.
    counter++;

    // If we reach the end of the string, and haven't found a new dictonary entry,
    // output the final part. Note: Not sure if strings actually terminate with \0, see:
    // https://stackoverflow.com/questions/10943033/why-are-strings-in-c-usually-terminated-with-0
    if (*ptr == '\0') {
      str.pop_back();

      if (wordMap.find(str) == wordMap.end()){
        throw std::runtime_error("Word that should be in dictionary not found");
      }

      outputFile << wordMap[str] << " ";
      return;
    }
    // Recursively check the new string to see if it is in the dictionary.
    addToDictionary(wordMap, str, ptr, counter, mapCounter, outputFile);
  }
  else {
    // if str is not in the dictionary, add it.
    wordMap[str] = mapCounter++;

    // Remove last element of str, this will be our decoded part.
    str.pop_back();

    // Find the position of str, i.e. its decode message.
    if (wordMap.find(str) == wordMap.end()){
      throw std::runtime_error("Word that should be in dictionary not found");
    }
    outputFile << wordMap[str] << " ";
  }

}

} // namespace

namespace lzw {

int Encoder::run(std::string inFile, std::string outFile) {
  fs::path inFilePath(inFile);
  fs::path outFilePath(outFile);

  if (inFilePath.extension() == ".ENC") {
    throw std::runtime_error(std::string("File: ") + inFilePath.string()
                             + " is already encoded (has extension .ENC)");
  }

  if(!(outFile.empty() || (outFile == ""))) {
    if (outFilePath.extension() != ".ENC") {
      throw std::runtime_error(std::string("Output file needs .ENC extension, but was: ")
                              + outFilePath.string());
    }
  }

  std::ifstream inFileIfs (inFilePath, std::ios::in | std::ios::binary
                                                    | std::ios::ate);
  if (!inFileIfs.is_open()) {
    throw std::runtime_error(("Unable to open inFile: " + inFilePath.string()));
  }

  std::streampos inputSize = inFileIfs.tellg();
  auto size = static_cast<int>(inputSize);

  auto input = std::make_unique<char[]>(inputSize);
  inFileIfs.seekg(0, std::ios::beg);
  inFileIfs.read(input.get(), inputSize);
  inFileIfs.close();

  // Create the starting dictionary.
  std::map<std::string, int> dictionaryOfWords;
  int dictionaryCount = 0;

  for(int i = 0; i < 256; i++){
    char temp_c = i;
    std::string temp(1, temp_c);
    dictionaryOfWords[temp] = dictionaryCount++;
  }

  if(outFile.empty() || (outFile == "")) {
    // The output file is a .ENC file with the same name as the input file.
    outFilePath = createOutFilePathBasedOnInFile(inFilePath, ".ENC");
  } else {
    outFilePath = outFile;
  }

  std::ofstream outFileOfs(outFilePath);
  if (!outFileOfs.is_open()) {
    throw std::runtime_error(("Unable to open outFile: " + outFilePath.string()));
  }

  std::cout << "Encoding file: " << inFilePath
            << " to file: " << outFilePath << std::endl;

  for(int i = 0; i < size; i++){
    // comp_str holds the current character to check if it's in dictionary.
    std::string comp_str;
    // p_input is a pointer to the current input, used in the process to add
    // more characters to the input string in addToDictionary.
    char* p_input;

    p_input = &input[i];
    comp_str = *p_input;

    // To follow the LZW algorithm, we need to skip iterations in case we add
    // a string of three or more characters. Hence, i_add set to -1 here
    // (-1 to compensate for the two first iterations).
    int i_add = -1;
    addToDictionary(dictionaryOfWords, comp_str, p_input, i_add, dictionaryCount, outFileOfs);

    // Skip iteration in case we add a string with three or more characters.
    if (i_add > 0){
      i = i + i_add;
    }
  }

  return 0;
}

} // lzw
