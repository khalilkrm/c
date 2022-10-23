#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 255

int index_of(char *string, char toSearch)
{
	char *found = strchr(string, toSearch); 
	return found - string;	
}


int main(void)
{	
	/*DECLARATION DES ATTRIBUTS NECESSAIRES*/
	int i, initialPos, newPos;
	char cryptedChar;
	char toCrypt[BUFFER_SIZE], crypted[BUFFER_SIZE];
	char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	/*INTERACTION UTILISATEUR*/
	printf("Enter a string to crypt : ");
	scanf("%255[^\n]%*c", toCrypt);
	
	/*CRYPTAGE*/
	for(i = 0; toCrypt[i]; i++)
	{
	
		initialPos = index_of(alphabet, toCrypt[i]) % 25;
		if(sizeof(int) == sizeof(initialPos)) 
		{
			if((initialPos+3)>25) newPos = (initialPos + 2) % 25;
			else newPos = initialPos+3;
			cryptedChar = alphabet[newPos];
			crypted[i] = cryptedChar;	
		}else crypted[i] = toCrypt[i];
	
	}
	
	crypted[i] = '\0';

	/*AFFICHAGE DE LA STRING CRYPTEE*/
	printf("%s", crypted);

	return EXIT_SUCCESS;
}
