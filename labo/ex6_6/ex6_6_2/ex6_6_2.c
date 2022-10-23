#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

typedef struct unite {
   /*VALUES*/
   char id[10];
   char name[100];
   char owner[60];

   int credites;
   
   /*NODES*/
   struct unite *next_prerequired;
   struct unite *next_corequired;

}unite_t;

bool test_id(char *id) {
 
 if(*((int*)(id+=2)) != '-') return false;
 if(*((int*)(id+=3)) != '-') return false;
 return true;
 
}

unite_t unite_creation(unite_t u) {
 
 /*NODES INITIALISATION*/
 u.next_prerequired = NULL;
 u.next_corequired = NULL;
 
 /*VALUES ENCODING*/
 printf("Entrez l'identifiant: ");scanf("%10[^\n]%*c", u.id);
 printf("Entrez le nom de l'unite d'enseignement: ");scanf("%100[^\n]%*c", u.name);
 printf("Entrez le nom du responsable: ");scanf("%60[^\n]%*c", u.owner);
 printf("Entrez le nombre de credit: ");scanf("%d%*c", &u.credites);

 return u;
}

void unite_add_prerequired(unite_t *to_add, unite_t destination) {

 unite_t * current = destination.next_prerequired;
 
 while(current != NULL)
 {
   current = current->next_prerequired;
 }

 current->next_prerequired = to_add;
}

void unite_add_corequired(unite_t *to_add, unite_t destination) {

 unite_t * current = destination.next_corequired;

 while(current != NULL)
 {
   current = current->next_corequired;
 }

 current->next_corequired = to_add;
}

void show(unite_t u) {

 int i;
 unite_t * current;

 printf("Identifiant de l'unite: %s\n", u.id);
 printf("Nom de l'unite: %s\n", u.name);
 printf("Nom de du responsable de l'unite: %s\n", u.owner);
 printf("Nombre de credits: %d", u.credites);
 
 printf("Affichage des prerequis : \n");
 
 i = 0;
 current = u.next_prerequired;
 
 while(current != NULL) {
  printf("\t>>Identifiant du prerequis n°%d : %s\n", i, current->id); 
  current = current->next_prerequired;
 }
 
 printf("Affichage des corequis : \n");
  
 i = 0;
 current = u.next_corequired;
 
 while(current != NULL) {
  printf("\t>>Identifiant du prerequis n°%d : %s\n", i, current->id);
  current = current->next_corequired;
 }

}

int menu() {
 
 int answer;
 printf("1.Encoder une unite.\n2.Ajouter un prerequis à une unite.\n3.Ajouter un corequis à une unite.\n4.Afficher une unite.\n5.Quitter le programme.\nChoisissez : ");
 
 do {
   scanf("%d%*c", &answer);
 } while(answer < 1 || answer > 5);

 return answer;
}

int main(void) {
 
 /*DECLARATION*/ 
 int us_effective_size;
 unite_t us[30];
 unite_t unite_tmp;
 int i;
 int menu_choice;

 /*PRE-CO-REQUIRED EDITION ATTRIBUTES*/
 int unite_num;
 unite_t * to_add;
 unite_t destination;
 
 /*INITIALISATION*/
 us_effective_size = 0;
  
 /*WORK*/
 do {
 switch((menu_choice = menu())) {
  case 1: {
   if(us_effective_size >= 30) {
     printf("Nombre d'unite maximum atteint. Impossible d'ajouter d'unite supplèmentaire.\n");
   }else {
     unite_tmp = unite_creation(us[us_effective_size]);
     us_effective_size++;
   }
   break;
  }
  case 2: {
    printf("Les unites disponibles : \n");
    for(i = 0; i < us_effective_size; i++) {
     printf("\t>>Identifiant unite n°%d : %s\n", i, us[i].id);
    }

    /*DESTINATION*/
    printf("Choisissez l'unite qui recevra le prerequis (en entrant le n° de l'unite)\n : "); 
    
    do {
      scanf("%d%*c", &unite_num);    
    }while(unite_num < 0 || unite_num > us_effective_size);
    
    destination = us[unite_num];
    
    /*PREREQUIS*/
    printf("Choisissez l'unite à ajouter comme prerequis (en entrant le n° de l'unite)\n : ");    
    
    do {
      scanf("%d%*c", &unite_num);
    }while(unite_num < 0 || unite_num > us_effective_size);
    
    to_add = &us[unite_num];

    unite_add_prerequired(to_add, destination);
    break;
  }
  case 3: {
    printf("Les unites disponibles : \n");
    for(i = 0; i < us_effective_size; i++) {
     printf("\t>>Identifiant unite n°%d : %s\n", i, us[i].id);
    }

    /*DESTINATION*/
    printf("Choisissez l'unite qui recevra le corequis (en entrant le n° de l'unite)\n : ");

    do {
      scanf("%d%*c", &unite_num);
    }while(unite_num < 0 || unite_num > us_effective_size);

    destination = us[unite_num];

    /*PREREQUIS*/
    printf("Choisissez l'unite à ajouter comme corequis (en entrant le n° de l'unite)\n : ");

    do {
      scanf("%d%*c", &unite_num);
    }while(unite_num < 0 || unite_num > us_effective_size);

    to_add = &us[unite_num];

    unite_add_corequired(to_add, destination);
  }
  case 4: {
    printf("Les unites disponibles : \n");
     for(i = 0; i < us_effective_size; i++) {
      printf("\t>>Identifiant unite n°%d : %s\n", i, us[i].id);
    }
    printf("Choisissez l'unite à afficher (en entrant le n° de l'unite): ");
   
    do {
      scanf("%d%*c", &unite_num);
    }while(unite_num < 0 || unite_num > us_effective_size); 
   
    show(us[unite_num]);
    break;
  }
  default: printf("Bye !\n");
 }
 }while(menu_choice != 5);

 return EXIT_SUCCESS;

}





