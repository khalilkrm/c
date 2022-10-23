#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


void* encodage(void* arg)
{
	char chaine[60+1];
	int *taille = malloc(sizeof(int));

	printf("Entrez une chaîne de caractère : ");
	scanf("%60[^\n]%*c", chaine);
	
	*(taille) = strlen(chaine);
	
	pthread_exit(taille);
}


int main(void)
{
	pthread_t th_id;
	int ret;
	void *compteur;
	
	/*On travail avec une donnée partagée*/
	ret = pthread_create(&th_id, NULL, encodage, NULL);
	
	if(ret != 0)
	{ printf("Erreur creation thread\n"); exit(-1); }
	
	pthread_join(th_id, &compteur);
	
	printf("Thread %d est mort. Compteur = %d", ((int)th_id), *((int *)compteur));
	
	free(compteur);
	return EXIT_SUCCESS;
}

