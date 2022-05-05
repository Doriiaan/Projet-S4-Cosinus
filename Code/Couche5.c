#include "header.h"
#include "Couche1.h"
#include "Couche2.h"
#include "Couche3.h"
#include "Couche4.h"
#include "Couche5.h"
#include "conio.h"
extern virtual_disk_t *virtual_disk_sos;

#define FIRST_TIME 1
#define TEST_ADD_INODE 1
#define TEST_DELETE_INODE 0
#define TEST_ADD_USER 1
#define TEST_DELETE_USER 0
#define TEST_SESSION 0


int interprete = 1;


void listusers(){
  if(virtual_disk_sos->super_block.number_of_users == 0){
    printf("0 utilisateurs");
  }
  printf("Nombre d'utilisateurs : %d\n" , virtual_disk_sos->super_block.number_of_users );
  for(uint i = 0 ; i<virtual_disk_sos->super_block.number_of_users ; i++){
    if(virtual_disk_sos->users_table[i].login==NULL){
      printf("vide\n");
    }
    printf("%s\n"  ,virtual_disk_sos->users_table[i].login);
  }
}

void ls_l(){
  for (uint i = 0; i < virtual_disk_sos->super_block.number_of_files ; i++){
    printf("%s | %d | %d | %d | %d | %s | %s | %d | %d\n " , virtual_disk_sos->inodes[i].filename , virtual_disk_sos->inodes[i].size , virtual_disk_sos->inodes[i].uid ,
      virtual_disk_sos->inodes[i].uright , virtual_disk_sos->inodes[i].oright , virtual_disk_sos->inodes[i].ctimestamp , virtual_disk_sos->inodes[i].mtimestamp ,
      virtual_disk_sos->inodes[i].nblock , virtual_disk_sos->inodes[i].first_byte );
    fflush(stdout);

  }
} // je referais l'affichage plus tard

int cat(char* nom_fichier){
  file_t *file = malloc(sizeof(file_t));
  read_file(nom_fichier , file);
  printf("%s\n" , file->data);
  return 1;
}

int adduser(){
  int pos;
  pos = get_unused_user();
  if(pos==-1){
    printf("Nombre d'utilisateurs max atteint\n");
    return 0;
  }
  char login[20];
  char password[20];

    printf("Saisissez un login\n");
    fgets(login , 20 , stdin);
    printf("Saisissez un mot de passe :\n" );
    fgets(password , 20 , stdin);
    add_user(login , password);
    printf("Creation de l utilisateur %s reussi\n" , virtual_disk_sos->users_table[pos].login);
    return 1;

}

int rmuser(char * nom_login){
  int pos;
  pos = search_login(nom_login);

  if(pos==-1){
    printf("Login inexistant\n");
    return 0;
  }
  if(pos==0){
    printf("Impossible de supprimer l'utilisateur root\n");
    return 0;
  }
  delete_user(nom_login);
  return 1;

}


int edit(char* nom_fichier){
  file_t file;
  printf("Entrez vos donnees , utilisez la touche espace suivi de @ pour quitter la saisie\n");

    fgets((char*)file.data, MAX_FILE_SIZE , stdin);
      char ch = getch();
      if ( kbhit() && ch=='@' ) { // quand on rentre \n et @ ca s'arrete
                return 0;
            }

    file.data[MAX_FILE_SIZE-1] = (uchar)EOF;
    file.size = MAX_FILE_SIZE;
    write_file(nom_fichier,file);
    return 1;

  }

void ls(){
  for (uint i = 0; i < virtual_disk_sos->super_block.number_of_files ; i++){
    printf("%s \t  %d \n  " , virtual_disk_sos->inodes[i].filename , virtual_disk_sos->inodes[i].size );
}
}
void quit(){
  interprete = 0;
  save_disk_sos();
  printf("\nSAVE\n");

}
int cr(char* nom_fichier){
  init_inode(nom_fichier , MAX_FILE_SIZE , virtual_disk_sos->super_block.first_free_byte);
  return 1;
}

int rm(char* nom_fichier){
  if(delete_file(nom_fichier)!=1){
    printf("Erreur suppression fichier\n");
  return 0;
}
return 1;
}

void help(){
  printf("cat <nom de fichier> : affiche a  l ecran le contenu d un fichier si l utilisateur a les droits\n");
  printf("rm <nom de fichier> : supprime un fichier du systeme si l utilisateur a les droits\n");
  printf("cr <nom de fichier> : cree un nouveau fichier sur le systeme, le proprietaire est l utilisateur.\n");
  printf("edit <nom de fichier> : edite un fichier pour modifier son contenu si l utilisateur a les droits\n") ;
  printf("load <nom de fichier> : copie le contenu d un fichier du systeme hote sur le systeme avec le meme nom\n ");
  printf("store <nom de fichier> : copie le contenu d un fichier du systeme sur hote avec le meme nom\n");
  printf("chown <nom de fichier> <login autre utilisateur> change le proprietaire d un fichier\n");
  printf("chmod <nom de fichier> <droit> change les droits d’un fichier pour tous les autres utilisateurs\n");
  printf("listusers : affiche la liste des utilisateurs du systeme\n");
  printf("quit : sort de l interprete de commande\n");

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
            printf("Nombre d'essai max atteint , fermeture système\n");
            return 0;
          }
        }
      }
    }
    if(!utilisateur && !mot_de_passe){
      printf("Connexion valide : \n");
      printf("Lancement de l'interprete de commande ...\n");
      printf("Tapez -help a tout moment pour connaitre les commandes utilisables\n");

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
    int somme = 0;
    // On cherche à récupérer, un à un, tous les mots (token) de la phrase
    // et on commence par le premier.
  if(connexion()==1){
    while(interprete){
    printf("Saisissez une commande :\n ");
    fgets(str , 32 , stdin);
    int j = 0;
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
    else if(strcmp(commande[0] , "ls")==0 && strcmp(commande[1] , "-l")!=0 && tab.nbArgs==2){
      printf("Argument inconnu pour la commande ls voulez-vous dire -l?\n " );
    }

    if(strcmp(commande[0] , "listusers")==0 && tab.nbArgs == 1){
      listusers();
    }

    if(strcmp(commande[0] , "listusers")==0 && tab.nbArgs > 1){
      printf("trop d'argument pour la commande listusers\n");
    }


    if(strcmp(commande[0] , "quit")==0){
      save_disk_sos();
      printf("\nSAVE\n");
      quit();
    }
    somme = get_unused_inode();
    if(strcmp(commande[0] , "cr")==0 && tab.nbArgs>1 && commande[1]!=NULL && somme==-1){
        printf("Nombre de fichier max atteint\n");
      }
      if(strcmp(commande[0] , "cr")==0 && tab.nbArgs>1 && commande[1]!=NULL && somme!=-1)
      {
        printf("Creation fichier %s\n" , commande[1]);
        cr(commande[1]);
      }
       if(strcmp(commande[0] , "cr")==0 && tab.nbArgs==1 )
      {
        printf("La commande cr prend au moin un argument\n");
      }

      if(strcmp(commande[0] , "-help")==0 && tab.nbArgs==1){
        help();
      }

      if(strcmp(commande[0] , "ls")==0 && tab.nbArgs==1){
        ls();
      }

      if(strcmp(commande[0] , "rm")==0 && tab.nbArgs>1 && commande[1]!=NULL){
        rm(commande[1]);
      }

      if(strcmp(commande[0] , "edit")==0 && tab.nbArgs>1 && commande[1]!=NULL){
        edit(commande[1]);
      }

      if(strcmp(commande[0] , "cat")==0 && tab.nbArgs>1 && commande[1]!=NULL){
        cat(commande[1]);
      }
      if(strcmp(commande[0] , "adduser")==0 && tab.nbArgs==1){
        adduser();
      }
      if(strcmp(commande[0] , "rmuser")==0 && tab.nbArgs>1 && commande[1]!=NULL){
        rmuser(commande[1]);
      }
          tab.nbArgs = 0;

    }


 }
}
