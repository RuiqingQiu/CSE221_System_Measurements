#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>

#include "rds.h"
//char files[][40] = { "./simple_data_size/file_1gb", "./simple_data_size/file_256mb", "./simple_data_size/file_64mb", "./simple_data_size/file_16mb", "./simple_data_size/file_4mb", "./simple_data_size/file_1mb", "./simple_data_size/file_256kb", "./simple_data_size/file_64kb", "./simple_data_size/file_16kb", "./simple_data_size/file_4kb" };

char files[][40] = { "./simple_data_size_backup/file_1gb", "./simple_data_size_backup/file_256mb", "./simple_data_size_backup/file_64mb", "./simple_data_size_backup/file_16mb", "./simple_data_size_backup/file_4mb", "./simple_data_size_backup/file_1mb", "./simple_data_size_backup/file_256kb", "./simple_data_size_backup/file_64kb", "./simple_data_size_backup/file_16kb", "./simple_data_size_backup/file_4kb" };
int size[] = {1024*1024*1024, 256*1024*1024, 64*1024*1024, 16 * 1024 * 1024, 4 * 1024 * 1024, 1024*1024, 256 * 1024, 64 * 1024, 16 * 1024, 4 * 1024};
int main(){
    for(int i = 0; i < 10; i++){
        int fd = open(files[i],O_SYNC);
        //int fd = open("./simple_data_size/file_1gb",O_SYNC);
        if(fcntl(fd,F_NOCACHE,1) == -1){
            printf("disable cache failed\n");
        }
        int filelen = size[i];
        //int filelen = 1024 * 1024 * 1024;
        char buffer[4096];
        struct timeval t1, t2;
        double elapsedTime = 0.0;
        double totalTime = 0.0;
        uint64_t pre, post;
        uint64_t total = 0;
        //gettimeofday(&t1, NULL);
        for(int i = 0; i < filelen / 4096; i++) {
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
        //gettimeofday(&t2, NULL);
        //elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
        //elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        close(fd);
        printf("%f\n", (total / (filelen/4096.0) / 2.6 / 1000));
        printf("read time %s is %f ms\n", files[i], totalTime);
        printf("read time %s is %f ms\n", files[i], totalTime / (filelen/4096));
    }
    return 0;
}
