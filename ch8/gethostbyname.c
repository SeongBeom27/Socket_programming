#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

void error_handling(char *message);

int main(int argc, char **argv)
{
	int i;
	struct hostent *host;

	if(argc != 2)
	{
		printf("input ip, port");
		exit(1);
	}

	host = gethostbyname(argv[1]);
	if(!host)
		error_handling("get host error");

	printf("Officially name : %s \n\n", host->h_name);

	puts("Aliases-------");
	for(i = 0; host->h_aliases[i]; i++)
	{
		puts(host->h_aliases[i]);
	}

	printf("Address Type : %s \n", host->h_addrtype == AF_INET ? "AF_INET" : "AF_INET6");

	puts("IP Address------");
	for(i = 0; host->h_addr_list[i]; i++)
	{
		// inet_ntoa : convert "network byte order" to "formal ip address"
		puts(inet_ntoa( *(struct in_addr*)host->h_addr_list[i]));
	}
	return 0;
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
