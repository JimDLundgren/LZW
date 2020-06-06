all: Encoder main

Encoder: src/Encoder.cpp
	cl /EHsc src/Encoder.cpp

main: src/main.cpp
	cl /EHsc src/main.cpp src/Decoder.cpp src/TextChecker.cpp src/ReadFile.cpp

clean:
	del Encoder.exe main.exe \
	Encoder.obj main.obj
