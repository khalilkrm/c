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
               /* printf("Le caractère '%c' a été trouvé à la position %d\n", characterToLookFor, indexOfFoundCharacter);*/
        }

       /*printf("Nombre d'occurence du caractère '%c' est de %d\n", characterToLookFor, totalCharacterToLookForFound);*/
	return totalCharacterToLookForFound;
}


int main()
{
	
	int tube;
	
	char *TUBE_NAME = "tube";
	
	char BUFFER_READ[BUFFER_SIZE];
	char BUFFER_WRITE[BUFFER_SIZE];

	char BUFFER_WRITE_COUNT[BUFFER_SIZE];
	char BUFFER_READ_COUNT[BUFFER_SIZE];

	int WRITTEN_SIZE, READ_SIZE, WRITTEN_SIZE_COUNT, READ_SIZE_COUNT;

	mkfifo("tube", 0777);

	switch(fork())
	{
		case -1: printf("Erreur fork()\n"); exit(-1);
		case 0:
		{	
			tube = open(TUBE_NAME, O_WRONLY);
			close(1);
			dup(tube);
			printf("%[^\n]%*c", MESSAGE);
			close(tube);
			/*WRITTEN_SIZE = write(tube, MESSAGE, strlen(MESSAGE));*/
			tube = open(TUBE_NAME, O_RDONLY);
			READ_SIZE_COUNT = read(tube, BUFFER_READ_COUNT, BUFFER_SIZE);
			printf("Compte : %s\n", BUFFER_READ_COUNT);
			close(tube);
			exit(0);
		}
	}

        switch(fork())
        {

                case -1: printf("Erreur fork()\n"); exit(-1);
                case 0: 
		{	
		 	tube = open(TUBE_NAME, O_RDONLY);
			/*READ_SIZE = read(tube, BUFFER_READ, strlen(MESSAGE) + 1); BUFFER_READ[READ_SIZE] = '\0';*/
			printf("Avant traitement: %s\n", BUFFER_READ);
			close(tube);
			tube = open(TUBE_NAME, O_WRONLY);
			sprintf(BUFFER_WRITE_COUNT, "'e': %d, 'a': %d", count(MESSAGE, 'e'), count(MESSAGE, 'a'));
			WRITTEN_SIZE_COUNT = write(tube, BUFFER_WRITE_COUNT, BUFFER_SIZE);
			close(tube);
			break;
		}
        }

	close(tube);
	wait(NULL);
	wait(NULL);
	return EXIT_SUCCESS;

}
