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
	/*Permet de de lire est écrire, 
	on en crée deux pour bien montrer que les buffers 
	sont bien différents pour chaque processus, 
	les processus ne communique donc pas à travers le buffer,
	mais bien grâce au tube et au méthode read et write*/

	pipe(tube);

	switch(fork()) 
	{ 
		case -1:
			printf("Erreur fork()\n");
			exit(-1); 
		case 0: {
				/*On lit ce qu'il y a dans le tube, l'opération est blocante tant que le père n'a rien écris dans ce même tube*/
				if(read(tube[READ], READ_BUFFER, MAX_SIZE) > 0)
					printf("Message: %s\n", READ_BUFFER);
				else 
					printf("Message vide\n");
				break;
			}
		default:
			{
				strncpy(WRITE_BUFFER,MESSAGE,strlen(MESSAGE)+1);
				/*On ecrit dans le buffer, ce buffer est independant du fils, le contenue du buffer va dans le tube et le fils lit le tube et non le buffer*/
				write(tube[WRITE], WRITE_BUFFER, strlen(WRITE_BUFFER));
				/*On attend que le fils ait terminé, car si il n'y a plus personne ici alors read peut retourner 0 car il y'aura plus personne pour écrire*/
				wait(NULL);
				close(tube[READ]);
				close(tube[WRITE]);
				break;
			}
	}

	return EXIT_SUCCESS;
}
