#include "Decoder.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

void addToDictionary(std::map<std::string, int>& wordMap, std::string str, int* ptr,
                     int* ptr_stop, int& mapCounter, std::map<int, std::string>& indexMap)
{
  if (wordMap.find(str) != wordMap.end()) {
    // If str is in the dictionary, check if we are considering the last element
    // of the coded input, if so we're done.
    if (ptr == ptr_stop) {
      return;
    }

    // Consider the next code in the input list.
    ptr++;
    std::string temp_str;

    // If the code is not in the dictionary, it is of the form str + str[0],
    // hence add it to the dictionary.
    try{
      temp_str = indexMap.at((*ptr));
    }
    catch (const std::out_of_range& oor) {
      str += str[0];
      wordMap[str] = mapCounter;
      indexMap[mapCounter++] = str;
      return;
    }

    // In case the next code is in the dictionary, check if str added with the
    // first character of the next code, temp_str[0] is in the dictionary.
    // If not, add str + temp_str[0] to the dictionary. If it is, keep
    // extending str + temp_str[0] with temp_str[1] , check if it is in the
    // dictionary and so on.
    for(int i = 0; i < temp_str.size(); i++){
      str += temp_str[i];

      if ( wordMap.find(str) == wordMap.end() ){
        wordMap[str] = mapCounter;
        indexMap[mapCounter++] = str;
        return;
      }
    }

    addToDictionary (wordMap, str, ptr, ptr_stop, mapCounter, indexMap);
  }
  else {
    // If str is not in the dictionary, add it to the dictionary.
    wordMap[str] = mapCounter;
    indexMap[mapCounter++] = str;
  }
}

} // namespace

namespace lzw {

int Decoder::run(std::string inFile, std::string outFile)
{
  fs::path inFilePath(inFile);

  if (inFilePath.extension() != ".ENC") {
    throw std::runtime_error((std::string("Incorrect file type. ")
            + "Need .ENC extension, but was: " + inFilePath.string()));
  }

  int data;
  std::vector<int> toDecode;

  std::ifstream inFileIfs(inFilePath);
  if (!inFileIfs.is_open()) {
    throw std::runtime_error(("Unable to open inFile: " + inFilePath.string()));
  }

  while (inFileIfs >> data) {
    toDecode.push_back(data);
  }
  inFileIfs.close();

  fs::path outFilePath;
  if(outFile.empty() || (outFile == "")) {
    // The output file is a .txt file with the same name as the input file.
    outFilePath = createOutFilePathBasedOnInFile(inFilePath, ".txt");
  } else {
    outFilePath = outFile;
  }

  std::ofstream outFileOfs(outFilePath);
  if (!outFileOfs.is_open()) {
    throw std::runtime_error(("Unable to open outFile: " + outFilePath.string()));
  }

  std::cout << "Decoding file: " << inFilePath
            << " to file: " << outFilePath << std::endl;

  // pointer to the last code, used to stop addToDictionary.
  int* p_lastInput = &toDecode.at(toDecode.size()-1);

  // Create the starting dictionary. We need two copies for the current
  // way we do the algorithm:
  // - dictionaryOfWords contains the words as keys, the numbers as values.
  // - dictionaryOfIndex contains the numbers as keys, the word as values.
  std::map<std::string, int> dictionaryOfWords;
  std::map<int, std::string> dictionaryOfIndex;
  int dictionaryCount = 0;

  for(int i = 0; i < 256; i++){
    char temp_c = i;
    std::string temp(1, temp_c);
    dictionaryOfWords[temp] = dictionaryCount;
    dictionaryOfIndex[dictionaryCount++] = temp;
  }

  // Loop over the code words, and add to the dictionary
  // according to the LZW rules.
  for(int i = 0; i < toDecode.size(); i++){
    // p_input points to the current code word, passed to addToDictionary to be
    // able to check the next coming codes in the function.
    int* p_input;
    std::string comp_str; // comp_str holds the decoded code (i.e. the word).

    p_input = &toDecode.at(i);

    try{
      comp_str = dictionaryOfIndex.at((*p_input));
    }
    catch (const std::out_of_range& oor) {
      std::cerr << "Out of Range error: " << oor.what() << '\n';
    }

    addToDictionary(dictionaryOfWords, comp_str, p_input,
                    p_lastInput, dictionaryCount, dictionaryOfIndex);

    outFileOfs << comp_str;
  }

  return 0;
}

} // lzw
