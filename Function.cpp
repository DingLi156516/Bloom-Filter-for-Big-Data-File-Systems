//
// Created by Ding Li on 4/8/18.
//
#include <string>
#include <stdio.h>
#include "Function.h"
#include <fstream>
#include <iostream>


/*
 * Function.cpp
 *
 * Implemenataion for Bloom Filter class
 *
 */

/*
 * Determine the number of bytes
 */
void Bloom_Filter::bytes_assertion(){
    NumBytes = M / 8;
    if ((M % 8) != 0)
    {
        cout<<"*** ERROR - M value must be divisible by 8 \n";
        exit(1);
    }
}

/*
 * clear the bloom filter
 */
void Bloom_Filter::clear(){
    for (int i = 0; i < NumBytes; i++)
        BFilter[i] = 0x00;
}

/*
 * Function to initialize CRC32 table
 */
void Bloom_Filter::gen_crc_table()
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
 * Put the strings in file into the bloom filter
 */
void Bloom_Filter::put_filename(string Path){
//    cout<<"File name of input list to add to filter ===========> ";
//    cin>>inFile1;
    strncpy(inFile1, Path.append("/metadata.txt").c_str(), sizeof(inFile1)-1);
//    cout<<Path<<endl;
    inFile1[sizeof(inFile1)] = '\0';
    fp1 = fopen(inFile1, "r");
    if (fp1 == NULL)
    {
        cout<<"ERROR in opening input file #1 ("<<inFile1<<") *** \n";
        exit(1);
    }
    while (1)
    {
        fgets(inString, 1024, fp1);
        inString[strlen(inString) - 1] = '\0';
        if (feof(fp1))
            break;
        for (i = 0; i < K; i++)
        {
            crc32 = update_crc(i, inString, strlen(inString));
            mapBloom(crc32);
        }
    }
    fclose(fp1);
}

/*
 * Output the current status of bloom filter
 */
void Bloom_Filter::status(string Path){
    // Output the Bloom filter
    cout<<"-------------------------------------------------------- \n";
    cout<<"Bloom filter is (M = "<<M<<" bits and K = "<<K<<" mappings)... \n";
    for (int i = 0; i < NumBytes; i++)
        printf("%2d ", i);
    cout<<endl;
    for (int i = 0; i < NumBytes; i++)
        printf("%2x ", BFilter[i]);
    ofstream out;
    out.open (Path.append("/metadata"), ios::out | ios::app | ios::binary);

    out.write((char*) &BFilter, sizeof BFilter);
    out.close();
    ifstream in(Path, ios::in | ios::binary);
    in.read((char *) &BFilter, sizeof BFilter);
    in.close();
    printf("\n");
    for (int i = 0; i < NumBytes; i++)
        printf("%2x ", BFilter[i]);
    cout<<endl;
    cout<<"-------------------------------------------------------- \n";
}

/*
 *
 */
void Bloom_Filter::matching_filename(){
    cout<<"File name of input list to check for match =========> ";

    cin>>inString;
    cout<<"-----------------------------------------------------\n";


    for (i = 0; i < K; i++) {
        crc32 = update_crc(i, inString, strlen(inString));
        retCode = testBloom(crc32);
        if (retCode == 0)
            break;
    }
    if (retCode == 1) {
        cout << inString << " is in the directory!\n";
    } else {
        cout << "There is no match for this filename in this directory!\n";
    }
}

/*
 * Function to map hash into Bloom filter
 */
void Bloom_Filter::mapBloom(word32 hash)
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
int Bloom_Filter::testBloom(word32 hash)
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

/*
 * Function to generate CRC32
 */
word32 Bloom_Filter::update_crc(word32 crc_accum, char *data_blk_ptr, word32 data_blk_size)
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








