#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


void* encodage(void* arg)
{
	char chaine[60+1];
	printf("Entrez une chaîne de caractère : ");
	scanf("%60[^\n]%*c", chaine);
	*((int*) arg) = strlen(chaine);
	/*NULL car on ne retourne rien, on veut juste quitter le thread*/
	pthread_exit(NULL);
}

/*Les threads partagent la même mémoire, cette version utilise ce mécanisme en passant une adresse  à la fonction devant être exécuté par le thread*/
int main(void)
{
	pthread_t th_id;
	int ret;
	int compteur;
	
	/*On travail avec une donnée partagée - compteur*/
	ret = pthread_create(&th_id, NULL, encodage, &compteur);
	
	if(ret != 0)
	{ printf("Erreur creation thread\n"); exit(-1); }
	
	/*On ne retourne rien, donc pas besoin de récuperer,
	 c'est pour cela qu'on met NULL.
	Cette méthode permet également d'attendre la mort d'un thread*/
	pthread_join(th_id, NULL);
	
	printf("Thread %d est mort. Compteur = %d", th_id, compteur);

	return EXIT_SUCCESS;
}

