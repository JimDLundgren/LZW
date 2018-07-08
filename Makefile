all: LZW_Decoder.ex LZW_Encoder.ex


LZW_Decoder.ex: LZW_Decoder.cpp
	g++ -std=c++11 LZW_Decoder.cpp -o LZW_Decoder.ex 

LZW_Encoder.ex: LZW_Encoder.cpp
	g++ -std=c++11 LZW_Encoder.cpp -o LZW_Encoder.ex 



clean:
	rm -v LZW_Decoder.ex LZW_Encoder.ex 
