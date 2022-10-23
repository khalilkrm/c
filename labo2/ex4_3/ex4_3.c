#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>

#define BUFFER_SIZE 255
#define MESSAGE "La seule limite à notre épanouissement de demain sera nos doutes d’aujourd’hui - Franklin Delano Roosevelt"
#define SORTIE 1
#define ENTREE 0

int count(char stringToSearchIn[BUFFER_SIZE], char characterToLookFor)
{
        /*DECLARATION DES VARIABLES NECESSAIRES*/
        int indexOfFoundCharacter;
        char *characterFound;
        char *pointerToStringToSearchIn = &stringToSearchIn[0];
        int totalCharacterToLookForFound;

        /*DEMANDE DU CARACTERE A TROUVER*/

        totalCharacterToLookForFound = 0;

        while((characterFound = strchr(pointerToStringToSearchIn, characterToLookFor)) != NULL)
        {
                indexOfFoundCharacter = (characterFound - stringToSearchIn);
                pointerToStringToSearchIn = &stringToSearchIn[indexOfFoundCharacter+1];
                totalCharacterToLookForFound++;
        }

        return totalCharacterToLookForFound;
}

int main()
{

        int tube[2];
	char BUFFER_READ[BUFFER_SIZE];
	char BUFFER_READ_1[BUFFER_SIZE];
	char BUFFER_WRITE[BUFFER_SIZE];

	pipe(tube);

        switch(fork())
        {
                case -1: printf("Erreur fork()\n"); exit(-1);
                case 0:
                {
			/*DOIT ECRIRE DANS LE TUBE GRACE A PRINTF*/
			close(SORTIE); close(tube[ENTREE]);
			dup(tube[SORTIE]);
			close(tube[SORTIE]);
			printf("%s\n", MESSAGE);
			fflush(stdout);
			/*DOIT LIRE LE TUBE*/
			close(ENTREE);
			dup(tube[ENTREE]);
			close(tube[ENTREE]);
			scanf("%[^\n]%*c", BUFFER_READ_1);
			printf("%s\n", BUFFER_READ_1);
                }
        }

        switch(fork())
        {

                case -1: printf("Erreur fork()\n"); exit(-1);
                case 0:
 		{
                
			/*DOIT LIRE LE TUBE AVEC SCANF*/
			close(ENTREE); close(tube[SORTIE]);
			dup(tube[ENTREE]);
			close(tube[ENTREE]);
			scanf("%[^[\n]%*c]", BUFFER_READ);
			printf("MESSAGE RECU: %s\n", BUFFER_READ);
			/*DOIT ECRIRE DANS LE TUBE*/
			close(SORTIE);
			dup(tube[SORTIE]);
			close(tube[SORTIE]);
			sprintf(BUFFER_WRITE, "'e': %d, 'a': %d", count(MESSAGE, 'e'), count(MESSAGE, 'a'));
			printf("%s\n", BUFFER_WRITE); fflush(stdout);
		}
        }
		
	close(tube[SORTIE]);
	close(tube[ENTREE]);
        wait(NULL);
        wait(NULL);
        return EXIT_SUCCESS;

}

