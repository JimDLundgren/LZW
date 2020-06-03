all: DecoderLZW EncoderLZW main

DecoderLZW: src/DecoderLZW.cpp
	cl /EHsc src/DecoderLZW.cpp

EncoderLZW: src/EncoderLZW.cpp
	cl /EHsc src/EncoderLZW.cpp

main: src/main.cpp
	cl /EHsc src/main.cpp src/TextChecker.cpp src/ReadFile.cpp

clean:
	del DecoderLZW.exe EncoderLZW.exe main.exe \
	DecoderLZW.obj EncoderLZW.obj main.obj
