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


void EncryptByte(unsigned char input, u_int16_t key)
{
    // TODO
    /* Permutate input */
    input = PermIP(input);

    /* Generate Key 1 */

    // The binary representation of the 10 bit key
    int binaryKey[10];
    ToBinaryArr(binaryKey, key, 10);

    // The left half of the binary key
    int left[5];
    // The right half of the binary key
    int right[5];

    SplitArr(binaryKey, left, right, 10);

    // Shift right and left by 1
    LeftShift(left, 5);
    LeftShift(right, 5);

    // Combine the arrays to send to p10
    int shiftedkey[10];
    CombineArrs(shiftedkey, left, right, 10);
    u_int16_t key1 = PermP8(ToInt(shiftedkey, 10));

    /* Send Key 1 to Encryption */
    input = Feistal(input, key1);

    /* SW */
    int binary[8];
    ToBinaryArr(binary, input, 8);

    std::cout << "before: " << int(input) << std::endl;

    Swap(binary, 8);
    input = ToInt(binary, 8);
    std::cout << "after: " << int(input) << std::endl;

    /* Generate Key 2 */
    
    // Shift right and left by 2
    LeftShift(left, 5);
    LeftShift(left, 5);

    LeftShift(right, 5);
    LeftShift(right, 5);

    // Combine the arrays to send to p10
    CombineArrs(shiftedkey, left, right, 10);

    u_int16_t key2 = PermP8(ToInt(shiftedkey, 10));

    /* Send Key 2 to Encryption */
    char outputF2 = Feistal(input, key2);

    /* Give to final permutation */
    input = PermIPn(input);


    std::cout << input;
}

u_int16_t Feistal(unsigned char input, u_int16_t key)
{
    // TODO

    /* Convert to binary and split */
    
    int binary[8];
    int left[4];
    int right[4];
    ToBinaryArr(binary, input, 8);

    SplitArr(binary, left, right, 8);

    /* Expand R from 4->8bits */
   
    unsigned char rightVal;
    rightVal = ToInt(right, 4);
    std::cout << "Before expansion: " << int(rightVal) << std::endl;
    rightVal = Expansion(rightVal);
    std::cout << "After expansion: " << int(rightVal) << std::endl;

    /* XOR the Expanded Right side and the Key */

    unsigned char xored = rightVal^key;
    std::cout << "After xor: " << int(xored) << std::endl;

    /* Substitution */

    int binSubstituion[8];

    ToBinaryArr(binSubstituion, xored, 8);
    int LSub[4];
    int RSub[4];
    SplitArr(binSubstituion, LSub, RSub, 8);

    int Sub[4];

    std::cout << "LSub: ";
    for(int i = 0; i < 4; i++)
        std::cout << LSub[i];
    std::cout << std::endl;
    

    int LRow = LSub[0]*2 + LSub[3];
    int LCol = LSub[1]*2 + LSub[2];

    int LVal = S0[LRow][LCol];

    // TODO convert this to the first two bits

    

    u_int16_t output = 0;
    return input;
}



/*** Binary Actions ***/

void ToBinaryArr(int binary[], u_int16_t val, int size)
{
    // The binary array that is created from char
    // Hard coded size of 16 because there are no values that should be above 16 bits
    size = size-1;

    for(int i = 0; i <= size; i++)
        binary[i] = (val >> size-i) & 1;
    
    return;
}

u_int16_t ToInt(int binary[], int size = 8)
{
    u_int16_t val = 0;
    for(int i = 0; i < size; i++)
        val += binary[i] * pow(2, (size - (i+1)));
    return val;
}

void LeftShift(int val[], int size = 8)
{
    // Save the first element to wrap around
    int temp = val[0];
    for(int i = 0; i < size-1; i++)
    {
        val[i] = val[i+1];
    }
    val[size-1] = temp;

    return; 
}

void SplitArr(int binary[], int left[], int right[], int size)
{
    int split = size / 2;


    for(int i = 0; i < split; i++) {
        left[i] = binary[i];
        right[i] = binary[i + split];
    }

    return;
}

void CombineArrs( int full[], int left[], int right[], int full_size)
{
    int split = full_size / 2;

    for (int i = 0; i < split; i++) {
        full[i] = left[i];
        full[i + split] = right[i];
    }

    return;
}

void Swap(int binary[], int size)
{
    int left[size/2];
    int right[size/2];

    SplitArr(binary, left, right, size);
    CombineArrs(binary, right, left, size);

    return;
}


/*** Permutations ***/

/* Actually all of the work */

u_int16_t Permutation(u_int16_t val, int input_size, int permutation_size, int permutation[])
{
    // Binary array of length 8 that will be used to accomplish permutation
    int binary[input_size];
    ToBinaryArr(binary, val, input_size);

    // The permutated character in binary array form
    int permutated[16];
    
    for(int i = 0; i < permutation_size; i++)
        permutated[i] = binary[permutation[i]-1];

    // The permutated character
    unsigned char permCh = ToInt(permutated, 8);

    return permCh;
}


/* Encryption */

unsigned char PermIP(unsigned char ch)
{
    return Permutation(ch, 8, 8, IP);
}

unsigned char PermIPn(unsigned char ch)
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


