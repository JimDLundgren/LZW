all: main

main: src/main.cpp
	cl /EHsc /std:c++17 src/main.cpp src/BaseCoder.cpp src/Decoder.cpp src/Encoder.cpp src/TextChecker.cpp

test: test/test.cpp
	cl /EHsc /I src /std:c++17 test\test.cpp src\BaseCoder.cpp src\Decoder.cpp src\Encoder.cpp src\TextChecker.cpp

clean:
	del main.exe main.obj BaseCoder.obj Decoder.obj Encoder.obj TextChecker.obj

cleanTest:
	del test.exe test.obj BaseCoder.obj Decoder.obj Encoder.obj TextChecker.obj
