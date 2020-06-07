# LZW encoder/decoder

CLI tool for encoding and decoding text files, using an LZW algorithm.

The CLI have three modes `encode`, `decode`, and `check`.
* `encode` takes a text file as input, encodes it and puts it in an output file with .ENC extension.
* `decode` takes the encoded file (.ENC) and decodes it to an output file.
* `check` takes two input files, and checks that they have the same number of characters and content.

For `encode` and `decode`, the output file will be automatically named but can be manually specified as an optional input.
The only requirement is that that for `encode`, it has to have an extension .ENC.

For information about the LZW algorithm, see for example:
* https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Welch
* https://www.youtube.com/watch?v=j2HSd3HCpDs

### TODOs

* The algorithm is outdated and should be updated:
    * Clean up the logic of the encoding and decoding.
    * Replace recursive call with an iterative one.
    * Look over how Encoder and Decoder reads in the inFile (different methods currently).
    * Use modern C++ syntax.
    * (Optional) Currently the output is not optimized for compression, it may even be
    larger than the input in most cases. Look into ways this can be addressed.

### Open issues

* The test current fails, the reason seems to be that carriage returns are not handled correctly.
This algorithm was initially made on Linux - now using Windows instead have exposed this issue.
* Old issue (present on the older version when run on Linux, but kept here as it never was investiagted):
When encoding a reference text,
https://archive.org/stream/BarthesRolandCameraLucidaReflectionsOnPhotography/Barthes_Roland_Camera_Lucida_Reflections_on_Photography_djvu.txt,
and checking the decoded output against the original text, the checker reports a difference by one character.
If the file created by the decoder is opened and save is pressed, the checker now reports they're the same.
This issue may be related to the above regarding carriage return, resolve that first and then try to reproduce
this to see if it is still present with the updated coded.
