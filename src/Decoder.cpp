#include "Decoder.hpp"

#include <algorithm>
#include <chrono>
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

// Function addToDictionary adds a new dictionary input, based on the encoded input
void addToDictionary(std::map<std::string, int>& wordMap, std::string str, int* ptr,
                     int* ptr_stop, int& mapCounter, std::map<int, std::string>& indexMap){
  // checks if str is in the dictionary
  if (wordMap.find(str) != wordMap.end()) {
    // If str is in the dictionary:
    // Check if we are considering the last element of the coded input,
    // if so, do no proceed further, i.e. return
    if (ptr == ptr_stop) {
      return;
    }

    // We consider the next code in the input list
    ptr++;
    std::string temp_str;

    // If the next code is not in the dictionary, it is of the form str + str[0]
    // hence add that to the dictionary
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
    // If not, add str + temp_str[0] to the dictionary.
    // If it is, keep extending str + temp_str[0] with temp_str[1] , check if
    // it is in the dictionary and so on.
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
    // If str is not in the dictionary, add str to the dictionary
    wordMap[str] = mapCounter;
    indexMap[mapCounter++] = str;
  }
}

} // namespace

namespace lzw {

int Decoder::run(std::string inFile)
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

  // pointer to the last code, used to stop the function AddToDictionary
  int* p_lastInput = &toDecode.at(toDecode.size()-1);

  // Create the starting dictionary
  // dictionaryOfWords contains the word as a key, the number as a value
  // dictionaryOfIndex contains the number as a key, the word as a value
  std::map<std::string, int> dictionaryOfWords;
  std::map<int, std::string> dictionaryOfIndex;
  int dictionaryCount = 0;

  for(int i = 0; i < 256; i++){
    char temp_c = i;
    std::string temp(1, temp_c);
    dictionaryOfWords[temp] = dictionaryCount;
    dictionaryOfIndex[dictionaryCount++] = temp;
  }

  // The output file is a .txt file with the same name as the input
  // file. If it already exists, append the current time (since epoch)
  // to its name.
  fs::path outFilePath = inFilePath.parent_path();
  outFilePath /= inFilePath.stem();
  outFilePath += ".txt";
  if (fs::exists(outFilePath)) {
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()
    );
    auto count = ms.count();
    outFilePath = inFilePath.parent_path();
    outFilePath /= inFilePath.stem();
    outFilePath += ("_" + std::to_string(count));
    outFilePath += ".txt";
  }

  std::ofstream outFileOfs(outFilePath);
  if (!outFileOfs.is_open()) {
    throw std::runtime_error(("Unable to open outFile: " + inFilePath.string()));
  }

  std::cout << "Decoding file: " << inFilePath
            << " to file: " << outFilePath << std::endl;

  // Loop over the code words, and add a dictionary input for each
  // according to the LZW rules
  for(int i = 0; i < toDecode.size(); i++){
    // comp_str holds the decode
    // p_input points to the current code word, passed to addToDictionary to be
    // able to check the next coming codes in the function
    int* p_input;
    std::string comp_str;

    p_input = &toDecode.at(i);

    try{
      comp_str = dictionaryOfIndex.at((*p_input));
    }
    catch (const std::out_of_range& oor) {
      std::cerr << "Out of Range error: " << oor.what() << '\n';
    }

    // Add a new dictionary entry, constructed from the code word;
    addToDictionary(dictionaryOfWords, comp_str, p_input,
                    p_lastInput, dictionaryCount, dictionaryOfIndex);

    outFileOfs << comp_str;
  }

  return 0;
}

} // lzw
