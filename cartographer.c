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

void* bigmem[TOTAL_LEN];

double get_diff_in_msec(struct timeval start, struct timeval stop)
{
    time_t sec_diff = stop.tv_sec - start.tv_sec;
    int usec_diff = stop.tv_usec - start.tv_usec;
    double total = (sec_diff * 1000.0) + (usec_diff / 1000.0);
    return total;
}

int main(int argc, char *argv[])
{
    uint64_t pre, post, diff;
    uint64_t i;
    uint64_t j;
    uint64_t current_ind = 0;
    uint64_t prev_ind = 0;
    double aggregate = 0;
    int pagesize = getpagesize();
    int fd = 0;
    uint8_t * data_addr = NULL;

    fd = open(OUR_FILE, O_RDWR);
    data_addr = mmap(0, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    CPUID;
    RDTSC(pre);
    data_addr[0] = 'a';
    RDTSCP(post);
    CPUID;
    diff = post - pre;
    printf("%llu\n", diff);
    aggregate += diff;
    munmap(data_addr, pagesize);
    close(fd);

    return 0;
}
