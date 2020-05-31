all: DecoderLZW EncoderLZW TextCheck

DecoderLZW: DecoderLZW.cpp
	cl /EHsc DecoderLZW.cpp

EncoderLZW: EncoderLZW.cpp
	cl /EHsc EncoderLZW.cpp

TextCheck: TextCheck.cpp
	cl /EHsc TextCheck.cpp

clean:
	del DecoderLZW.exe EncoderLZW.exe TextCheck.exe \
    DecoderLZW.obj EncoderLZW.obj TextCheck.obj
