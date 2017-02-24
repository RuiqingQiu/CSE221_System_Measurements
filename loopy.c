#include "rds.h"
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>

#define NUM_ITERS 100

int main()
{
    uint64_t start, end;
    int expr_num = NUM_ITERS;

    CPUID;
    RDTSC(start);
    uint32_t i;
    for (i = 0; i < NUM_ITERS; ++i)
    {
    }
    RDTSCP(end);
    CPUID;
    printf("%llu\n", end-start);
}

