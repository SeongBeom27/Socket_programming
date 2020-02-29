#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(void)
{
	int serv_sock;
	struct sockaddr_in serv_addr;			// struct which include server information, such as ip, port , internet version
	char *serv_ip = "127.0.0.1";			// server ip
	char *serv_port = "9190";				// server ip port

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);		// make socket
	if(serv_sock == -1)
	{
		error_handling("socket() error");
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;			// use IPV4 
	serv_addr.sin_addr.s_addr = inet_addr(serv_ip);	// ip address to hexa
	serv_addr.sin_port=htons(atoi(serv_port));	// port >>> char * to int
	
	if( bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)		// if return -1 << fault binding
	{
		error_handling("bind() error");
	}

	printf("Socket of file descriptor %d is binded complete\n", serv_sock);

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
