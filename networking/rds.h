#include <stdint.h>
#ifndef __RDS_H
#define __RDS_H
// These variables are clobbered on every use of the RDTSC or RDTSCP macros
static uint64_t _lo, _hi;
// Macro to make running the cpuid instruction easier
#define CPUID __asm__ volatile ("cpuid"::)
// Macro to make running RDTSC/P easier
#define RDTSC(dest) __asm__ volatile ("rdtsc" : "=d" (_hi), "=a" (_lo)); dest = (_hi << 32) | _lo
#define RDTSCP(dest) __asm__ volatile ("rdtscp" : "=d" (_hi), "=a" (_lo)); dest = (_hi << 32) | _lo
#endif

