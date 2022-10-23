#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define TAILLE_BUFFER 255
#define LECTURE 0
#define ECRITURE 1
#define NB_DESCRIPTEUR 2
int main(void)
{
	int tube[NB_DESCRIPTEUR];
	char buffer[TAILLE_BUFFER+1];
	pipe(tube);
	switch(fork())
	{ 
	case -1 : printf("Erreur fork()\n"); exit(-1);
	case 0 : 
		close(tube[ECRITURE]);
		read(tube[LECTURE], buffer, TAILLE_BUFFER);
		
		close(tube[LECTURE]);
		printf("Message : %s", buffer);
		break;
	default:
		
		write(tube[ECRITURE], buffer, TAILLE_BUFFER);
		
		close(tube[LECTURE]);
		close(tube[ECRITURE]);
		
		printf("Un petit message envoye\n"); fflush(stdout);
		
		wait(NULL);
		break;
	}
	return EXIT_SUCCESS;
}
