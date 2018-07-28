%%%%%%%%%%%%%%%%%%%%
LZW encoder/decoder
%%%%%%%%%%%%%%%%%%%%
- Algorithm details, see for example:
	https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Welch
	https://www.youtube.com/watch?v=j2HSd3HCpDs


The encoder takes a text file as input, encodes it and puts it in another output file. 
The decoder takes the encoded file and decodes it to the original file.
TextCheck takes two input files (through the command line), and checks that they have the same number of characters, and that those characters are the same.  


%%%%%%%%%%%%%%%%%%%%
Version overview:
%%%%%%%%%%%%%%%%%%%%
Version 1: Use vector to store the dictonary and and rely on recursive function to build the dictionary. 
		   Output the encoded/decoded data into files. Have a text checker function to compare that the decoded output is the same as the original text. 
Version 2: 2.0: Use hash table (sets or maps) to store the dictionary, hopefully allowing for faster decoding/encoding.
		   Use a non-recursive function to build the dictionary.


%%%%%%%%%%
Done
%%%%%%%%%%
	1.0: Previous code I wrote earlier (Early Febuary 2018). 
		 Seems to work, but not optimized. Uses vectors to store the dictionary and relies on a recursive function to build the dictionary.
	1.1: Script for checking the difference between two files (e.g. the decoded file and the original - to make sure everything works).
	1.2: Print the output of the encoder to a file. 
	1.3: Print the output of the decoder to a file.

%%%%%%%%%%
TODO: 	
%%%%%%%%%%
	1.9: Add hash tables for dictionary storage for the encoder 
		 Maybe: i. remove recursive call if convenient 
			    ii. Do not call the output file in the function that adds dictionary entries (only for the encoder)
	2.0: Add hash tables for dictionary storage for the decoder 
		 Maybe: remove recursive call if convenient
	2.1: Remove recursive call
	2.2: Do not call the output file in the function that adds dictionary entries (only for the encoder)
	2.3: Look over how the encoder and decoder reads in the input file (different methods currently)


%%%%%%%%%%
Issues
%%%%%%%%%%
- When running the encoder and checking the output against the Ref, TextChecker says they differ by one character. 
  If I go in to the file created by the encoder and press delete at the last line, TextChecker says they're the same. 
  However, the weird thing is that when I press delete, there is actually nothing being deleted (no space or new line at least)
