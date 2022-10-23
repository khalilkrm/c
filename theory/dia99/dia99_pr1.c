#define _XOPEN_SOURCE 1
#define SEMKEY1 21394
#define SEMKEY2 21395

#include "semadd.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(void)
{
	int sem1, sem2;
	sem1 = sem_transf(SEMKEY1);
	sem2 = sem_transf(SEMKEY2);
	printf("Le programme 1 s’exécute ...\n");
	printf("Le programme 1 passe en pause ...\n");
	v(sem2);
	p(sem1);	
	printf("Le programme 1 reprend ...\n");
	v(sem2);
	sleep(5);
	printf("Libération des ressources ...\n");
	semctl(sem1, 0, IPC_RMID, NULL);
	semctl(sem2, 0, IPC_RMID, NULL);
	return EXIT_SUCCESS;
}
