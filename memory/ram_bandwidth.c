#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

/*
  File function: measure RAM bandwidth experiment
*/

// These variables are clobbered on every use of the RDTSC or RDTSCP macros
static uint64_t _lo, _hi;
// Macro to make running the cpuid instruction easier
#define CPUID __asm__ volatile ("cpuid"::)
// Macro to make running RDTSC/P easier
#define RDTSC(dest) __asm__ volatile ("rdtsc" : "=d" (_hi), "=a" (_lo)); dest = (_hi << 32) | _lo
#define RDTSCP(dest) __asm__ volatile ("rdtscp" : "=d" (_hi), "=a" (_lo)); dest = (_hi << 32) | _lo

// roughly 1GB
// May want to make this smaller. The output from running this program on my 
// system is 5+GBsc
// The project description says you don't need to know the L1/2 cache sizes, 
// but the lmbench paper mentions that this number is tuned based off of those 
// cache sizes, so I'm going to say go with the lmbench paper.
#define TOTAL_LEN 8000000
#define NUM_LOOPS 100

// This exists as a destination for our writing. Could move it to heap instead 
// of BSS, not sure if there would be a difference
uint8_t bigmem[TOTAL_LEN];

double get_diff_in_msec(struct timeval start, struct timeval stop)
{
    time_t sec_diff = stop.tv_sec - start.tv_sec;
    int usec_diff = stop.tv_usec - start.tv_usec;
    double total = (sec_diff * 1000.0) + (usec_diff / 1000.0);
    return total;
}

/*
 * This is all based off of the lmbench paper. First you write some incredibly 
 * large amount of data to memory, and then you read it. I think the summation 
 * when reading is designed to ensure that it doesn't get optimized out; 
 * because we disable optimizations, I don't know that we would have any issue 
 * removing the summation. In addition, the lmbench paper had the compiler 
 * unroll loops. I don't know how necessary this is, but I suppose those 
 * handful of cycles would shave off a bit of execution time.
 */
int main()
{
  uint64_t pre, post, diff;
  struct timespec write_pre, write_post, read_pre, read_post;
  double write_diff, read_diff;
  double write_ratio, read_ratio;
  //struct timeval stop, start;
  unsigned long stop, start;
  unsigned long loop_time = 18438;
  uint64_t i;
  uint64_t j;
  /*
  unsigned long avg_loop = 0;
  for (i =0; i < NUM_LOOPS; ++i)
  {
      start = clock();
      for(j = 0; j < TOTAL_LEN; j++) {}
      stop = clock();
      loop_time = (stop-start);
      avg_loop += loop_time;
  }
  avg_loop /= NUM_LOOPS;
  printf("%lu\n",avg_loop);
  return 0;
  */
  start = clock();
  for (i = 0; i < TOTAL_LEN; i+=2)
  {
      bigmem[i] = 17;
      bigmen[i+1] = 17; // loop unrolling

  }
  stop = clock();
  write_diff = (stop-start)  - loop_time;
  write_ratio = (double) TOTAL_LEN / write_diff;
  printf("Write byte/msec:\n%f\n", write_ratio);
  uint64_t sum = 0;

  start = clock();
  for (uint64_t i = 0; i < TOTAL_LEN; i+=2)
  {
      sum = bigmem[i];
      sum += bigmen[i + 1];
  }

  stop = clock();
  read_diff = (stop-start)  - loop_time;
  read_ratio = TOTAL_LEN / read_diff;
  printf("Read byte/msec:\n%f\n", read_ratio);
  return 0;
}
