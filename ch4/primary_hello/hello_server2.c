/*
	version 1.2
 	server
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char **argv)
{
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;

	int clnt_addr_size;
	char message[] = "Hello World!";
	
	if(argc != 2)
	{
		printf("Usage : %s <PORT>\n", argv[0]);
		exit(1);
	}
	// 1. server socekt generation
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);		// IPV4, TCP
	if(serv_sock == -1)
	{
		error_handling("socket() error");
	}
	// insert address information
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	// 2. allocate server address information to server socket
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
	{
		error_handling("bind() error");
	}
	// 3. response holdposition
	if(listen(serv_sock, 5) == -1)			// queue size : 5
	{
		error_handling("listen() error");
	}
	
	// 4. prepare space for client 
	clnt_addr_size = sizeof(clnt_addr);

	// 5. accept cient request
	clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
	if(clnt_sock== -1)
	{
		error_handling("accept() error");
	}

	// 6. transefer data to client
	write(clnt_sock, message, sizeof(message));
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

