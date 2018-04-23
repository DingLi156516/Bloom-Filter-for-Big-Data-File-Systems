//
// Created by Ding Li on 4/8/18.
//

/*
 * Function.h
 *
 * InterFace for Bloom Filter class
 * Including the construction of bloom filter and the test
 *
 *
 */

#ifndef BF_PROJECT_FUNCTION_H
#define BF_PROJECT_FUNCTION_H
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#define POLYNOMIAL 0x04C11DB7L  // Standard CRC-32 polynomial
#define M 48000  // Number of bits in the Bloom filter
#define K 4   // Number of bits set per mapping in filter
using namespace std;
typedef unsigned short int word16;
typedef unsigned int word32;
static word32 CrcTable[256];  // Table of 8-bit CRC32 remainders
class Bloom_Filter{
public:
    char BFilter[M / 8];      // Bloom filter array of M/8 bytes
    word32 NumBytes;            // Number of bytes in Bloom filter

    void bytes_assertion(void);
    void clear(void);
    void gen_crc_table(void);
    void put_filename(string);
    void status(string);
    void matching_filename(void);
    void mapBloom(word32 hash);
    int testBloom(word32 hash);
    word32 update_crc(word32 crc_accum, char *data_ptr, word32 data_size);



private:
    FILE *fp1;
    char inFile1[256];
    char inString[1024];
    word32 crc32;
    int retCode;
    word32 i;


};

#endif //BF_PROJECT_FUNCTION_H
