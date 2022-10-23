#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int n, handle; char buf[255];
	handle = open("tube", O_RDONLY);
	n = read(handle, buf, 255); buf[n]='\0';
	close(handle);
	printf("%d octets lus. Contenu: '%s'\n", n, buf);
	return EXIT_SUCCESS;
}
