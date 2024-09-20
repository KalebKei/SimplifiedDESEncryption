.PHONY = all clean

all: des_encrypt clean

des_encrypt: des_encrypt.cpp encrypt.o
	g++ -o des_encrypt des_encrypt.cpp source

encrypt.o: encrypt.cpp encrypt.h
	g++ -o source -c encrypt.cpp

clean:
	rm source