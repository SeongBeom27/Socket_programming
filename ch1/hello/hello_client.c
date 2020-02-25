#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *message);

int main(int argc, char* argv[])
{
	int sock;
	/*
	struct sockaddr_in{
		sa_family_t 	sin_family;		// addressing family
		uint16_t		sin_port;		// 16 bit TCP or UDO Port
		struct in_addr	sin_addr;		// 32 bit IPv4 address
		char			sin_zero[8];	// not use
	}
	*/
	struct sockaddr_in serv_addr;
	struct sockaddr_in sock_addr;
	char message[30];
	int str_len;

	if(argc != 3)
	{
		printf("Usage : %s <IP> <PORT>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		error_handling("socket() error");
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	memset(&sock_addr, 0, sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	sock_addr.sin_port = htons(atoi("9000"));

	// connect에서 bind자동으로 해주기 전에 미리 bind해보기
	if(bind(sock, (struct sockaddr*) &sock_addr, sizeof(sock_addr)) == -1)
	{
		error_handling("bind() error");
	}

	if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
	{
		error_handling("connect() error");
	}

	str_len = read(sock, message, sizeof(message)-1);
	if(str_len == -1)
	{
		error_handling("read() error");
	}
	printf("Messge from server: %s\n", message);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
