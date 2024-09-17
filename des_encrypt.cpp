/**
 * @file des_encrypt.cpp
 * @author Kaleb Keichel (kk471921@ohio.edu)
 * @brief Implements Simplified DES encryption security algorithm
 * @version 0.1
 * @date 2024-09-20
 * 
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std; 


/********* Variables *********/
/* All relevant permutations */

static int P1[4] = {2, 4, 3, 1}; // Constant permutation
static int P10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6}; // Constant permutation
static int IP[8] = {2, 6, 3, 1, 4, 8, 5, 7}; // Constant permutation
static int IPn[8] = {4, 1, 3, 5, 7, 2, 8, 6}; // Constant permutation
static int EP[8] = {4, 1, 2, 3, 2, 3, 4, 1}; // Constant permutation
static int P8[8] = {6, 3, 7, 4, 8, 5, 10, 9}; // Constant permutation

const char* progname = "";
const char* filename = "";


/********* Functions *********/
/**
 * @brief Reads in all of the contents of a file and places it into a string
 * 
 * @param file Filename of the file to read in
 * @return string The input of the file
 */
string ReadFile(const char* file);

/**
 * @brief Takes in an input string and encrypts it using DES. Most of the logic implemented here
 * 
 * @param input The input that desires to be encrypted
 */
void EncryptInput(string input);


void KeyGen();

/* Permutations */

/**
 * @brief Permutation implementation of P1
 * 
 * @param input An input stream of 4 bits
 * @return string Returns the permutated string
 */
string PerP1(string input);


int main(int argc, char *argv[])
{
    progname = argv[0];
    if(argc == 2)
        filename = argv[1];

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

string ReadFile(const char* file)
{
    string input = "";

    ifstream inStream;

    // Open the file and fail if it doesn't exist
    inStream.open(file);
    if(inStream.fail())
    {
        perror(file);
        exit(1);
    }

    // Read in each line and keep the newlines
    string currLine = "";
    while(getline(inStream, currLine))
    {
        input += currLine;
        input += '\n';
    }
    

    return input;
}


void EncryptInput(string input)
{
    // TODO





    cout << input << endl;
}


string PerP1(string input)
{
    string perm = "";
    // TODO
    return perm;
}