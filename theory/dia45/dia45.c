#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define INPUT_LENGHT 255

int main(void) {
	pid_t ret;
	char input[INPUT_LENGHT+1];
	int traveler_data;
	
	switch((ret = fork()))
	{
		case -1 :
			printf("Erreur fork()\n");
			exit(-1);
			break;
		case 0 :
			printf("Je suis le fils: %i\n", getpid());
			printf("Entrez une chaine de caractère\n");
			scanf("%255[^\n]%*c", input);
			exit(strlen(input));
		default :
			waitpid(ret, &traveler_data, 0);
			printf("Enfant %i mort. Compteur %i\n", ret, WEXITSTATUS(traveler_data));
			
	}
	
	return EXIT_SUCCESS;
}
