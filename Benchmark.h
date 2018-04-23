//
// Created by Ding Li on 4/18/18.
//

/*
 * Benchmark.h
 *
 * benchmark for recording the time of normal
 * C function
 * Helper code for project
 *
 */

#include "Function.h"
#include <sys/stat.h>
#include <unistd.h>
#include <string>

#ifndef BF_PROJECT_BENCHMARK_H
#define BF_PROJECT_BENCHMARK_H


bool exists_test (const char *);
void Benchmark_normal(void);

#endif //BF_PROJECT_BENCHMARK_H
