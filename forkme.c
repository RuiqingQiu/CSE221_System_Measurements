#include "rds.h"
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * This outputs the two times on the same line. The first number is the creation 
 * time in cycles, and the second number is the run time in cycles.
 */

int main()
{
    uint64_t pre, post;

    pid_t pid1;

    CPUID;
    RDTSC(pre);
    pid1 = fork();

    //Child
    if(pid1 == 0)
    {
        RDTSCP(post);
        CPUID;
        // creation time
        printf("%llu", post - pre);
        return 0;
    }
    //Parent
    else
    {
        wait(0);
        RDTSCP(post);
        CPUID;
        printf("\t%llu\n", post - pre);
    }
}

