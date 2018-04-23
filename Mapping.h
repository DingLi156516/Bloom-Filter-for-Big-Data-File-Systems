//
// Created by 李鼎 on 4/8/18.
//

#ifndef BF_PROJECT_MAPPING_H
#define BF_PROJECT_MAPPING_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define POLYNOMIAL 0x04C11DB7L  // Standard CRC-32 polynomial
#define M 32   // Number of bits in the Bloom filter
#define K 4   // Number of bits set per mapping in filter
typedef unsigned short int word16;
typedef unsigned int word32;
char BFilter[M / 8];      // Bloom filter array of M/8 bytes
word32 NumBytes;            // Number of bytes in Bloom filter

static word32 CrcTable[256];  // Table of 8-bit CRC32 remainders
void gen_crc_table(void);
void mapBloom(word32 hash);
int testBloom(word32 hash);
word32 update_crc(word32 crc_accum, char *data_ptr, word32 data_size);



#endif //BF_PROJECT_MAPPING_H

