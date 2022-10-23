#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_SIZE 255
#define MESSAGE "salut à toi"

#include "../helpers/tube.h"

int main(void)
{ 
	int tube[2];
	pipe(tube);
	switch(fork())
	{
		case -1:
			 printf("Erreur fork()\n"); exit(-1);
		case 0: {

			replace_standard_input(tube);
			scanf("%255[^\n]%*c", READ_BUFFER);
			fflush(stdout);
			printf("Message: %s\n", READ_BUFFER);  
			break;
			}
		default:{
			strncpy(WRITE_BUFFER, MESSAGE, strlen(MESSAGE)+1);
			replace_standard_output(tube);
			printf("%s\n", WRITE_BUFFER); fflush(stdout);
			wait(NULL);
			break;
			}
	}
	return EXIT_SUCCESS;
}
