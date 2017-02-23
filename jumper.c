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
#define TOTAL_LEN (8000000 / sizeof(void*))
#define NUM_LOOPS 100
#define NUM_PTRS 100000
#define STRIDE_SIZE 67

void* bigmem[TOTAL_LEN];

double get_diff_in_msec(struct timeval start, struct timeval stop)
{
    time_t sec_diff = stop.tv_sec - start.tv_sec;
    int usec_diff = stop.tv_usec - start.tv_usec;
    double total = (sec_diff * 1000.0) + (usec_diff / 1000.0);
    return total;
}

int main()
{
  uint64_t pre, post, diff;
  uint64_t i;
  uint64_t j;
  uint64_t current_ind = 0;
  uint64_t prev_ind = 0;


  for (i = 0; i < NUM_PTRS; ++i)
  {
      current_ind = (current_ind + STRIDE_SIZE) % TOTAL_LEN;
      bigmem[prev_ind] = &bigmem[current_ind];
      prev_ind = current_ind;
  }

  void** current_spot = &bigmem[0];
  for (i = 0; i < NUM_PTRS; ++i)
  {
      CPUID;
      RDTSC(pre);
      current_spot = (void**) (*current_spot);
      RDTSCP(post);
      CPUID;
      diff = post - pre;
      printf("%llu\n", diff);
  }

  return 0;
}
