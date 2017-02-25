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
#include <sys/types.h>
#include <sys/wait.h>

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
    RDTSCP(timestamp);
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

int main()
{
    //uint64_t start = rdtsc();
    uint64_t start, end;
    unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;
    int total = 0;

    int parent_child[2];
    int child_parent[2];
    pipe(parent_child);
    pipe(child_parent);
    errno = 0;
    pid_t pid1 = fork();
    errno = 0;
    if (pid1)
    {
        //close(parent_child[1]);
        //close(child_parent[0]);
        do_child(parent_child[0], child_parent[1]);
        //close(parent_child[0]);
        //close(child_parent[1]);
        return 0;
    }
    else
    {
        //close(parent_child[0]);
        //close(child_parent[1]);
        do_parent(child_parent[0], parent_child[1]);
        //close(parent_child[1]);
        //close(child_parent[0]);
        wait(0);
    }
    return 0;
}

