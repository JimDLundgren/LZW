#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;


// Function addToDictionary adds a new dictionary input, based on the encoded input   
void addToDictionary (map<string, int> & wordMap, string str, int* ptr, int* ptr_stop, int & mapCounter, map<int, string> & indexMap){        

// checks if str is in the dictionary
  // If str is in the dictionary:   
  if (wordMap.find(str) != wordMap.end()) {      

    // Check if we are considering the last element of the coded input, 
    // if so, do no proceed further, i.e. return
    if (ptr == ptr_stop) {  
      return;
    }
    
    // We consider the next code in the input list
    ptr++;    
    string temp_str;
    
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
  // If str is not in the dictionary, add str to the dictionary
  else {  
    wordMap[str] = mapCounter;
    indexMap[mapCounter++] = str;            
  } 
  
}



int main () {

  // Read in text to decode
  string fileName = "InputText/EncodedText.txt";

  int data;
  vector<int> toDecode;
  
  ifstream inputFile( fileName.c_str() );
  if ( inputFile.is_open() ) {
       while (inputFile >> data) {
           toDecode.push_back(data);
       }
    inputFile.close();
  }
  else { 
    cout << "Error: Unable to open input file" << endl; 
    return 0; 
  }


  
  // pointer to the last code, used to stop the function AddToDictionary
  int* p_lastInput = &toDecode.at(toDecode.size()-1); 
  
  
  
  // Create the starting dictionary
  // dictionaryOfWords contains the word as a key, the number as a value
  // dictionaryOfIndex contains the number as a key, the word as a value
  map<string, int> dictionaryOfWords;
  map<int, string> dictionaryOfIndex;
  int dictionaryCount = 0;

  for(int i = 0; i < 256; i++){ 
    char temp_c = i;
    string temp(1, temp_c);
    dictionaryOfWords[temp] = dictionaryCount;
    dictionaryOfIndex[dictionaryCount++] = temp;
  }


  
  // Open output file
  ofstream OutputFile ("InputText/DecodedText.txt");
  if (OutputFile.is_open()) {
    // Loop over the code words, and add a dictionary input for each according to
    // the LZW rules
    for(int i = 0; i < toDecode.size(); i++){        
      int* p_input;
      string comp_str;
      
      p_input = &toDecode.at(i);

      try{
        comp_str = dictionaryOfIndex.at((*p_input));
      }
      catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
      }
                    
      // comp_str holds the decode
      // p_input points to the current code word, passed to addToDictionary to be
      // able to check the next coming codes in the function
      
      // Add a new dictionary entry, constructed from the code word;
      addToDictionary(dictionaryOfWords, comp_str, p_input, p_lastInput, dictionaryCount, dictionaryOfIndex); 
      
      // print the decoded message
      //cout << comp_str;
      OutputFile << comp_str; 
    }
    
    OutputFile.close();
    
  }
  else { 
    cout << "Error: Unable to open output file" << endl; 
    return 0;
  } 



  // Uncomment to print dictionary 
  /*
  cout << endl << "Dictionary: " << endl << endl;
  for(int i = 0; i < 256; i++){ 
    char temp_c = i;
    string temp(1, temp_c);
    cout << dictionaryOfWords.find(temp)->first << " ";
  }
  cout << endl;
  */



  cout << endl;
  return 0;  
}