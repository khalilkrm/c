#define _XOPEN_SOURCE 1
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semadd.h"
#define SEMKEY 11209
#define SHMKEY 19309
int main(void)
{ 	
	/*DECLARATION DES ATTRIBUTS NECESAIRES*/
	int shmid, i, sem, *mem1, *mem2;
	
	/*UNION SERVANT A INITIALISER LA VALEUR DU SEMAPHORE*/
	union semun init;
	
	/*AFFECTATION DE LA VALEUR 1 AU SEMAPHORE*/
	init.val = 1;	

	/*ALLOCATION D'UNE ZONE MEMOIRE PARTAGEE*/
	shmid = shmget(SHMKEY, 2*sizeof(int), 0666|IPC_CREAT);
	
	/*ALLOCATION D'UN SEMAPHORE*/
	sem = sem_transf(SEMKEY);
	
	/*AFFECTATION DE LA VALEUR DU SEMAPHORE SUR BASE DE 
	L'INSTRUCTION inti.val PRECEDENTE*/
	semctl(sem, 0, SETVAL, init);
		
	/*INITIALISATION DES MEMOIRE AVEC UN POINTEUR VERS UN ENTIER*/
	mem1 = (int*) shmat(shmid, 0, 0);

	/*ARITHMETIQUE DE POINTEUR, ETANT DONNEE QUE LA TAILLE D'UN ENTIER EST 
	32 BITS ET Q'UN LA TAILE DE MA ZONE MEMOIRE EST 2*INT JE PLACE DONC mem2 APRES mem1*/
	mem2 = mem1+1;

	/*INITIALISATION DES POINTEUR*/
	(*mem1) = 10;
	(*mem2) = 10;
	
	/*LE PERE ET LE FILS FONT LES OPERATION INVERSE - INCREMENTATION ET DECREMENTATION -
	A LA FIN JE DEVRAIT DONC AVOIR LES MEME VALEUR QU'AU DEPART*/
	switch(fork())
	{ 
		case -1: printf("Erreur Fork\n"); exit(-1);
		case 0:
			for(i=0;i<5; ++i)
			{	p(sem);
				(*mem1) = (*mem1)-1;
				(*mem2) = (*mem2)+1;
				printf("[FILS] mem1=%d, mem2=%d\n", (*mem1), (*mem2));
				v(sem);
			} shmdt(mem1); exit(0);
		default:
			for(i=0;i<5; ++i)
			{	p(sem);
				(*mem1) = (*mem1)+1; 
				(*mem2) = (*mem2)-1;
				printf("[PERE] mem1=%d, mem2=%d\n", (*mem1), (*mem2));
				v(sem);
			} break;
	}
	wait(NULL);
	printf("Valeurs: mem1=%d, mem2=%d\n", *mem1, *mem2);
	shmdt(mem1); 
	shmctl(shmid, IPC_RMID, NULL);
	semctl(sem, 0, IPC_RMID, NULL);
	return EXIT_SUCCESS;
}
