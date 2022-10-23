#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{ 	int pid;
	printf("Entrez le PID du processus :"); 
	scanf("%d",&pid);
	kill(pid, SIGUSR1);
	return EXIT_SUCCESS;
}
