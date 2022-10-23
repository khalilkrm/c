union semun {
   int val;                    
   struct semid_ds *buf;       
   unsigned short int *array;  
   struct seminfo *__buf;      
};

int sem_transf(int key);
int semcall(int sid, int op);
void p(int sem);
void v(int sem);

