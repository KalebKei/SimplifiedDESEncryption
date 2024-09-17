.PHONY = all

all: des_encrypt

des_encrypt: des_encrypt.cpp
	g++ -o des_encrypt des_encrypt.cpp

