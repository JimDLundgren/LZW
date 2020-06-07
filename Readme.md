# LZW encoder/decoder

CLI tool for encoding and decoding text files, using an LZW algorithm.

The CLI have three modes `encode`, `decode`, and `check`.
* `encode` takes a text file as input, encodes it and puts it in an output file with .ENC extension.
* `decode` takes the encoded file (.ENC) and decodes it to an output file.
* `check` takes two input files, and checks that they have the same number of characters and content.

For `encode` and `decode`, the output file will be automatically named but can be manually specified as an optional input.
The only requirement is that that for `encode`, it has to have an extension .ENC.

Example:
> \> lzw encode path\to\inFile.txt optional\path\to\outFile.ENC

For information about the LZW algorithm, see for example:
* https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Welch
* https://www.youtube.com/watch?v=j2HSd3HCpDs

### Installation

To run the make file, install the Visual Studio C++ command-line toolset. See e.g.:
https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=vs-2019

You can use `make` on Windows, by installing it through a package manager, such as Chocolatey:
https://chocolatey.org/

The `make` commands are restricted to Windows.
For other platforms, the souce code would have to be compiled manually.
