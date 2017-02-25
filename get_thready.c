#include "rds.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>

/*
 * This program outputs two times on the sime line. The first output is the 
 * thread creation time, and the second is the thread running time.
 */

void* do_child_pthread(void * inputs)
{
    uint64_t post;
    uint64_t pre = *((uint64_t*) inputs);
    RDTSCP(post);
    CPUID;
    printf("%llu", post - pre);
}

int main()
{
    uint64_t start, end;

    pthread_t split;
    errno = 0;
    CPUID;
    RDTSC(start);
    pthread_create(&split, NULL, do_child_pthread, (void*) &start);
    pthread_join(split, NULL);
    RDTSCP(end);
    CPUID;
    printf("\t%llu\n", end - start);
    return 0;
}

