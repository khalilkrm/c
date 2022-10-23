#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int random_number(int min, int max) 
{
	return  (rand() % (max - min + 1)) + min;
}

void generate_password(char password[10+1])
{	
	int i;

	int intsThresholds[] = {48, 57};
        int majThresholds[] = {65, 90};
        int minThresholds[] = {97, 122};
	
	for(i = 0; i < 10; i++)
	{

		switch(random_number(1,3))
		{

			case 1: {
					password[i] = (char)random_number(intsThresholds[0], intsThresholds[1]);
					break;
				}
			case 2: 
				{
					password[i] = (char)random_number(majThresholds[0], majThresholds[1]);
					break;
				}
			case 3: 
				{
					password[i] = (char)random_number(minThresholds[0], minThresholds[1]);
					break;
				}
			default: printf("Erreur when chosing the thresholds"); exit(-1);
		}

	}
}

int main(void)
{	
	char password[10+1];
	srand(time(NULL));
	generate_password(password);
	printf("%s\n", password);
	return EXIT_SUCCESS;
}
