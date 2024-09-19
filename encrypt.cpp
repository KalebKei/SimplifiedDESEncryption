#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cmath>
#include "encrypt.h"



/********* Functions *********/


/*** Input Related ***/


u_int16_t ReadKey(const char* hexInput)
{
    u_int16_t key = 0x0;

    // This is just the string version of the char array. Ease of use with built in string functions
    std::string strHex = hexInput;

    key = stoi(strHex, 0, 16); // Starting at index 0. 16 is the base (hex)
    
    return key;
}


/**
 * @brief Reads in all of the contents of a file and places it into a std::string
 * 
 * @param file Filename of the file to read in
 * @return std::string The input of the file
 */
std::string ReadFile(const char* file)
{
    std::string input = "";

    std::ifstream inStream;

    // Open the file and fail if it doesn't exist
    inStream.open(file);
    if(inStream.fail())
    {
        perror(file);
        exit(1);
    }

    // Read in each line and keep the newlines
    std::string currLine = "";
    while(std::getline(inStream, currLine))
    {
        input += currLine;
        input += '\n';
    }
    

    return input;
}


void EncryptByte(char input, u_int16_t key)
{
    // TODO
    /* Permutate input */
    input = PermIP(input);

    std::cout << "After IP permutation: " << int(input) << std::endl;


    /* Generate Key 1 */

    // The binary representation of the 10 bit key
    int* binaryKey = ToBinaryArr(key, 10);

    std::cout << "Binary representation of key: ";
    for(int i = 0; i < 10; i++)
        std::cout << binaryKey[i];
    std::cout << std::endl;


    // The left half of the binary key
    int left[5];
    // The right half of the binary key
    int right[5];

    std::cout << "Splitting binary key" << std::endl;

    SplitArr(binaryKey, left, right, 10);

    std::cout << "Binary representation of left: ";
    for(int i = 0; i < 5; i++)
        std::cout << left[i];
    std::cout << std::endl;
    std::cout << "Binary representation of right: ";
    for(int i = 0; i < 5; i++)
        std::cout << right[i];
    std::cout << std::endl;

    // Shift right and left by 1
    LeftShift(left, 1, 4);
    LeftShift(right, 1, 4);

    std::cout << "Shifted Binary representation of left: ";
    for(int i = 0; i < 5; i++)
        std::cout << left[i];
    std::cout << std::endl;
    std::cout << "Shifted Binary representation of right: ";
    for(int i = 0; i < 5; i++)
        std::cout << right[i];
    std::cout << std::endl;

    // Combine the arrays to send to p10
    int* shiftedkey = CombineArrs(left, right, 10);
    u_int16_t key1 = PermP8(ToInt(shiftedkey, 10));

    std::cout << "Shifted Binary Key representation: ";
    for(int i = 0; i < 10; i++)
        std::cout << shiftedkey[i];
    std::cout << std::endl;



    /* Send Key 1 to Encryption */
    input = Feistal(input, key1);

    /* SW */
    int* binary = ToBinaryArr(input, 8);

    std::cout << "Binary Value representation: ";
    for(int i = 0; i < 8; i++)
        std::cout << binary[i];
    std::cout << std::endl;

    binary = Swap(binary, 8);
    input = ToInt(binary, 8);

    
    std::cout << "Swapped Binary Value representation: ";
    for(int i = 0; i < 8; i++)
        std::cout << binary[i];
    std::cout << std::endl;

    /* Generate Key 2 */
    
    // Shift right and left by 2
    LeftShift(left, 2, 4);
    LeftShift(right, 2, 4);

    // TODO fix this 
    std::cout << "Shifted Binary representation of left: ";
    for(int i = 0; i < 5; i++)
        std::cout << left[i];
    std::cout << std::endl;
    std::cout << "Shifted Binary representation of right: ";
    for(int i = 0; i < 5; i++)
        std::cout << right[i];
    std::cout << std::endl;


    // Combine the arrays to send to p10
    shiftedkey = CombineArrs(left, right, 10);
    u_int16_t key2 = PermP8(ToInt(shiftedkey, 10));

    /* Send Key 2 to Encryption */
    char outputF2 = Feistal(input, key2);

    /* Give to final permutation */
    input = PermIPn(input);


    std::cout << input;
}

u_int16_t Feistal(char input, u_int16_t key)
{
    // TODO
    // u_int16_t output = 0;

    return input;
}



/*** Binary Actions ***/

int* ToBinaryArr(u_int16_t val, int size = 8)
{
    // The binary array that is created from char
    // Hard coded size of 16 because there are no values that should be above 16 bits
    static int binary[16];
    size = size-1;

    for(int i = 0; i <= size; i++)
        binary[i] = (val >> size-i) & 1;
    
    return binary;
}

u_int16_t ToInt(int* binary, int size = 8)
{
    u_int16_t val = 0;
    for(int i = 0; i < size; i++)
        val += binary[i] * pow(2, (size - (i+1)));
    return val;
}

void LeftShift(int* val, unsigned int amount, int size = 8)
{
    for(int i = 0; i < amount; i++)
    {
        // Save the last to replace
        int temp = val[size-1];
        for(int j = size-1; j > 0; j--)
            val[j] = val[j-1];
        val[0] = temp;
    }

    return; 
}

void SplitArr(int* binary, int* left, int* right, int size)
{
    int split = size / 2;


    for(int i = 0; i < split; i++) {
        left[i] = binary[i];
        right[i] = binary[i + split];
    }

    return;
}

int* CombineArrs(int* left, int* right, int full_size)
{
    int* full = new int[full_size];
    int split = full_size / 2;

    for (int i = 0; i < split; i++) {
        full[i] = left[i];
        full[i + split] = right[i];
    }

    return full;
}

int* Swap(int* binary, int size)
{
    int left[size/2];
    int right[size/2];

    SplitArr(binary, left, right, size);
    binary = CombineArrs(right, left, size);

    return binary;
}


/*** Permutations ***/

/* Actually all of the work */

u_int16_t Permutation(u_int16_t val, int input_size, int permutation_size, int* permutation)
{
    // Binary array of length 8 that will be used to accomplish permutation
    int* binary = ToBinaryArr(val, input_size);
    

    // The permutated character in binary array form
    int permutated[16];
    

    for(int i = 0; i < permutation_size; i++)
        permutated[i] = binary[permutation[i]-1];


    // The permutated character
    char permCh = ToInt(permutated);

    return permCh;
}


/* Encryption */

char PermIP(char ch)
{
    return Permutation(ch, 8, 8, IP);
}

char PermIPn(char ch)
{
    return Permutation(ch, 8, 8, IPn);
}


/* Key Gen */

u_int16_t PermP10(u_int16_t val)
{
    return Permutation(val, 10, 10, P10);
}

u_int16_t PermP8(u_int16_t val)
{
    return Permutation(val, 10, 8, P8);
}

/* Feistal Function */

u_int16_t Expansion(u_int16_t val)
{
    return Permutation(val, 4, 8, EP);
}


