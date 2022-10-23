#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void traitement_signal (int signum)
{ printf("Signal SIGUSR1 reçu\n"); }

int main(void)
{ 
	signal(SIGUSR1, traitement_signal);
	printf("Mon PID=%d\n",getpid());
	pause();
	return EXIT_SUCCESS;
}
