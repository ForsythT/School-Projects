#include "rdrand.h"
unsigned long genRDrand(unsigned long min, unsigned long max){
    int retries = 10;
    unsigned long long rand64;
    while (retries--)
    {
        __builtin_ia32_rdrand64_step(&rand64);
    }
    float test = (float)rand64 / ULONG_MAX;
    test = test * (max - min) + min;
    unsigned long result = test;
    return result;
}
