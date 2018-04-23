
#include "Function.h"
#include <iomanip>
#include "FSTree.h"
#include "Benchmark.h"

/*
 * main class for our bloom filter
 * to check if a file exist in a large directory
 *
 */



int main()
{
    cout<<"------------------------------------------ "<<endl;
    cout<<"         General Bloom Filter\n";
    cout<<"------------------------------------------ "<<endl;
    //get the directory path for check
    string Path = Get_path();
    //initialize the bloom filter
    Bloom_Filter BF;
    //determine the number of bytes in bloom filter and assert M is divisible by 8
    BF.bytes_assertion();
    //clear the bloom filter
    BF.clear();
    // Initialize the CRC32 table
    BF.gen_crc_table();
    //put the string into the bloom filter
    BF.put_filename(Path);
    //output the current status with M and K
    BF.status(Path);
    //check what values in the checking file match the one in bloom filter
    BF.matching_filename();


}
