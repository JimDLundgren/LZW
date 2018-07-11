all: DecoderLZW.ex EncoderLZW.ex


DecoderLZW.ex: DecoderLZW.cpp
	g++ -std=c++11 DecoderLZW.cpp -o DecoderLZW.ex 

EncoderLZW.ex: EncoderLZW.cpp
	g++ -std=c++11 EncoderLZW.cpp -o EncoderLZW.ex 



clean:
	rm -v DecoderLZW.ex EncoderLZW.ex 
