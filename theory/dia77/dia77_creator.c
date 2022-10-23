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
	
	/*REMPLIT UNE STRUCTURE EN MEMOIRE PARTAGEE*/

	/*DECLARATION DES ATTRIBUTS NECESSAIRES*/
	int shmid;
	struct dog strike;
	struct dog *ptr_strike;	
		
	/*	PREPARATION DE LA STRUCTURE	*/

	/*ECRITURE DANS STRUCTURE A ENVOYER*/
        strike.initial = 'S';
        strike.id = 11;
        strike.age = 5;

	/*	MEMOIRE:CREATION ET ACCES	*/

	/*ALLOCATION DE LA MEMOIRE PARTAGEE | RETOURNE UN DESCRIPTEUR EN 777 R/W*/
	shmid = shmget(SHM_KEY, SIZE, 777|IPC_CREAT);
	
	/*RETOURNE LE POINTEUR VERS LA MEMOIRE QUE JE CASTE AVEC LE TYPE A STOCKER*/
	ptr_strike = (struct dog *) shmat(shmid, NULL, 0);
	
	/*	MEMOIRE:AFFECTATION DE LA STRUCTURE ET FERMETURE	*/
	
	/*COPIE DE LA STRUCTURE DANS LA MEMOIRE*/
	memcpy(ptr_strike, &strike, 2*sizeof(int)+ sizeof(char));
	
	/*CLOSE MEMORY*/
	shmdt(ptr_strike);
	
	return EXIT_SUCCESS;
}
