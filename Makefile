all: Encoder main

Encoder: src/Encoder.cpp
	cl /EHsc src/Encoder.cpp

main: src/main.cpp
	cl /EHsc /std:c++17 src/main.cpp src/BaseCoder.cpp src/Decoder.cpp src/TextChecker.cpp

clean:
	del Encoder.exe main.exe \
	Encoder.obj main.obj BaseCoder.obj Decoder.obj TextChecker.obj
