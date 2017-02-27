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


int main()
{
    uint64_t pre, post;

    CPUID;
    RDTSC(pre);
    RDTSCP(post);
    CPUID;

    printf("%llu\n", post - pre);

    return 0;
}
