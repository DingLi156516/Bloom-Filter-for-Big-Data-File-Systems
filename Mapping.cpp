//
// Created by 李鼎 on 4/8/18.
//
#include "Mapping.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
/*
 * Function to generate CRC32
 */
word32 update_crc(word32 crc_accum, char *data_blk_ptr, word32 data_blk_size)
{
    register word32 i, j;
    for (j = 0; j < data_blk_size; j++)
    {
        i = ((int) (crc_accum >> 24) ^ *data_blk_ptr++) & 0xFF;
        crc_accum = (crc_accum << 8) ^ CrcTable[i];
    }
    crc_accum = ~crc_accum;

    return crc_accum;
}

/*
 * Function to initialize CRC32 table
 */
void gen_crc_table(void)
{
    register word32 crc_accum;
    register word16 i, j;
    // Initialize the CRC32 8-bit look-up table
    for (i = 0; i < 256; i++)
    {
        crc_accum = ((word32) i << 24);
        for (j = 0; j < 8; j++)
        {
            if (crc_accum & 0x80000000L)
                crc_accum = (crc_accum << 1) ^ POLYNOMIAL;
            else
                crc_accum = (crc_accum << 1);
        }
        CrcTable[i] = crc_accum;
    }
}

/*
 * Function to map hash into Bloom filter
 */
void mapBloom(word32 hash)
{
    int tempInt;
    int bitNum;
    int byteNum;
    unsigned char mapBit;
    tempInt = hash % M;
    byteNum = tempInt / 8;
    bitNum = tempInt % 8;

    mapBit = 0x80;
    mapBit = mapBit >> bitNum;

    // Map the bit into the Bloom filter
    BFilter[byteNum] = BFilter[byteNum] | mapBit;
}
/*
 * Function to test for a Bloom filter match
 */
int testBloom(word32 hash)
{
    int tempInt;
    int bitNum;
    int byteNum;
    unsigned char testBit;
    int retCode;
    tempInt = hash % M;
    byteNum = tempInt / 8;
    bitNum = tempInt % 8;

    testBit = 0x80;
    testBit = testBit >> bitNum;
    if (BFilter[byteNum] & testBit)
        retCode = 1;
    else
        retCode = 0;
    return retCode;
}
