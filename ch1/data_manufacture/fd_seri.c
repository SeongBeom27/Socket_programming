#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>

int main(void)
{
	int fdes1, fdes2, fdes3;

	fdes1 = socket(PF_INET, SOCK_STREAM, 0);	// MAKE TCP SOCKET
	fdes2 = open("test.dat", O_CREAT);
	fdes3 = socket(PF_INET, SOCK_DGRAM, 0);		// MAKE UDP SOCKET

	printf("%d\n", fdes1);
	printf("%d\n", fdes2);
	printf("%d\n", fdes3);

	close(fdes1);
	close(fdes2);
	close(fdes3);

	return 0;
}
