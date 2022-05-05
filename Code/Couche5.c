#include "header.h"
#include "Couche1.h"
#include "Couche2.h"
#include "Couche3.h"

#include "Couche5.h"

extern virtual_disk_t *virtual_disk_sos;

#define FIRST_TIME 1
#define TEST_ADD_INODE 1
#define TEST_DELETE_INODE 0
#define TEST_ADD_USER 1
#define TEST_DELETE_USER 0
#define TEST_SESSION 0

void listusers(){
  if(virtual_disk_sos->super_block.number_of_users == 0){
    printf("0 utilisateurs");
  }
  printf("Nombre d'utilisateurs : %d" , virtual_disk_sos->super_block.number_of_users );
  for(uint i = 0 ; i<virtual_disk_sos->super_block.number_of_users ; i++){
    printf("%s\n"  ,virtual_disk_sos->users_table[i].login);
  }
}

int interprete = 1;


void ls_l(){
  for (uint i = 0; i < virtual_disk_sos->super_block.number_of_files ; i++){
    printf("%s | %d | %d | %d | %d | %s | %s | %d | %d\n " , virtual_disk_sos->inodes[i].filename , virtual_disk_sos->inodes[i].size , virtual_disk_sos->inodes[i].uid ,
      virtual_disk_sos->inodes[i].uright , virtual_disk_sos->inodes[i].oright , virtual_disk_sos->inodes[i].ctimestamp , virtual_disk_sos->inodes[i].mtimestamp ,
      virtual_disk_sos->inodes[i].nblock , virtual_disk_sos->inodes[i].first_byte );
    fflush(stdout);

  }
} // je referais l'affichage plus tard

void quit(){
  interprete = 0;
}
int cr(char* nom_fichier){
  init_inode(nom_fichier , 514 , virtual_disk_sos->super_block.first_free_byte);
  return 1;
}

int rm(char* nom_fichier){
  delete_inode(nom_fichier);
  return 1;
}


int connexion(){
  char password[15];
  char login[15];
  int erreur = 0;
  char hash[100];
  int utilisateur = 1;
  int mot_de_passe = 1;
  int connexion = 1;
  int id;
  while(connexion){
    while(utilisateur){
      printf("Veuillez saisir un nom d'utilisateur : \n");
      gets(login);
      id = search_login(login);
      if(id==-1){
        printf("Nom d'utilisateur incorrect\n");
      }
      else{
        printf("Nom d'utilisateur correct\n");
        utilisateur = 0;
      }
    }
    if(!utilisateur){
      while(mot_de_passe && erreur!=3){
        printf("Saisissez le mot de passe : ");
        gets(password);
        sha256ofString((BYTE *) password, hash);
        if(strcmp(virtual_disk_sos->users_table[id].passwd , hash) ==0){
          printf("Mot de passe correct\n");
          mot_de_passe = 0;
        }
        else{
          printf("Mot de passe incorrect\n ");
          erreur++;
          if(erreur==3){
            printf("Nombre d'essai max atteint , fermeture système");
            return 0;
          }
        }
      }
    }
    if(!utilisateur && !mot_de_passe){
      printf("Connexion valide : \n");
      printf("Lancement de l'interprete de commande ...\n");

        connexion=0;
        return 1;

    }
  }
  return 0;
}



void interprete_commande(){
  char str[100];
  cmd_t tab;
  char *commande[10] = {" " }; // tableau de pointeur qui va contenir les commandes
  tab.nbArgs = 0;
  const char * separators = " \n \t " " ";

    // On cherche à récupérer, un à un, tous les mots (token) de la phrase
    // et on commence par le premier.
  if(connexion()==1){
    while(interprete){
    printf("Saisissez une commande :\n ");
    fgets(str , 32 , stdin);
    int j = 0;
    char concat[10];
    char * strToken = strtok ( str, separators );
    while ( strToken != NULL ) {
      commande[j] = strToken;
      j++;
      tab.nbArgs++;
      strToken = strtok ( NULL, separators );
    }// on prend chaque argument et on les compte

    if(strcmp(commande[0] , "ls")==0 && strcmp(commande[1] , "-l")==0 && tab.nbArgs==2){
      ls_l();
    }
    else if(strcmp(commande[0] , "ls")==0 && strcmp(commande[1] , "-l")==0 && tab.nbArgs>2){
      printf("Trop d'argument pour la commande %s " , commande[0]);
    }
    else if(strcmp(commande[0] , "ls")==0 && strcmp(commande[1] , "-l")!=0){
      printf("Argument inconnu pour la commande ls voulez-vous dire -l ? " );
    }

    if(strcmp(commande[0] , "listusers")==0 && tab.nbArgs == 1){
      listusers();
    }

    if(strcmp(commande[0] , "listusers")==0 && tab.nbArgs > 1){
      printf("trop d'argument pour la commande listusers\n");
    }


    if(strcmp(commande[0] , "quit")==0){
      quit();
    }

    if(strcmp(commande[0] , "rm")==0 && commande[1]!=NULL && tab.nbArgs>1){
     ls_l();
     strcat(commande[1] , " ");
     strcpy( concat , commande[1]);
     strcat(concat , commande[2]);
  // Concaténer Str2 dans Str1

     printf("Fichier %s supprimé avec succès\n" ,concat);
     ls_l();

   }
    tab.nbArgs = 0;

 }
 }
}

int main(void){
  interprete_commande();
  return 0;
}
