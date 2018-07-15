all: DecoderLZW.ex EncoderLZW.ex TextCheck.ex


DecoderLZW.ex: DecoderLZW.cpp
	g++ -std=c++11 DecoderLZW.cpp -o DecoderLZW.ex 

EncoderLZW.ex: EncoderLZW.cpp
	g++ -std=c++11 EncoderLZW.cpp -o EncoderLZW.ex 

TextCheck.ex: TextCheck.cpp
		g++ -std=c++11 TextCheck.cpp -o TextCheck.ex 


clean:
	rm -v DecoderLZW.ex EncoderLZW.ex TextCheck.ex 
