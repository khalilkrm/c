#define _XOPEN_SOURCE 1
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../sem/semadd.h"
#include "struct.h"
#define SEMKEY 11209
#define SHMKEY 19309

int menu()
{
	int choix = 0;
	printf("\n» 1. Encoder un article\n» 2. Visualiser tous les articles\n» 3. Libérer les ressources et quitter\n» 4. Quitter\nVotre choix : ");
	
	do {
		scanf("%d%*c", &choix);
	}while(choix > 4 || choix < 1);

	return choix;
}

struct un_article encoder_un_article(void)
{	
	struct un_article tmp_article;
	printf("\nEntrez un description du produit : ");
        scanf("%50[^\n]%*c", tmp_article.description);
	
        printf("Entrez le prix de l'article : ");
        scanf("%f%*c", &tmp_article.prix);
	
	return tmp_article;
}

void enregistrer_article(struct stock *ptr_stock, struct un_article nouvel_article)
{
	ptr_stock->articles[ptr_stock->nombre_article++] = nouvel_article;
}

void afficher_articles(struct stock *current_stock)
{
	int i;
	
	printf("\n%d article(s) dans le stock\n", current_stock->nombre_article);	

	for(i = 0; i < current_stock->nombre_article; i++)
	{
		
		printf("\t%d :\tdescription: %s\tprix: %f\n", i+1, current_stock->articles[i].description, current_stock->articles[i].prix);
		
	}
}

int main(void)
{
	/*DECLARATION DES ATTRIBUTS NECESSAIRES AU DOMAINE*/	
	int choix;
	struct un_article tmp_article;
	/*DECLARATION DES ATTRIBUTS NECESSAIRES AU MEMOIRE PARTAGEE*/
	int shmid;
	struct stock *ptr_stock;

	/*DECLARATION DES ATTRIBUTS NECESSAIRES AU SEMAPHORES*/
	int sem;
	union semun init;

	/*ALLOCATION DE LA MEMOIRE PARTAGEE*/
	shmid = shmget(SHMKEY, sizeof(struct stock), 0666);
	if(shmid < 0) { shmid = shmget(SHMKEY, sizeof(struct stock), 0666|IPC_CREAT); }
	if(shmid < 0) { printf("Erreur SHM\n");  exit(-1);}

	/*INITIALISATION DU POINTEUR*/
	ptr_stock = (struct stock *) shmat(shmid, NULL, 0);
	
	/*INITIALISATION DU SEMAPHORE*/
	sem = semget(SEMKEY, 1, 0666);
	if(sem < 0)
	{
                /*ALLOCATION DU SEMAPHORE*/
                sem = sem_transf(SEMKEY);
                /*INITIALISATION DE LA VALEUR DU SEMAPHORE POUR INTRODUIRE LE MECANISME D'EXCLUSION MUTUELLE*/
                init.val = 1;
                semctl(sem, 0, SETVAL, init);
                /*INITIALISATION DU NOMBRE D'ARTICLE A 0*/
                ptr_stock->nombre_article = 0;
	}

	do{
		choix = menu();	
		switch(choix)
		{
			case 1: {
				tmp_article = encoder_un_article();
				p(sem);
				enregistrer_article(ptr_stock, tmp_article);
				v(sem);
				break;
			}
			case 2: {
				p(sem);
				afficher_articles(ptr_stock);
				v(sem);
				break;
			}
			case 3: {
				shmdt(ptr_stock);
				shmctl(shmid, IPC_RMID, NULL);
			        semctl(sem, 0, IPC_RMID, NULL);
				exit(0);
			}
			case 4: {
				shmdt(ptr_stock);
				exit(0);
			}
			default : printf("Action non reconnu !");
		}
	}while(choix < 3);
	
	shmdt(ptr_stock);
	shmctl(shmid, IPC_RMID, NULL);
	semctl(sem, 0, IPC_RMID, NULL);
	return EXIT_SUCCESS;
}
