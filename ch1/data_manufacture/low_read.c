#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 100

void error_handling(char* message);

int main(void)
{
    int fildes;
    char buf[BUFSIZE];

    fildes=open("data.txt", O_RDONLY);
    if( fildes == -1)
    {
        error_handling("Open() error!");
    }
    printf("Open file's file descriptor is %d\n", fildes);
    if(read(fildes, buf, sizeof(buf)) == -1)
    {
        error_handling("write() error!");

    }

	printf("file's contents : %s", buf);

    close(fildes);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

