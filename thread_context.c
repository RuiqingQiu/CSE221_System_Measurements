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
 * to_child: a file descriptor of a pipe to the child
 * from_child: a file descriptor of a pipe from the child
 */
void do_parent(int from_child, int to_child)
{
    uint8_t ignorables = 0;
    unsigned int cycles_low, cycles_high;
    read(from_child, &ignorables, 1);
    uint64_t timestamp;
    CPUID;
    RDTSC(timestamp);
    ssize_t num_written = write(to_child, &timestamp, 8);
    // done
}

void do_child(int from_parent, int to_parent)
{
    unsigned int cycles_low, cycles_high;
    uint8_t single_byte = (uint8_t) 0;
    write(to_parent, &single_byte, 1);
    uint64_t parent_time = 1;
    ssize_t num_read = read(from_parent, &parent_time, 8);
    uint64_t child_time;
    RDTSCP(child_time);
    CPUID;
    printf("%llu\n", child_time - parent_time);
    fflush(stdout);
    // done
}

void* do_child_pthread(void * inputs)
{
    int * cast = (int*) inputs;
    do_child(cast[0], cast[1]);
}

int main()
{
    uint64_t start, end;
    unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;
    int total = 0;

    int parent_child[2];
    int child_parent[2];
    pipe(parent_child);
    pipe(child_parent);

    pthread_t inc_x_thread;

    errno = 0;
    int pthread_inputs[2];
    pthread_inputs[0] = parent_child[0];
    pthread_inputs[1] = child_parent[1];
    pthread_create(&inc_x_thread, NULL, do_child_pthread, (void*) pthread_inputs);
    do_parent(child_parent[0], parent_child[1]);
    pthread_join(inc_x_thread, NULL);
}

