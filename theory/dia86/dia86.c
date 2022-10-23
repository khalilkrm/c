#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void traitement_alarme (int signum)
{  printf("Signal SIGALRM reçu\n"); }

int main(void)
{
	printf("Avant l'alarme ...\n");
	signal(SIGALRM, traitement_alarme);
	alarm(10);
	pause();
	printf("Après l'alarme ...\n");
	return EXIT_SUCCESS;
}
