#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

struct ue encodage()
{	

	/*Calcul cote UE*/
	float nombre_heures = 0;
	int echec = 0;
	float cote = 0;
	
	/*Attribut necesaires*/
	int i;
	struct ue unite;
	struct aa *activite;
	printf("Entrez le nombre de credit : "); scanf("%d%*c", &unite.credit);
	printf("Entrez le nom du responsable : "); scanf("%60[^\n]%*c", unite.responsable);
	
	for(i = 0; i < NOMBRE_ACTIVITE; i++)
	{
		activite = &unite.activites[i];
		printf("Encodage de l'activite %d \n", i);
		printf("Entrez le nom de l'activite : "); scanf("%100[^\n]%*c", activite->nom);
		printf("Entrez le nombre d'heures : "); scanf("%d%*c", &activite->heures);
		printf("Entrez la note : "); scanf("%f%*c", &activite->note);
		
		if(activite->note < 10) echec++;
		nombre_heures += activite->heures;
	}
	

	if(echec > 0) unite.cote = 10 - echec;
	else 
	{

		for(i = 0; i < NOMBRE_ACTIVITE; i++)
		{
			activite = &unite.activites[i];
			cote += activite->note/(nombre_heures/activite->heures);
		}
		
		unite.cote = cote;
	}
	
	return unite;
}


void affichage(struct ue unite)
{
	int i;
	struct aa activite;
	printf("\n-----Affichage-----\n");
	printf("Nombre de credit : %d\n", unite.credit);
	printf("Responsable : %s\n", unite.responsable);
	for(i = 0; i < NOMBRE_ACTIVITE; i++)
	{
		activite = unite.activites[i];
		printf("Activite n°%d : \n", i);
		printf("Nom : %s\n", activite.nom);
		printf("Nombre d'heures : %d\n", activite.heures);
		printf("Note : %f\n", activite.note);
	}
	printf("Cote : %f\n", unite.cote);
}


int main(void)
{

	struct ue unite = encodage();
	affichage(unite);
	return EXIT_SUCCESS;

}
