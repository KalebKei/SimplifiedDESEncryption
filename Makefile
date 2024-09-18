.PHONY = all clean

all: des_encrypt clean

des_encrypt: des_encrypt.cpp des_encrypt_source.o
	g++ -o des_encrypt des_encrypt.cpp

des_encrypt_source.o: des_encrypt_source.cpp
	g++ -o source -c des_encrypt_source.cpp

clean:
	rm source