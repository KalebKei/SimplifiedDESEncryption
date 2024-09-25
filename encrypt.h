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

/*** Substitution Tables ***/
static int S0[4][4] = 
{
    {1,0,3,2},
    {3,2,1,0},
    {0,2,1,3},
    {3,1,3,2}
};

static int S1[4][4] = 
{
    {0,1,2,3},
    {2,0,1,3},
    {3,0,1,0},
    {2,1,0,3}
};


/********* Functions *********/


/*** Input Related ***/

/**
 * @brief Reads in a constant char* (c string) and reads it in as a hex value and places it into a 16 bit unsigned integer.
 * 
 * @param ch 
 * @return u_int16_t 
 */
u_int16_t ReadKey(const char* hexInput);

/**
 * @brief Reads in all of the contents of a file and places it into a std::string
 * 
 * @param file Filename of the file to read in
 * @return std::string The input of the file
 */
std::string ReadFile(const char* file);

/**
 * @brief Takes in an input char (8 bits) and encrypts it using DES. Most of the logic implemented here
 * 
 * @param input The input that desires to be encrypted
 */
void EncryptByte(unsigned char input, u_int16_t key);

/**
 * @brief The Feistel function implemented. Takes in an 8 bit input alongside a 10 bit key. Yes, it's spelled wrong it's a gimmick at this point
 * 
 * @param input The 8 bit character to be encrypted
 * @param key The 10 bit key used for encryption
 * @return u_int16_t The encrypted input
 */
u_int16_t Feistal(unsigned char input, u_int16_t key);


/*** Binary Actions ***/

/**
 * @brief Converts an unsigned integer of size up to 16 to a binary array
 * 
 * @param val The value to be converted into a binary array
 * @param size The amount of bits that are utilized by the value
 */
void ToBinaryArr(int binary[], u_int16_t val, int size);

/**
 * @brief Converts a binary array (integer array containing only 1's and 0's) to a unsigned 16 bit integer
 * 
 * @param binary The binary representation of a integer up to 16 bits
 * @param size The size of the binary array up to 16 bits
 * @return u_int16_t The integer representation of the inputted binary array
 */
u_int16_t ToInt(int binary[], int size);

/**
 * @brief Implements a left bit shift with wrap around
 * 
 * @param val The binary array representation of what we want to shift
 * @param size The size of the array
 */
void LeftShift(int val[], int size);

/**
 * @brief Splits an array in half
 * 
 * @param binary The array to be split
 * @param left The output left side of the array
 * @param right The output right side of the array
 * @param size The size of the full binary array
 */
void SplitArr(int binary[], int left[], int right[], int size);

/**
 * @brief Combines to arrays together
 * 
 * @param full The output array
 * @param left The input left side of the soon to be output
 * @param right The input right side of the soon to be output
 * @param full_size The size of the output array
 */
void CombineArrs(int full[], int left[], int right[], int full_size);

/**
 * @brief Swaps the front half of an array with the back half
 * 
 * @param binary The array to be swapped
 * @param size The size of the array
 */
void Swap(int binary[], int size);

/*** Permutations ***/

/* Actually all of the work */

/**
 * @brief A function that performs required bit permutations on values up to size 16 bits. Not intended for direct use
 * 
 * @param val The value to be permutated
 * @param input_size The size of the binary representation of the input
 * @param permutation_size The size of the permutation output
 * @param permutation Uses global variables defined at the top of this header file to define the permutation to be used. 
 * @return u_int16_t The permutated output
 */
u_int16_t Permutation(u_int16_t val, int input_size, int permutation_size, int permutation[]);

/* Encryption */

/**
 * @brief Ease of use IP permutation
 * 
 * @param ch 8 bit character to be permutated
 * @return unsigned char The permutated character
 */
unsigned char PermIP(unsigned char ch);

/**
 * @brief Ease of use IP-1 permutation
 * 
 * @param ch 8 bit character to be permutated
 * @return unsigned char The permutated character
 */
unsigned char PermIPn(unsigned char ch);

/* Key Gen */

/**
 * @brief Ease of use P10 permutation
 * 
 * @param val The 10 bit character to be permutated
 * @return u_int16_t The permutated character
 */
u_int16_t PermP10(u_int16_t val);

/**
 * @brief Ease of use P8 permutation
 * 
 * @param val The 10 bit character input to be permutated
 * @return u_int16_t The 8 bit permuted character
 */
u_int16_t PermP8(u_int16_t val);

/* Feistal Function */

/**
 * @brief Ease of use expansion permutation
 * 
 * @param val The 4 bit character input to be permutated
 * @return u_int16_t The 8 bit permutated character
 */
u_int16_t Expansion(u_int16_t val);

/**
 * @brief Ease of use P4 permutation
 * 
 * @param val The character to be permutated
 * @return u_int16_t The permutated character
 */
u_int16_t PermP4(u_int16_t val);