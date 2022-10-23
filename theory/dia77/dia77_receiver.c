
#define _XOPEN_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include "dog.h"

#define SHM_KEY 2324
#define SIZE 1024

int main(void)
{

        /*LIT UNE STRUCTURE EN MEMOIRE PARTAGEE*/

        /*DECLARATION DES ATTRIBUTS*/
        int shmid;
        struct dog *ptr_strike;

        /*ALLOCATION DE LA MEMOIRE PARTAGEE*/
        shmid = shmget(SHM_KEY, SIZE, 777);
			
	if(shmid < 0)
	{
		printf("Erreur SHM\n");
		exit(-1);
	}

        /*ACCESS A LA MEMOIRE PARTAGEE*/
        ptr_strike = (struct dog *) shmat(shmid, NULL, 0);

        /*LECTURE ET AFFICHAGE DE LA STRUCTURE EN MEMOIRE*/
	printf("%c\n", ptr_strike->initial);
	printf("%i\n", ptr_strike->id);
	printf("%i\n", ptr_strike->age);

        /*FERMETURE DE LA MEMOIRE*/
        shmdt(ptr_strike);

	/*DESTRUCTION DE LA ZONE MEMOIRE*/
	shmctl(shmid, IPC_RMID, NULL);

        return EXIT_SUCCESS;
}

