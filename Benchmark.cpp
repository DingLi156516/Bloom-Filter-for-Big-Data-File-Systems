//
// Created by Ding Li on 4/18/18.
//
#include "Benchmark.h"

/*
 * Benchmark.cpp
 *
 * Implemenataion for Benchmark class
 *
 */


bool exists_test (const char* name) {
    return ( access( name, F_OK ) != -1 );
}


void Benchmark_normal(){
    double ThisRunTime;
    clock_t start_t, end_t;
    for(int k = 100; k < 10000; k += 100) {

        start_t = clock();
        for (int i = 0; i < k; i++) {
            if (exists_test("/Users/liding/Desktop/test/test_dir/absolvable.txt"));
        }
        end_t = clock();
        ThisRunTime = (double) (end_t - start_t) / CLOCKS_PER_SEC;
        printf("%f\n", ThisRunTime);
    }
}

