#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_SIZE 255
#include "../helpers/tube.h"


int main(void)
{
	int pid;
	int tube[2];
	/*ALLOCATION DES TUBE, AFFECTATION DES DESCRIPTEURS DE LECTURE/ECRITURE*/
	pipe(tube);
	
	/*PREMIER ENFANT*/
	
	switch((pid = fork()))
	{
		case -1: 
			printf("Erreur fork()\n");
			exit(-1);
		case 0: 
			/*FILS, ECRITURE DU RESTULTAT DE LS DANS LE PIPE*/
			/*FERMETURE DU TUBE D'ENTREE STANDARD*/	
			close(WRITE);
			/*AFFECTATION DU TUBE DECRITURE EN REMPLACEMENT DE CELUI FERMEE CI-DESSUS*/
			dup(tube[WRITE]);
			/*FERMETURE DES TUBES APRES LEUR COPIE*/
			close(tube[WRITE]);
			close(tube[READ]);
			/*EXECUTION DE LA COMMANDE LS, QUI DEVRAIT ENVOYER SON RESULTAT DANS LE TUBE DE SORTIE*/
			if(execl("/usr/bin/ls", "/usr/bin/ls", NULL))
			{
				printf("Erreur execl() LS\n"); exit(-3);
			}
	}
	
	/*DEUXIEME ENFANT*/

	 switch((pid = fork()))
        {
                case -1:
                        printf("Erreur fork()\n");
                        exit(-2);
                case 0:
                        /*FILS, LECTURE DU RESTULTAT DE LS DANS LE PIPE*/
                        /*FERMETURE DU TUBE DE LECTURE STANDARD*/
                        close(READ);
                        /*AFFECTATION DU TUBE DE LECTURE EN REMPLACEMENT DE CELUI FERMEE CI-DESSUS*/
                        dup(tube[READ]);
                        /*FERMETURE DES TUBES APRES LEUR COPIE*/
                        close(tube[WRITE]);
                        close(tube[READ]);
                        /*EXECUTION DE LA COMMANDE LS, QUI DEVRAIT ENVOYER SON RESULTAT DANS LE TUBE DE SORTIE*/
			/*NOTEZ QUE EXECL LIT CE QU'IL Y A SUR LE PIPE DE LECTURE PAR DEFAUT*/
                        if(execl("/usr/bin/wc", "/usr/bin/wc", NULL))
			{
				printf("Erreur execl() WC\n"); exit(-4);				
			}
			
        }
	
	/*FERMETURE DES TUBE DU COTE PERE, SINON LE PROCESSUS NE COMPRED PAS LA L'UTILISATION DESIRE DES TUBES ET BLOQUE*/
	close(tube[READ]);
	close(tube[WRITE]);	
	wait(NULL);
	wait(NULL);
	return EXIT_SUCCESS;
}
