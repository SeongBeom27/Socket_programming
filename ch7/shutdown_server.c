/*
	shutdown_server
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 30
void error_handling(char *message);

int main(int argc, char **argv)
{
	int serv_sock;
	int clnt_sock;
	int fd;
	char buf[BUFSIZE];

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    int clnt_addr_size;
	int len;

    if(argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);     // when don't input port number
        exit(1);
    }

	fd = open("hello.txt", O_RDONLY);
	if(fd == -1)
        error_handling("File open error");

    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");
	
	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock=accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);

	if(clnt_sock == -1)
		error_handling("accept() error");
	/* Transfer data to client */
	while((len = read(fd, buf, BUFSIZE)) != 0)
	{
		write(clnt_sock, buf, len);
	}

	if(shutdown(clnt_sock, SHUT_WR) == -1)
		error_handling("shutdown() error");

	len = read(clnt_sock, buf, BUFSIZE);
	write(1, buf, len);
	
	close(fd);
	close(clnt_sock);
	close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
