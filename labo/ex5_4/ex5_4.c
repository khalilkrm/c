#include <stdlib.h>
#include <stdio.h>

#include "struct.h"

#define MAX_LOCALITE 10

int encodage(struct observation ob[MAX_LOCALITE])
{
	int nombre_localite;
	int i;

	do
	{
		printf("Entrez le nombre de localite observée (MAX 10) : ");scanf("%d%*c", &nombre_localite);
		if(nombre_localite > 10)
		{
			printf("Le nombre de localite observée ne peut depasser 10\n");
		}else {
					
			for(i = 0; i < nombre_localite; i++)
			{
				printf("Encodage de la localite n° %i\n", i);
				printf("Entrez le nom : ");scanf("%60[^\n]%*c", ob[i].localite);
				printf("Entrez la temperature : ");scanf("%f%*c", &ob[i].temperature);	
			}
		
		}
	}while(nombre_localite > 10);

	return nombre_localite;
}


void affichage(struct observation ob[MAX_LOCALITE], int nombre_effectif_localite)
{
	int i;
	printf("\n-----Affichage-----\n");
	for(i = 0; i < nombre_effectif_localite; i++)
	{
		printf("Localite n° %d\n", i);
		printf("\t\tNom : %s", ob[i].localite);
		printf("\t\tTemperature : %f\n", ob[i].temperature);
	}
}

float moyenne(struct observation ob[MAX_LOCALITE], int nombre_effectif_localite)
{
	int i;
	float moyenne = 0.0;
	for(i = 0; i < nombre_effectif_localite; i++)
	{
		moyenne += ob[i].temperature;
	}

	return moyenne / nombre_effectif_localite;
}


int main(void)
{
		
	struct observation ob[MAX_LOCALITE];
	int nombre_effectif_localite = encodage(ob);
	affichage(ob, nombre_effectif_localite);
	printf("\n\t\tTemperature moyenne : %f\n", moyenne(ob, nombre_effectif_localite));

	return EXIT_SUCCESS;
}
