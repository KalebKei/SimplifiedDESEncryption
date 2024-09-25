/**
 * @file des_encrypt.cpp
 * @author Kaleb Keichel (kk471921@ohio.edu)
 * @brief Implements Simplified DES encryption security algorithm
 * @version 0.1
 * @date 2024-09-20
 * 
 */
#include <iostream>
#include <string>
#include <cstdint>
#include "encrypt.h"

using namespace std; 

const char* progname = "";
const char* filename = "";

// Hard set key. Organized into a 16 bit int and only utilizes the last 10 bits (seperated by pipe).
static u_int16_t key; 

int main(int argc, char *argv[])
{
    progname = argv[0];
    if(argc == 2)
    {
        key = ReadKey(argv[1]);
    }   
    else if(argc == 3)
    {
        key = ReadKey(argv[1]);
        filename = argv[2];
    }
    else
    {
        cout << "No key provided" << endl;
        exit(1);
    }

    /* Obtain the Input */

    string input;
    if(filename != "")
    {
        input = ReadFile(filename);
        for(int i = 0; i < input.size(); i++)
            EncryptByte(input[i], key);
    }
    else
    {
        while(1) // There is no way of knowing that the input has stopped so ctrl C
        {
            input = getchar();
            if (!input.empty() && input[0] != -1) {
                EncryptByte(static_cast<unsigned char>(input[0]), key);
            }
        }
    }

    return 0;
}