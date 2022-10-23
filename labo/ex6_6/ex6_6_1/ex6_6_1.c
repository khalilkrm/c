#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 255

int main(void) 
{	
	/*DECLARATION DES VARIABLES NECESSAIRES*/
	char characterToLookFor;
	int indexOfFoundCharacter;
	char *characterFound;
	char stringToSearchIn[BUFFER_SIZE];
	char *pointerToStringToSearchIn = &stringToSearchIn[0];
	int totalCharacterToLookForFound;
	
	/*DEMANDE DE CHAINE DE CARACTERE*/	
	printf("Entrez une chaîne de caractère : ");
	scanf("%255[^\n]%*c", stringToSearchIn);
	
	/*DEMANDE DU CARACTERE A TROUVER*/
	printf("Entrez le caractère à trouver :");
	scanf("%c%*c", &characterToLookFor);
	
	totalCharacterToLookForFound = 0;
	
	while((characterFound = strchr(pointerToStringToSearchIn, characterToLookFor)) != NULL)
        {
                indexOfFoundCharacter = (characterFound - stringToSearchIn);
                pointerToStringToSearchIn = &stringToSearchIn[indexOfFoundCharacter+1];
                totalCharacterToLookForFound++;
                printf("Le caractère '%c' a été trouvé à la position %d\n", characterToLookFor, indexOfFoundCharacter);
        }

	printf("Nombre d'occurence du caractère '%c' est de %d\n", characterToLookFor, totalCharacterToLookForFound);
	return EXIT_SUCCESS;
}
