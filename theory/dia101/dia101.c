#define _XOPEN_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"
#include "semadd.h"

#define SHM_KEY 2324
#define SEM_KEY_1 21394
#define SEM_KEY_2 21395
#define SIZE 1024

int main(void)
{

	pid_t pid;
	
	/*DECLARATION DES ATTRIBUT NECESSAIRES*/
	int shmid;
	struct operation *ptr_operation;	

	/*UN SEMAPHORE POUR LE PERE ET LE FILS, POUR TRAITER LE CAS OU LE PERE EST
	EN PAUSE ET LE CAS OU LE FILS EST EN PAUSE*/
	int sem1, sem2;

	/*ALLOCATION DE LA MEMOIRE PARTAGEE | RETOURNE UN DESCRIPTEUR EN 777 R/W*/
	shmid = shmget(SHM_KEY, sizeof(struct operation), 0777|IPC_CREAT);
	if(shmid < 0) {printf("Erreur allocation SHM\n"); exit(-1);}	
	
	/*RETOURNE LE POINTEUR VERS LA MEMOIRE QUE JE CASTE AVEC LE TYPE A STOCKER*/
	ptr_operation = (struct operation *) shmat(shmid, NULL, 0);	

	/*ALLOCATION D'UN SEMAPHORE*/
	sem1 = sem_transf(SEM_KEY_1);
	sem2 = sem_transf(SEM_KEY_2);
	if(sem1 < 0 || sem2 < 0){printf("Erreur allocation SEM\n"); exit(-2);}	

	switch((pid = fork()))
	{
		case -1: printf("Erreur fork()\n"); exit(-1);
		case 0: 
			{
				/*FILS*/

				/*ATTENDRE QUE LE PERE ECRIVE L'OPERATION*/
                                p(sem1);
				/*signal(SIGUSR1, ttt);*/
                  		/*pause();*/
				
				/*EFFECTUER L'OPERATION*/
				switch(ptr_operation->signe)
				{	
					case '+' : ptr_operation->resultat = (ptr_operation->operande_gauche + ptr_operation->operande_droite); break;
					case '-' : ptr_operation->resultat = (ptr_operation->operande_gauche - ptr_operation->operande_droite); break;
					case '/' : ptr_operation->resultat = (ptr_operation->operande_gauche / ptr_operation->operande_droite); break;
					case '*' : ptr_operation->resultat = (ptr_operation->operande_gauche * ptr_operation->operande_droite); break;
				}

				/*PREVENIR LE PERE QUE L'OPERATION A ETE EFFECRTUE*/
				v(sem2);
				/*kill(getppid(), SIGUSR2);*/
				
				/*DETACHEMENT DE LA ZONE DE MEMOIRE PARTAGEE*/	
				shmdt(ptr_operation);
				
				break;
			}
		default:
			{
				/*PERE*/
				/*signal(SIGUSR2, ttt);*/
				
				/*DEMANDE A L'UTILISATEUR L'OPERATION*/
				printf("Entrez une operation: ");
				scanf("%d %c %d", &ptr_operation->operande_gauche, &ptr_operation->signe, &ptr_operation->operande_droite);
				
				/*PREVENIR LE FILS QUE L'OPERATION A ETE ECRITE*/
				/*kill(pid, SIGUSR1);*/
				v(sem1);
				
				/*ATTENDRE QUE LE FILS EFFECTUE L'OPERATION*/
				/*pause();*/
				p(sem2);
				
				printf("%d %c %d = %u\n", ptr_operation->operande_gauche, ptr_operation->signe, ptr_operation->operande_droite, ptr_operation->resultat);
				
				/*CLOSE MEMORY*/
                                shmdt(ptr_operation);
				
				/*DESTRUCTION DE LA ZONE DE MEMORIE PARTAGEE*/
				shmctl(shmid, IPC_RMID, NULL);
				
				/*DESTRUCTION DE LA SEMAPHORE*/
				semctl(sem1, 0, IPC_RMID, NULL);
				semctl(sem2, 0, IPC_RMID, NULL);
				
				break;
			}
	}
	return EXIT_SUCCESS;
}
