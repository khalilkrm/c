#define _XOPEN_SOURCE 1

#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>

#define SHM_KEY 2324
#define K 1024

int main(void)
{ 
	int shmid; char* ptr;
	shmid = shmget(SHM_KEY, K, 0777|IPC_CREAT);
	ptr = shmat(shmid,NULL,0);
	strncpy(ptr, "Hello !\n", 9);
	shmdt(ptr);
	return EXIT_SUCCESS;
}
