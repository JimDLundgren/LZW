all: lzw tests

lzw: src/lzw.cpp
	cl /EHsc /std:c++17 src/lzw.cpp src/BaseCoder.cpp src/Decoder.cpp src/Encoder.cpp src/TextChecker.cpp \
	&& make clean

tests: test/test.cpp
	cl /EHsc /I src /std:c++17 test/test.cpp src/BaseCoder.cpp src/Decoder.cpp src/Encoder.cpp src/TextChecker.cpp \
	&& make cleanTest

clean:
	del lzw.obj BaseCoder.obj Decoder.obj Encoder.obj TextChecker.obj

cleanTest:
	del test.obj BaseCoder.obj Decoder.obj Encoder.obj TextChecker.obj
