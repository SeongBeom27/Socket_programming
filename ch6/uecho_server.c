/*
	shutdown_server
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 30
void error_handling(char *message);

int main(int argc, char **argv)
{
	int fd;
	int sd;		// server socket descriptor

	char buf[BUFSIZE];
    struct sockaddr_in serv_addr;
	int len;

    if(argc != 3)
    {
        printf("Usage : %s <port>\n", argv[0]);     // when don't input port number
        exit(1);
    }
	
	/*File recevied from server open to store */
	fd = open("receive.dat", O_WRONLY|O_CREAT|O_TRUNC);
	if(fd == -1)
		error_handling("File open error");

    sd=socket(PF_INET, SOCK_DGRAM, 0);
    if(sd == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(bind(sd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

	if(connect(sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error!");

	while((len ==read(sd,buf,BUFSIZE)) != 0)
	{
		write(fd, buf, len);
	}

	close(fd);
	close(sd);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}




