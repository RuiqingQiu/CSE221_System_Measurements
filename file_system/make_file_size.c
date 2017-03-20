#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int X = 256 * 1024 * 1024 - 1;
    FILE *fp = fopen("file_256mb", "w");
    fseek(fp, X , SEEK_SET);
    fputc('\0', fp);
    fclose(fp);
}

