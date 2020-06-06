all: Decoder Encoder main

Decoder: src/Decoder.cpp
	cl /EHsc src/Decoder.cpp

Encoder: src/Encoder.cpp
	cl /EHsc src/Encoder.cpp

main: src/main.cpp
	cl /EHsc src/main.cpp src/TextChecker.cpp src/ReadFile.cpp

clean:
	del Decoder.exe Encoder.exe main.exe \
	Decoder.obj Encoder.obj main.obj
