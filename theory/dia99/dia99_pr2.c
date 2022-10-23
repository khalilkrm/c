#define _XOPEN_SOURCE 1
#define SEMKEY1 21394
#define SEMKEY2 21395

#include "semadd.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(void)
{ 
	int sem1, sem2;
	sem1 = semget(SEMKEY1, 1, 0666);
	sem2 = semget(SEMKEY2, 1, 0666);
	if(sem1 < 0 || sem2 < 0)
	{ printf("Le programme 1 n’est pas démarré\n");exit(-1); }
	printf("Le programme 2 passe en pause ...\n");
	p(sem2);
	printf("Le programme 2 reprend ...\n");
	v(sem1);
	p(sem2);
	printf("Le programme 2 quitte ...\n");
	return EXIT_SUCCESS;
}
