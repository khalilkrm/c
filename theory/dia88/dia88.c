#define _XOPEN_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "struct.h"

#define SHM_KEY 2324 
#define SIZE 1024

void ttt() {}

int main(void)
{

	pid_t pid;
	
	/*DECLARATION DES ATTRIBUT NECESSAIRES*/
	int shmid;
	struct operation *ptr_operation;	

	/*ALLOCATION DE LA MEMOIRE PARTAGEE | RETOURNE UN DESCRIPTEUR EN 777 R/W*/
	shmid = shmget(SHM_KEY, sizeof(struct operation), 0777|IPC_CREAT);
	
	/*RETOURNE LE POINTEUR VERS LA MEMOIRE QUE JE CASTE AVEC LE TYPE A STOCKER*/
	ptr_operation = (struct operation *) shmat(shmid, NULL, 0);	

	switch((pid = fork()))
	{
		case -1: printf("Erreur fork()\n"); exit(-1);
		case 0: 
			{
				/*FILS*/

				/*ATTENDRE QUE LE PERE ECRIVE L'OPERATION*/
                                signal(SIGUSR1, ttt);
                                pause();
				
				/*EFFECTUER L'OPERATION*/
				switch(ptr_operation->signe)
				{	
					case '+' : ptr_operation->resultat = (ptr_operation->operande_gauche + ptr_operation->operande_droite); break;
					case '-' : ptr_operation->resultat = (ptr_operation->operande_gauche - ptr_operation->operande_droite); break;
					case '/' : ptr_operation->resultat = (ptr_operation->operande_gauche / ptr_operation->operande_droite); break;
					case '*' : ptr_operation->resultat = (ptr_operation->operande_gauche * ptr_operation->operande_droite); break;
				}
				
				/*PREVENIR LE PERE QUE L'OPERATION A ETE EFFECRTUE*/
				kill(getppid(), SIGUSR2);

				shmdt(ptr_operation);
				break;
			}
		default:
			{
				/*PERE*/
				signal(SIGUSR2, ttt);

				/*DEMANDE A L'UTILISATEUR L'OPERATION*/
				printf("Entrez une operation: ");
				scanf("%d %c %d", &ptr_operation->operande_gauche, &ptr_operation->signe, &ptr_operation->operande_droite);
		
				/*PREVENIR LE FILS QUE L'OPERATION A ETE ECRITE*/
				kill(pid, SIGUSR1);
				
				/*ATTENDRE QUE LE FILS EFFECTUE L'OPERATION*/
				pause();

				printf("%d %c %d = %u\n", ptr_operation->operande_gauche, ptr_operation->signe, ptr_operation->operande_droite, ptr_operation->resultat);
				
				/*CLOSE MEMORY*/
                                shmdt(ptr_operation);

				shmctl(shmid, IPC_RMID, NULL);
				break;
			}
	}
	
	
	return EXIT_SUCCESS;
}
