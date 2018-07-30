#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;


// Function addToDictionary adds a new dictionary input, based on the text input    
void addToDictionary (map<string, int> & wordMap, string str, char* ptr, int & counter, int & mapCounter, ofstream & outputFile){   
  
// Check if str is in the dictionary:
  // If str is in the dictionary:   
  if (wordMap.find(str) != wordMap.end()) {    

    // Increase the pointer before dereferencing it, adding the next input character to str
    str += *(++ptr);  
    // Add one to counter, if we add enough characters to str we want to skip the corresponding next few characters in the input text 
    // i.e. skip a few iterations in the for-loop in main
    counter++;  
    
    // If we reach the end of the string, and haven't found a new dictonary entry, output the final part
    // Note: Not sure if strings actually terminate with \0, see:
    // https://stackoverflow.com/questions/10943033/why-are-strings-in-c-usually-terminated-with-0
    if (*ptr == '\0') { 
      str.pop_back();

      if ( wordMap.find(str) == wordMap.end() ){
        cout << "Error: Word that should be in dictionary not found" << endl;
        return;
      }

      // Output the decoded part
      //cout << pos << " "; 
      outputFile << wordMap[str] << " ";
      return; 
    }
    // Check the new string to see if it is in the dictionary, recursively 
    addToDictionary(wordMap, str, ptr, counter, mapCounter, outputFile); 
  }
  else { 
    // if str is not in the dictionary, add it
    wordMap[str] = mapCounter++;
    
    // Remove last element of str, this will be our decoded part (according to the LZW algorithm)
    str.pop_back(); 

    // Find the position of str, i.e. its decode message
    if ( wordMap.find(str) == wordMap.end() ){
      cout << "Error: Word that should be in dictionary not found" << endl;
      return;
    }        
    // Output the decoded part
    //cout << pos << " ";
    outputFile << wordMap[str] << " ";    
  } 
  
}



int main () {

  // Read in text to encode 
  streampos inputSize;
  char * input;
  int size;

  ifstream inputFile ("InputText/OriginalText.txt", ios::in|ios::binary|ios::ate);
  if (inputFile.is_open()) {
    inputSize = inputFile.tellg();
    size = int(inputSize);
    
    input = new char [inputSize];
    inputFile.seekg (0, ios::beg);
    inputFile.read (input, inputSize);
    inputFile.close();

  }
  else { 
    cout << "Error: Unable to open input file" << endl; 
    return 0;
  } 
  



  // Create the starting dictionary
  map<string, int> dictionaryOfWords;
  int dictionaryCount = 0;

  for(int i = 0; i < 256; i++){ 
    char temp_c = i;
    string temp(1, temp_c);
    dictionaryOfWords[temp] = dictionaryCount++;
  }



  // Open output file
  ofstream OutputFile ("InputText/EncodedText.txt");
  if (OutputFile.is_open()) {

    for(int i = 0; i < size; i++){        
      string comp_str;
      char* p_input;

      p_input = &input[i]; 
      comp_str = *p_input; 
      
      // comp_str holds the current character to check if it's in dictionary
      // p_input is a pointer to the current input, used in the process to add more characters to the input string in addToDictionary()
          
      // To follow the LZW algorithm we want to skip iterations in case we add a string of three or more characters. 
      // hence, i_add set to -1 here (-1 to compensate for the two first iterations)    
      int i_add = -1; 
      addToDictionary(dictionaryOfWords, comp_str, p_input, i_add, dictionaryCount, OutputFile);
    
      // Skip iteration in case we add a string with three or more characters
      if (i_add > 0){
        i = i + i_add;
      }
    
    }
  
  OutputFile.close();
  
  }
  else { 
    cout << "Error: Unable to open output file" << endl; 
    return 0;
  } 

  // delete input to free some memeory
  delete[] input; 



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