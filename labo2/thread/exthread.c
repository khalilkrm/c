#include "info-thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *incrementer(void *arg) {

		

}

void *afficher (void *arg) {

	(*(info-struct)arg)->initial_value;

}


int main() {
	
	struct info-struct struct_th1;
	struct info-struct struct_th2;
	struct info-struct struct_th3;

	pthread_t th1_id;
	pthread_t th2_id;
	pthread_t th3_id;

	int ret1, ret2, ret3;
	
	ret1 = pthread_create(&th1_id, NULL, incrementer, &struct_th1);
	ret2 = pthread_create(&th2_id, NULL, incrementer, &struct_th2);
	ret3 = pthread_create(&th3_id, NULL, incrementer, &struct_th3);
	
	if(ret1 != 0 || ret2 != 0 || ret3 != 0)
	{
		prinft("Erreur creation thread\n");
		exit(-1);
	}

	pthread_join(th1_id, NULL);
	pthread_join(th2_id, NULL);
	pthread_join(th3_id, NULL);

}
