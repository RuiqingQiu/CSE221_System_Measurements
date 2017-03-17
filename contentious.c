#include "rds.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FNAME_BUFSIZE 32
#define READ_BUFSIZE 4096

/*
 * This program is for determining the contention read time.
 *
 * It assumes that there are a number of files ready for it equal to 2^n, where
 * n is the input. If the files do not exist, behavior is undefined.
 *
 * It will output the read time in cycles for each contentious read.
 */

int main(int argc, char** argv)
{
	int num_forks = 0;
	int file_num = 0;
	char read_buf[READ_BUFSIZE];
	char fname_buf[FNAME_BUFSIZE];
	int fd = 0;
	uint64_t pre = 0;
	uint64_t post = 0;
	struct timeval pre_time;
	struct timeval post_time;
	double elapsedTime = 0.0f;

	if (argc > 1)
	{
		num_forks = atoi(argv[1]);
	}
	else
	{
		fprintf(stderr, "%s\n", "Number of forks not specified; assuming 0.");
	}

	while (num_forks > 0)
	{
		file_num *= 2;
		pid_t pid = fork();
		if (pid)
		{
			// Child
			++file_num;
		}
	}
	snprintf(fname_buf, FNAME_BUFSIZE, "block_file_%d.bk", file_num);

	// Open the file
	fd = open(fname_buf, O_RDONLY);

	gettimeofday(&pre_time, NULL);
	CPUID;
	RDTSC(pre);
	// Read the file
	read(fd, read_buf, READ_BUFSIZE);
	RDTSCP(post);
	CPUID;
	gettimeofday(&post_time, NULL);

	elapsedTime = (post_time.tv_sec - pre_time.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (post_time.tv_usec - pre_time.tv_usec) / 1000.0;   // us to ms
	// Print out timing information
	printf("%d\t%f\n", post-pre, elapsedTime);

	// Close the file... done here
	close(fd);
}
