#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>

#include "rds.h"
int main(){
    char file_name[] = "./simple_data_size_backup/file_5gb";
    int fd = open(file_name,O_SYNC);
    char buffer[4096];
    int filelen = 256 * 1024 * 5;
    struct timeval t1, t2;
    double elapsedTime = 0.0;
    double totalTime = 0.0;
    uint64_t pre, post;
    uint64_t total = 0;
    for(long i = 0; i < filelen; i++) {
        gettimeofday(&t1, NULL);
        CPUID;
        RDTSC(pre);
        read(fd, buffer,4096); 
        RDTSCP(post);
        CPUID;
        gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        totalTime += elapsedTime;
        total += post - pre;
    }
    close(fd);
    printf("read time %s is %f ms\n", file_name, totalTime);
    printf("read time %s is %f ms\n", file_name, totalTime / filelen);
    return 0;
}
