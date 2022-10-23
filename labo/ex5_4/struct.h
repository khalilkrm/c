#define LOCALITE_BUFFER_SIZE 60

struct observation 
{
	float temperature;
	char localite[LOCALITE_BUFFER_SIZE];
};
