#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// These variables are clobbered on every use of the RDTSC or RDTSCP macros
static uint64_t _lo, _hi;
// Macro to make running the cpuid instruction easier
#define CPUID __asm__ volatile ("cpuid"::)
// Macro to make running RDTSC/P easier
#define RDTSC(dest) __asm__ volatile ("rdtsc" : "=d" (_hi), "=a" (_lo)); dest = (_hi << 32) | _lo
#define RDTSCP(dest) __asm__ volatile ("rdtscp" : "=d" (_hi), "=a" (_lo)); dest = (_hi << 32) | _lo

// roughly 1GB
// cache sizes, so I'm going to say go with the lmbench paper.
#define NUM_LOOPS 100000
#define STRIDE_SIZE 1
// Array size, 8000 = 8000 bytes
#define ARRAY_SIZE (800000000 / sizeof(int))

int bigmem[ARRAY_SIZE];

int rand_lim(int limit) {
    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

int main()
{
    uint64_t pre, post, diff;
    uint64_t i;
    uint64_t j;
    uint64_t current_ind = 0;
    uint64_t prev_ind = 0;

    uint64_t measure_overhead = 0;
    for(i = 0; i < NUM_LOOPS; i++){
        CPUID;
        RDTSC(pre);
        RDTSC(post);
        CPUID;
        measure_overhead += (post-pre);
    }
    measure_overhead /= NUM_LOOPS;
    printf("measurement overhead is %llu\n", measure_overhead);
    //Warm up the cache
    for(i = 0; i < ARRAY_SIZE; i++){
        bigmem[i] = i;
    }
    int next;
    uint64_t total = 0; 
    for(i = 0; i < 1000; i++){
        int index = rand_lim(ARRAY_SIZE);
        CPUID;
        RDTSC(pre);
        bigmem[index];
        RDTSCP(post);
        CPUID;
        diff = post - pre; 
        total += diff;
    }
    printf("%llu\n", diff-measure_overhead*1000);

    return 0;
}
