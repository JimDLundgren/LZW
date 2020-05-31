# LZW encoder/decoder

CLI tool for encoding and decoding text files, using the LZW algorithm.

The encoder takes a text file as input, encodes it and puts it in another output file. 
The decoder takes the encoded file and decodes it to the original file.
`TextCheck` takes two input files (through the command line), and checks that they have 
the same number of characters, and that those characters are the same.  

For information about the LZW algorithm, see for example:
* https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Welch
* https://www.youtube.com/watch?v=j2HSd3HCpDs

### TODOs

* Remove recursive call.
* Do not call the output file in the function that adds dictionary entries (only for the encoder).
* Look over how the encoder and decoder reads in the input file (different methods currently).

### Open issues

* When running the encoder on a reference text,
https://archive.org/stream/BarthesRolandCameraLucidaReflectionsOnPhotography/Barthes_Roland_Camera_Lucida_Reflections_on_Photography_djvu.txt,
and checking the output against the original text, `TextCheck` reports a difference by one character. 
If I open the file created by the encoder and press delete at the last line, `TextCheck` now reports they're the same. 
Note, when I press delete there is actually nothing being deleted (no space or new line at least).
It is enough that I open the file and press save, without changing anything, and `TextCheck` reports they are the same. 
Potentially could be an added carriage return or something similar?
