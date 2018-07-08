#include <iostream>
#include<vector>
#include <string>
#include <algorithm>
//#include <cmath>
//#include <cstdio>
//#include <stdio.h>
#include <sstream>
#include <fstream>

using namespace std;


// Function inOrOut adds a new dictionary input, based on the text input   
void inOrOut (vector<string> & vec, string str, char* ptr, int& counter){   
  
  // checks if str is in the dictionary
  std::vector<string>::iterator it;
  it = find (vec.begin(), vec.end(), str);  
  
  // If str is in the dictionary:   
  if (it != vec.end()) {  

    // Increase the pointer before dereferencing it, adding the next input character to str
    str += *(++ptr);  
    // Add one to counter, if we add enough characters to str we want to skip the corresponding next few characters in the input text 
    // i.e. skip a few iterations in the for-loop in main
    counter++;  
    
    // Not sure if strings actually terminate with \0, see:
    // https://stackoverflow.com/questions/10943033/why-are-strings-in-c-usually-terminated-with-0
    
    // If we reach the end of the string, and haven't found a new dictonary entry, output the final part
    // NOTE: Not sure if strings actually terminate with \0, see:
    if (*ptr == '\0') { 
      str.pop_back();
      ptrdiff_t pos = distance(vec.begin(), find(vec.begin(), vec.end(), str));
      if(pos >= vec.size()) {
        cout << "Error: Word that should be in dictionary not found" << endl;
        return;
      }      

      // Output the decoded part
      cout << pos << " "; 
      return; 
    }
    // Check the new string to see if it is in the dictionary, recursively 
    inOrOut(vec, str, ptr,counter); 
  }
  else { 
    // if str is not in the dictionary, add it
    vec.push_back(str); 
    
    // Remove last element of str, this will be our decoded part (according to the LZW algorithm)
    str.pop_back(); 

    // Find the position of str, i.e. its decode, and print it
    ptrdiff_t pos = distance(vec.begin(), find(vec.begin(), vec.end(), str));
    if(pos >= vec.size()) {
      cout << "Error: Word that should be in dictionary not found" << endl;
      return;
    }
    cout << pos << " ";
  } 
  
}



int main () {

  // Read in text to encode 
  streampos inputSize;
  char * input;
  int size;

  ifstream file ("InputText_1/OriginalText.txt", ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
    inputSize = file.tellg();
    size = int(inputSize);
    
    input = new char [inputSize];
    file.seekg (0, ios::beg);
    file.read (input, inputSize);
    file.close();

  }
  else { 
    cout << "Unable to open file"; 
    return 0;
  } 
  



  // Create the starting dictionary
  vector<string> dictionaryOfWords;

  for(int i = 0; i < 256; i++){ 
    char temp_c = i;
    string temp(1, temp_c);
    dictionaryOfWords.push_back(temp);
  }


  for(int i = 0; i < size; i++){        
    string comp_str;
    char* p_input;

    p_input = &input[i]; 
    comp_str = *p_input; 
    
    // comp_str holds the current character to check if it's in dictionary
    // p_input is a pointer to the current input, used in the process to add more characters to the input string in inOrOut()
        
    // To follow the LZW algorithm we want to skip iterations in case we add a string of three or more characters. 
    // hence, i_add set to -1 here (-1 to compensate for the two first iterations)    
    int i_add = -1; 
    inOrOut(dictionaryOfWords,comp_str,p_input,i_add);
  
    // Skip iteration in case we add a string with three or more characters
    if (i_add > 0){
      i = i + i_add;
    }
  
  }


  // delete input to free some memeory
  delete[] input; 


  // Uncomment to print dictionary
  /*
  cout << endl << "Dictionary: " << endl << endl;
  for(auto& str : dictionaryOfWords){ cout << str << " "; }
  cout << endl;
  */

  cout << endl;
  return 0;  
}