#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{ 
	int nb, fd; char *buffer = "Hello";
	mkfifo("tube", 0777);
	fd = open("tube", O_WRONLY);
	nb = write(fd, buffer, strlen(buffer));
	printf("%d octets écrits. Contenu: '%s'\n", nb, buffer);
	close(fd);
	return EXIT_SUCCESS;
}


