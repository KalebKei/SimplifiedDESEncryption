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
#include "des_encrypt_source.cpp"

using namespace std; 

// #define debug


#ifdef debug
void test();
#endif

const char* progname = "";
const char* filename = "";

// Hard set key. Organized into a 16 bit int and only utilizes the last 10 bits (seperated by pipe). Key is as shown in binary:
// 0 0 0 0 0 0 | 1 0 1 0 1 0 1 0 1 0
static u_int16_t key = 0x2AA; 

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
    // else
    // {
    //     cout << "No key provided" << endl;
    //     exit(1);
    // }
#ifdef debug
    test();
#endif

    /* Obtain the Input */

    string input = "";
    if(filename != "")
    {
        input = ReadFile(filename);
        EncryptInput(input);
    }
    else
    {
        while(1) // There is no way of knowing that the input has stopped so ctrl C
        {

            input = getchar();
            EncryptInput(input);
        }
    }

    return 0;
}

#ifdef debug
void test()
{
    // char ch = 'a';
    u_int16_t val = 0x2AA;
    int size = 8;
    cout << int(val) << endl;
    
    int* binary = ToBinaryArr(val, size);
    // u_int16_t new_val = ToInt(binary, size);
    // cout << hex << new_val << dec << endl;

    // LeftShift(new_val, 2, 10);

    int* left;
    int* right;
    SplitArr(binary, left, right, size);
    
    // PermP8(val);


    // for (int i = 0; i < size; i++)
    //     std::cout << binary[i];
    // std::cout << std::endl;
    
    // int* binary = ToBinaryArr(ch, size/2);
    // for (int i = 0; i < size; i++)
    //     std::cout << binary[i];
    // std::cout << std::endl;
}
#endif