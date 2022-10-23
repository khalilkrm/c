typedef struct unite
{
   char id[10];
   char nom[100];
   int credits;
   char responsable[60];
   int n_prerequises;
   int n_corequises;
   struct unite *prerequises;
   struct unite *corequises;
}unite;

typedef enum { false, true } bool;

bool isIdCorrect(char id[10+1]);
unite encoder_unite(void);
bool ajouter_prerequis(unite unites[30], int n_unites, char *id_prerequis, char *id_unite);
bool ajouter_corequis(unite unites[30], int n_unites, char *id_corequis, char *id_unite);
void afficher(unite);
void quitter(void);
