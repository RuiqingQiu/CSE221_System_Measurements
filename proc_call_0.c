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

void f0(){return;}
void f1(int a){}
void f2(int a, int b){}
void f3(int a, int b, int c){}
void f4(int a, int b, int c, int d){}
void f5(int a, int b, int c, int d, int e){}
void f6(int a, int b, int c, int d, int e, int f){}
void f7(int a, int b, int c, int d, int e, int f, int g){}

int main()
{
    uint64_t pre, post;
    uint64_t t0, t1, t2, t3, t4, t5, t6, t7;

    CPUID;
    RDTSC(pre);
    f0();
    RDTSCP(post);
    CPUID;
    t0 = post - pre;

    printf("%llu\n", t0);

    return 0;
}
