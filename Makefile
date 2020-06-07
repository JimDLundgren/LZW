all: main

main: src/main.cpp
	cl /EHsc /std:c++17 src/main.cpp src/BaseCoder.cpp src/Decoder.cpp src/Encoder.cpp src/TextChecker.cpp

clean:
	del main.exe main.obj BaseCoder.obj Decoder.obj Encoder.obj TextChecker.obj
