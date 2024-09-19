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
void EncryptByte(char input, u_int16_t key);

u_int16_t Feistal(char input, u_int16_t key);


/*** Binary Actions ***/

/**
 * @brief Converts an unsigned integer of size up to 16 to a binary array
 * 
 * @param val The value to be converted into a binary array
 * @param size The amount of bits that are utilized by the value
 * @return int* The returned binary representation in array format of the value
 */
int* ToBinaryArr(u_int16_t val, int size);

u_int16_t ToInt(int* binary, int size);

void LeftShift(int* val, unsigned int amount, int size);

void SplitArr(int* binary, int* left, int* right, int size);

int* CombineArrs(int* left, int* right, int full_size);

int* Swap(int* binary, int size);



/*** Permutations ***/

/* Actually all of the work */

u_int16_t Permutation(u_int16_t val, int input_size, int permutation_size, int* permutation);

/* Encryption */

char PermIP(char ch);

char PermIPn(char ch);

/* Key Gen */

u_int16_t PermP10(u_int16_t val);

u_int16_t PermP8(u_int16_t val);

/* Feistal Function */

u_int16_t Expansion(u_int16_t val);