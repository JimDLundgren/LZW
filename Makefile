all: DecoderLZW EncoderLZW TextCheck

DecoderLZW: src/DecoderLZW.cpp
	cl /EHsc src/DecoderLZW.cpp

EncoderLZW: src/EncoderLZW.cpp
	cl /EHsc src/EncoderLZW.cpp

TextCheck: src/TextCheck.cpp
	cl /EHsc src/TextCheck.cpp

clean:
	del DecoderLZW.exe EncoderLZW.exe TextCheck.exe \
    DecoderLZW.obj EncoderLZW.obj TextCheck.obj
