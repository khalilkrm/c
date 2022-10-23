#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(void)
{
 pid_t pid;
 switch(pid = fork())
 {
  case -1: printf("Erreur fork()\n");
  exit(-1);
  case 0: sleep(10);
  printf("Je suis le nouveau né %u. PID de papa %u\n",
  getpid(), getppid());
  break;
  default: printf("J'ai créé le fils %u\n", pid);
 }
 return EXIT_SUCCESS;
}
