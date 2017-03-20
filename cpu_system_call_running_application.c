#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

// These variables are clobbered on every use of the RDTSC or RDTSCP macros
static uint64_t _lo, _hi;
// Macro to make running the cpuid instruction easier
#define CPUID __asm__ volatile ("cpuid"::)
// Macro to make running RDTSC/P easier
#define RDTSC(dest) __asm__ volatile ("rdtsc" : "=d" (_hi), "=a" (_lo)); dest = (_hi << 32) | _lo
#define RDTSCP(dest) __asm__ volatile ("rdtscp" : "=d" (_hi), "=a" (_lo)); dest = (_hi << 32) | _lo

// roughly 1GB
// cache sizes, so I'm going to say go with the lmbench paper.
#define TOTAL_LEN (8000000 / sizeof(void*))
#define NUM_LOOPS 100
#define NUM_PTRS 100000
#define STRIDE_SIZE 67

#define OUR_FILE "mapme.mapper"

int main()
{
    uint64_t pre, post, diff;

   
    for (int i = 0; i < 1000; i++) {

        pid_t pid = fork();

        if (pid == -1) {
            printf("fork failed!\n");
            exit(-1);
        }
        if (pid == 0) {
            CPUID;
            RDTSC(pre);
            getpid();
            RDTSCP(post);
            CPUID;
            printf("%llu\n", post - pre);

            return 0;
        } else {
            wait(NULL);
        }
    }


    return 0;
}
