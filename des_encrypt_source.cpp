#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cmath>



/********* Variables *********/
/*** All relevant permutations ***/

/* Encryption */
static int IP[8] = {2, 6, 3, 1, 4, 8, 5, 7}; // Constant permutation used at start of encryption
static int IPn[8] = {4, 1, 3, 5, 7, 2, 8, 6}; // Constant permutation used at end of encryption (inverse IP)

/* Key gen */
static int P10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6}; // Constant permutation
static int P8[8] = {6, 3, 7, 4, 8, 5, 10, 9}; // Constant permutation

/* Feistal Function */
static int EP[8] = {4, 1, 2, 3, 2, 3, 4, 1}; // Constant permutation used for the feistal function
static int P4[4] = {2, 4, 3, 1}; // Constant permutation



/********* Functions *********/


/*** Input Related ***/

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
    




    std::cout << input;
}



/*** Binary Actions ***/

/**
 * @brief Converts an unsigned integer of size up to 16 to a binary array
 * 
 * @param val The value to be converted into a binary array
 * @param size The amount of bits that are utilized by the value
 * @return int* The returned binary representation in array format of the value
 */
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

/**
 * @brief 
 * 
 * @param binary 
 * @param size 
 * @return u_int16_t 
 */
u_int16_t ToInt(int* binary, int size = 8)
{
    u_int16_t val = 0;
    for(int i = 0; i < size; i++)
        val += binary[i] * pow(2, (size - (i+1)));
    return val;
}

/**
 * @brief 
 * 
 * @param val 
 * @param amount 
 * @param size 
 * @return u_int16_t 
 */
u_int16_t LeftShift(u_int16_t val, unsigned int amount, int size = 8)
{
    int* binary = ToBinaryArr(val, size);

    for(int i = 0; i < amount; i++)
    {
        std::cout << "before ";
        for(int b = 0; b < size; b++)
            std::cout << binary[b];
        std::cout << std::endl;

        // Save the last to replace
        int temp = binary[size-1];
        std::cout << temp << std::endl;
        for(int j = size-1; j > 0; j--)
            binary[j] = binary[j-1];
        binary[0] = temp;

        std::cout << "after  ";
        for(int b = 0; b < size; b++)
            std::cout << binary[b];
        std::cout << std::endl;
    }

    u_int16_t shifted_val = ToInt(binary, size);
    std::cout << shifted_val << std::endl; 

    return shifted_val; 
}


void SplitArr(int* binary, int* left, int* right, int size)
{
    int split = size / 2;

    // Create new arrays for the left and right side
    left = new int[split];
    right = new int[split];

    for(int i = 0; i < split; i++) {
        left[i] = binary[i];
        right[i] = binary[i + split];
    }

    std::cout << "Full: ";
    for (int i = 0; i < size; i++) {
        std::cout << binary[i];
    }
    std::cout << std::endl;

    std::cout << "Left:  ";
    for (int i = 0; i < split; i++) {
        std::cout << left[i];
    }
    std::cout << std::endl;

    std::cout << "Right: ";
    for (int i = 0; i < split; i++) {
        std::cout << right[i];
    }
    std::cout << std::endl;

    return;
}


/*** Permutations ***/

/* Actually all of the work */

u_int16_t Permutation(u_int16_t val, int input_size, int permutation_size, int* permutation)
{
    // The permutated character
    char permCh = 0;
    std::cout << "Permutating value " << val << std::endl;

    // Binary array of length 8 that will be used to accomplish permutation
    int* binary = ToBinaryArr(val, input_size);

    
    for (int i = 0; i < input_size; i++)
        std::cout << binary[i];
    std::cout << std::endl;
    

    // The permutated character in binary array form. (Probably won't keep)
    int permutated[16];
    for(int i = 0; i < permutation_size; i++)
        std::cout << permutation[i];
    std::cout << std::endl;
    

    for(int i = 0; i < permutation_size; i++)
    {
        permutated[i] = binary[permutation[i]-1];
        std::cout << permutated[i];
        // permCh += binary[permutation[i]-1] * pow(2, 7 - i);
        // std::cout << permCh << std::endl;
    } 
    // std::cout << permCh << std::endl;
    std::cout << std::endl;

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


