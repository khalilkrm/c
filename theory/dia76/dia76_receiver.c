#define _XOPEN_SOURCE 1

#include <stdio.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 2324
#define K 1024

int main(void)
{
	int shmid; char* ptr;
	shmid = shmget(SHM_KEY, K, 0777);
	if(shmid < 0) 
	{
		printf("Erreur SHM\n");
		exit(-1);
	}
	ptr = shmat(shmid,NULL,0);
	printf("Contenu : %s\n",ptr);
	shmdt(ptr);
	shmctl(shmid, IPC_RMID, NULL);
	return EXIT_SUCCESS;
}
