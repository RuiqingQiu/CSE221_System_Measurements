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
uint64_t rdtsc(int x){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

#define NUM_ITERS 100

void f0(){return;}
void f1(int a){}
void f2(int a, int b){}
void f3(int a, int b, int c){}
void f4(int a, int b, int c, int d){}
void f5(int a, int b, int c, int d, int e){}
void f6(int a, int b, int c, int d, int e, int f){}
void f7(int a, int b, int c, int d, int e, int f, int g){}
void helper();
uint64_t store[NUM_ITERS];

void *inc_x(void* start_time)
{
    unsigned int cycles_low1, cycles_high1;
    __asm__ __volatile__ ("cpuid" ::: "%rdx", "%rax","%rbx", "%rcx");
    __asm__ __volatile__ ("rdtscp" : "=a" (cycles_low1), "=d" (cycles_high1)::"%rdx", "%rax");
    uint64_t start = *(uint64_t*)start_time;
    uint64_t end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );

    printf("%llu\n", (end-start));
    /* the function must return something - NULL will do */
    return NULL;
}

/*
 * to_child: a file descriptor of a pipe to the child
 * from_child: a file descriptor of a pipe from the child
 */
void do_parent(int from_child, int to_child)
{
    uint8_t ignorables = 0;
    unsigned int cycles_low, cycles_high;
    read(from_child, &ignorables, 1);
    __asm__ __volatile__ ("rdtscp" : "=a" (cycles_low), "=d" (cycles_high)::"%rdx", "%rax");
    uint64_t timestamp = ( ((uint64_t)cycles_high << 32) | cycles_low );
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
    __asm__ __volatile__ ("rdtscp" : "=a" (cycles_low), "=d" (cycles_high)::"%rdx", "%rax");
    uint64_t child_time = ( ((uint64_t)cycles_high << 32) | cycles_low );
    printf("%llu\n", child_time - parent_time);
    fflush(stdout);
    // done
}

void do_child_pthread(void * inputs)
{
    int * cast = (int*) inputs;
    do_child(cast[0], cast[1]);
}

int main(){
    //uint64_t start = rdtsc();
    uint64_t start, end;
    unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;
    int expr_num = NUM_ITERS;
    int total = 0;
    

    int parent_child[2];
    int child_parent[2];
    pipe(parent_child);
    pipe(child_parent);
    for(int i = 0; i < NUM_ITERS; i++){
        pthread_t inc_x_thread;
        //__asm__ __volatile__ ("cpuid" ::: "%rdx", "%rax","%rbx", "%rcx");
        //__asm__ __volatile__ ("rdtscp" : "=a" (cycles_low), "=d" (cycles_high)::"%rdx", "%rax");
        //start = ( ((uint64_t)cycles_high << 32) | cycles_low );
        errno = 0;
        //pid_t pid1 = fork();
        errno = 0;
        int pthread_inputs[2];
        pthread_inputs[0] = parent_child[0];
        pthread_inputs[1] = child_parent[1];
        pthread_create(&inc_x_thread, NULL, do_child_pthread, (void*) pthread_inputs);
        do_parent(child_parent[0], parent_child[1]);
        pthread_join(inc_x_thread, NULL);
        /*
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
        */
        //pthread_create(&inc_x_thread, NULL, inc_x, &start);
        //pthread_join(inc_x_thread, NULL);
        //__asm__ __volatile__ ("cpuid" ::: "%rdx", "%rax","%rbx", "%rcx");
        //__asm__ __volatile__ ("rdtscp" : "=a" (cycles_low1), "=d" (cycles_high1)::"%rdx", "%rax");
        //end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        //store[i] = end - start;        
    }
    return 0;
    printf("===============\n");
    for(int i = 0; i < NUM_ITERS; i++){
        printf("%llu\n", store[i]);
    }
    return 1;

    for(int i = 0; i < 100; i++){
        pid_t pid1;

        __asm__ __volatile__ ("cpuid" ::: "%rdx", "%rax","%rbx", "%rcx");
        __asm__ __volatile__ ("rdtscp" : "=a" (cycles_low), "=d" (cycles_high)::"%rdx", "%rax");
        pid1 = fork();

        __asm__ __volatile__ ("rdtscp" : "=a" (cycles_low1), "=d" (cycles_high1)::"%rdx", "%rax");
        __asm__ __volatile__ ("cpuid" ::: "%rdx", "%rax","%rbx", "%rcx");

        start = ( ((uint64_t)cycles_high << 32) | cycles_low );
        end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        //Child
        if(pid1 == 0){
            // creation time
            printf("%llu\n", (end-start));
            exit(0);
        }
        //Parent
        else{
            //printf("creation time: %llu\n", (end-start));
            //creation_time[i] = end - star;
            wait(0);
            // running time
            __asm__ __volatile__ ("rdtscp" : "=a" (cycles_low1), "=d" (cycles_high1)::"%rdx", "%rax");
            __asm__ __volatile__ ("cpuid" ::: "%rdx", "%rax","%rbx", "%rcx");
            start = ( ((uint64_t)cycles_high << 32) | cycles_low );
            end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
            store[i] = (end-start);
        }
        //----------------------------------------------------------
        /* Code for running benchmark for procedure call and system call
        __asm__ __volatile__ ("cpuid" ::: "%rdx", "%rax","%rbx", "%rcx");
        __asm__ __volatile__ ("rdtscp" : "=a" (cycles_low), "=d" (cycles_high)::"%rdx", "%rax");
        //for(int j = 0; j < expr_num; j++){
        //}
        sleep(0);
        //f7(1,1,1,1,1,1,1);
        //f6(1,1,1,1,1,1);
        __asm__ __volatile__ ("rdtscp" : "=a" (cycles_low1), "=d" (cycles_high1)::"%rdx", "%rax");
        __asm__ __volatile__ ("cpuid" ::: "%rdx", "%rax","%rbx", "%rcx");
        start = ( ((uint64_t)cycles_high << 32) | cycles_low );
        end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        printf("%llu\n", (end-start));
        total += end - start;
        */
    }
    printf("========\n");
    for (int i = 0; i < NUM_ITERS; ++i)
    {
        printf("%llu\n", store[i]);
    }
    //printf("\n%d\n",total);
    //uint64_t end = rdtsc();
    //printf("%" PRIu64 "\n", start);

    //printf("%" PRIu64 "\n", end);
    
    return 1;
}

