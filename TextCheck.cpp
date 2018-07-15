#include <iostream>
#include <fstream>


using namespace std;


int main () {

// Read in file 1
  streampos inputSize1;
  char * input1;

  ifstream file ("InputText/OriginalText.txt", ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
    inputSize1 = file.tellg();
    
    input1 = new char [inputSize1];
    file.seekg (0, ios::beg);
    file.read (input1, inputSize1);
    file.close();
  }
  else { 
    cout << "Error: Unable to open input file"; 
    return 0;
  }   

  
// Read in file 2
  streampos inputSize2;
  char * input2;

  ifstream file2 ("InputText/DecodedText.txt", ios::in|ios::binary|ios::ate);
  if (file2.is_open())
  {
    inputSize2 = file2.tellg();
    
    input2 = new char [inputSize2];
    file2.seekg (0, ios::beg);
    file2.read (input2, inputSize2);
    file2.close();
  }
  else { 
    cout << "Error: Unable to open input file"; 
    return 0;
  }     


// Check if the number of characters (i.e. the file sizes) is the same
  if (inputSize1 == inputSize2){
    cout << "Number of characters is the same." << endl;
  }
  else{
    cout << "Number of characters is not the same." << endl;
    cout << "Input 1 has: " << inputSize1 << endl;
    cout << "Input 2 has: " << inputSize2 << endl;
    return 0;
  }


// Check if the characters are the same
  for (int i = 0; i < ((int)inputSize1 + 1); ++i){  
    if (input1[i] != input2[i]){
      cout << "Different character at index: " << i << endl;
      cout << "Input 1 has: " << input1[i] << endl;
      cout << "Input 2 has: " << input2[i] << endl;
      return 0;
    }
  }
  cout << "All characters are the same" << endl;



// Print size and the first and last five chars of the input to the terminal
// Used to troubleshoot in case it is needed
/*
  cout << "--- Text 1 ---" << endl;
  cout << "Text, Size:" << inputSize1 << endl;
  cout << "Text, Beginning:" << endl;  
  cout << input1[0] << input1[1] << input1[2] << input1[3] << input1[4] << endl;
  cout << "Text, End:" << endl;
  cout << input1[(int)inputSize1-4] << input1[(int)inputSize1-3] << input1[(int)inputSize1-2] << input1[(int)inputSize1-1] << input1[(int)inputSize1] << endl;


  cout << "--- Text 2 ---" << endl;
  cout << "Text, Size:" << inputSize2 << endl;
  cout << "Text, Beginning:" << endl;  
  cout << input2[0] << input2[1] << input2[2] << input2[3] << input2[4] << endl;
  cout << "Text, End:" << endl;
  cout << input2[(int)inputSize2-4] << input2[(int)inputSize2-3] << input2[(int)inputSize2-2] << input2[(int)inputSize2-1] << input2[(int)inputSize2] << endl;
*/  
  
  
  
  delete[] input1;
  delete[] input2;
  
  return 0;
}
