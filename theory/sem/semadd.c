/* Routine pour faciliter l'utilisation des semaphores */
#define _XOPEN_SOURCE 1
#include "semadd.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int sem_transf(int key)
{
	int sid;
	if((sid=semget(key,1,0666|IPC_CREAT))==-1)
	{
		puts("Erreur semget"); exit(-1);
	}
	return(sid);
} /* convertit une clef en semaphore */

int semcall(int sid, int op)
{
	struct sembuf sb; sb.sem_num=0; sb.sem_op = op;
	sb.sem_flg = 0; /* WAIT par dzfaut */
	if(semop(sid, &sb,1) == -1)
	{
		puts("Erreur semop"); exit(-2);
	}
	return 0;
}

void p(int sem)
{
	semcall(sem, -1);
}

void v(int sem)
{
	semcall(sem, 1);
}

