all: lzw

lzw: src/lzw.cpp
	cl /EHsc /std:c++17 src/lzw.cpp src/BaseCoder.cpp src/Decoder.cpp src/Encoder.cpp src/TextChecker.cpp

test: test/test.cpp
	cl /EHsc /I src /std:c++17 test\test.cpp src\BaseCoder.cpp src\Decoder.cpp src\Encoder.cpp src\TextChecker.cpp

clean:
	del lzw.exe lzw.obj BaseCoder.obj Decoder.obj Encoder.obj TextChecker.obj

cleanTest:
	del test.exe test.obj BaseCoder.obj Decoder.obj Encoder.obj TextChecker.obj
