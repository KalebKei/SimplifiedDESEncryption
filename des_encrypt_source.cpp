#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>


/********* Variables *********/
/* All relevant permutations */

static int P1[4] = {2, 4, 3, 1}; // Constant permutation
static int P10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6}; // Constant permutation
static int IP[8] = {2, 6, 3, 1, 4, 8, 5, 7}; // Constant permutation
static int IPn[8] = {4, 1, 3, 5, 7, 2, 8, 6}; // Constant permutation
static int EP[8] = {4, 1, 2, 3, 2, 3, 4, 1}; // Constant permutation
static int P8[8] = {6, 3, 7, 4, 8, 5, 10, 9}; // Constant permutation




/********* Functions *********/



/*** Key Related ***/

/**
 * @brief Reads in a constant char* (c string) and reads it in as a hex value and places it into a 16 bit unsigned integer.
 * 
 * @param ch 
 * @return u_int16_t 
 */
u_int16_t ReadKey(const char* hexInput)
{
    u_int16_t key = 0x0;

    // This is just the string version of the char array. Ease of use with built in string functions
    std::string strHex = hexInput;

    key = stoi(strHex, 0, 16); // Starting at index 0. 16 is the base (hex)
    
    return key;
}





/*** Input Related ***/

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

/**
 * @brief Takes in an input char (8 bits) and encrypts it using DES. Most of the logic implemented here
 * 
 * @param input The input that desires to be encrypted
 */
void EncryptInput(std::string input)
{
    // TODO
    




    std::cout << input << std::endl;
}

/**
 * @brief Converts an 8 bit character into a binary array. Probably more convinient/efficient ways, but this is how my brain worked 
 * 
 * @param ch The input character to be converted
 * @return int* A binary array representation of ch of length 8
 */
int* CharToBinaryArr(char ch)
{
    // Todo
    // The binary array that is created from char
    static int binary[8] = {0,0,0,0,0,0,0,0};

    // The return value of binary operations
    char ret = 0;

    // Most significant is index 0

    ret = ch & 0x80; // 1 0 0 0 0 0 0 0
    if(ret != 0)
        binary[0] = 1;

    ret = ch & 0x40; // 0 1 0 0 0 0 0 0
    if(ret != 0)
        binary[1] = 1;
    
    ret = ch & 0x20; // 0 0 1 0 0 0 0 0 
    if(ret != 0)
        binary[2] = 1;
    
    ret = ch & 0x10; // 0 0 0 1 0 0 0 0 
    if(ret != 0)
        binary[3] = 1;

    ret = ch & 0x8; // 0 0 0 0 1 0 0 0 
    if(ret != 0)
        binary[4] = 1;

    ret = ch & 0x4; // 0 0 0 0 0 1 0 0 
    if(ret != 0)
        binary[5] = 1;
    
    ret = ch & 0x2; // 0 0 0 0 0 0 1 0 
    if(ret != 0)
        binary[6] = 1;

    ret = ch & 0x1; // 0 0 0 0 0 0 0 1
    if(ret != 0)
        binary[7] = 1;
    
    for (int i = 0; i < 8; i++)
        std::cout << binary[i];
    std::cout << std::endl;

    return binary;
}



/*** Permutations ***/

/**
 * @brief Permutation implementation of P1
 * 
 * @param input An input stream of 4 bits
 * @return std::string Returns the permutated std::string
 */
std::string PerP1(char input)
{
    std::string perm = "";
    // TODO
    return perm;
}