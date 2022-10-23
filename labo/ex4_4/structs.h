
#define NOM_RESPONSABLE_BUFFER_SIZE 60
#define NOM_ACTIVITE_BUFFER_SIZE 100
#define NOMBRE_ACTIVITE 3

struct aa
{
	char nom[NOM_ACTIVITE_BUFFER_SIZE];
	int heures;
	float note;
};

struct ue
{
	struct aa activites[NOMBRE_ACTIVITE];
	int credit;
	char responsable[NOM_RESPONSABLE_BUFFER_SIZE];
	float cote;
};
