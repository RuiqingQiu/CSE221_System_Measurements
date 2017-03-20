#include "rds.h"
#include "contention.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

// FNAME_FORMAT, FNAME_BUFSIZE, and FILE_BUFISZE are defined in contention.h

int main(int argc, char** argv)
{
	int num_files = 0;
	int fd;
	char file_buf[FILE_BUFSIZE];
	char fname_buf[FNAME_BUFSIZE];
	ssize_t writes = 0;

	if (argc < 2)
	{
		fprintf(stderr, "Need an argument for number of files (log_2) to create.\n");
		return 1;
	}

	num_files = floor(exp2(atoi(argv[1])))-1;
	memset(file_buf, 1, FILE_BUFSIZE);

	while (num_files >= 0)
	{
		snprintf(fname_buf, FNAME_BUFSIZE, FNAME_FORMAT, num_files);
		fd = open(fname_buf, O_WRONLY | O_CREAT);
		writes = write(fd, file_buf, FILE_BUFSIZE);
		close(fd);
		if (writes != FILE_BUFSIZE)
		{
			fprintf(stderr, "Error: file %s, fd %d, wrote %d bytes instead of %d.\n", fname_buf, fd, writes, FILE_BUFSIZE);
			return 1;
		}
		--num_files;
	}
	return 0;
}

