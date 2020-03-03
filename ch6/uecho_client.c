/*
	UDP_client
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUFSIZE 30
void error_handling(char *message);

int main(int argc, char* argv[])
{
    int sock;
    char message[BUFSIZE];
    int str_len, addr_size;

	struct sockaddr_in serv_addr;
	struct sockaddr_in from_addr;

    if(argc != 3)
    {
        printf("Usage : %s <IP> <PORT>\n", argv[0]);
        exit(1);
    }

    // make socket to access server
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
        error_handling("socket() error");


    // input ip, port of server to struct object
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    while(1)
    {
        /* message input, transfer*/
        fputs("Please input to transfer message (q to quit) : ", stdout);   // standard output
        fgets(message, BUFSIZE, stdin);     // your input string put in message

        if(!strcmp(message,"q\n")) break;

		sendto(sock, message, strlen(message), 0, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
        addr_size = sizeof(from_addr);
		str_len = recvfrom(sock, message, BUFSIZE, 0, (struct sockaddr*)&from_addr, &addr_size);
        message[str_len] = 0;
        printf("Message from Server : %s\n", message);
    }

    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
        


