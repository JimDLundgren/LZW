%%%%%%%%%%%%%%%%%%%%
LZW encoder/decoder
%%%%%%%%%%%%%%%%%%%%

- Algorithm details, see for example:
	https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Welch
	https://www.youtube.com/watch?v=j2HSd3HCpDs


The encoder takes a text file as input, encodes it and puts it in another output file. 
The decoder takes the encoded file and decodes it to the original file.
TextCheck takes two input files (through the command line), and checks that they have the same number of characters, and that those characters are the same.  

Test text (served as a reference for runtime tests) is a .txt copy of:
https://archive.org/stream/BarthesRolandCameraLucidaReflectionsOnPhotography/Barthes_Roland_Camera_Lucida_Reflections_on_Photography_djvu.txt


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
		 Runtime: encoder ~ 30 sec, decoder ~ 20 sec
	1.9: Use hash tables for dictionary storage for the encoder.
		 The key is the word and the value is the corresponding number. 
		 Runtime: encoder ~ 0.3 sec (One order of magnitude improvement compared to earlier)
	2.0: Use hash tables for dictionary storage for the decoder. 
		 Using two hash tables, one where the key is the word and the value is the number. 
		 Another where the key is the number and the value is the word. 
		 This is because as I have written the code now, I need to look up both at different occasions.
		 This might be someting to improve in the future - only use one hash table. 
		 Note also: It is important that to use .at() and not the operator[] when checking for elements, as the latter does not throw an out of range exception
		 in case an element is not found - instead it adds an empty element. 
		 Runtime: decoder ~ 0.3 sec (One order of magnitude improvement compared to earlier)


%%%%%%%%%%
TODO: 	
%%%%%%%%%%

	2.1: Remove recursive call.
	2.2: Do not call the output file in the function that adds dictionary entries (only for the encoder).
	2.3: Look over how the encoder and decoder reads in the input file (different methods currently).


%%%%%%%%%%
Issues
%%%%%%%%%%

- When running the encoder and checking the output against the Ref, TextChecker says they differ by one character. 
  If I go in to the file created by the encoder and press delete at the last line, TextCheck says they're the same. 
  However, the weird thing is that when I press delete, there is actually nothing being deleted (no space or new line at least).
  I just found out that it is enough that I open the file and press save, without changing anything - and TextCheck says they are the same, 
  while before saving it TextCheck said they were of different lengths. 
  No change when going from vector to map, the issue might be how I store the last element?
