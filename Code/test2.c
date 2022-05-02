#include "header.h"
#include "Couche1.h"
#include "Couche2.h"
#include "Couche3.h"
#include "Couche4.h"

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

void ls_l(){
  for (uint i = 0; i < virtual_disk_sos->super_block.number_of_files ; i++){
    printf("%s | %d | %d | %d | %d | %s | %s | %d | %d\n " , virtual_disk_sos->inodes[i].filename , virtual_disk_sos->inodes[i].size , virtual_disk_sos->inodes[i].uid , 
      virtual_disk_sos->inodes[i].uright , virtual_disk_sos->inodes[i].oright , virtual_disk_sos->inodes[i].ctimestamp , virtual_disk_sos->inodes[i].mtimestamp , 
      virtual_disk_sos->inodes[i].nblock , virtual_disk_sos->inodes[i].first_byte );
    fflush(stdout);
    
  }
} // je referais l'affichage plus tard

void quit(){
  interprete = 1;
}
int cr(char* nom_fichier){
  init_inode(nom_fichier , 514 , virtual_disk_sos->super_block.first_free_byte);
  return 1;
}

int rm(char* nom_fichier){
  delete_inode(nom_fichier);
  return 1;
}
  int interprete = 1;

void interprete_commande(){
  char str[100];
  cmd_t tab;
  char *commande[10] = {" " }; // tableau de pointeur qui va contenir les commandes
  tab.nbArgs = 0;
  const char * separators = " \n \t " " ";

    // On cherche à récupérer, un à un, tous les mots (token) de la phrase
    // et on commence par le premier.
  
  printf("Saisissez une commande : ");
  gets(str);
  int j = 0;
  char * strToken = strtok ( str, separators );
    while ( strToken != NULL ) {
        printf ( "%s\n", strToken );
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

    if(strcmp(commande[0] , "rm")==0 && commande[1]!=NULL){
      printf("oui");
    }

     if(strcmp(commande[0] , "quit")==0){
      quit();
    }
}






int main() {
  init_disk_sos("C:\\Users\\totol\\Downloads\\TP5_BD\\test");


  if(FIRST_TIME){
    init_first_time_super_block();
    init_first_time_inodes_tables();
    init_first_time_user_table();
  }


  printf("Superbloc :\n");
  printf("nb file=%d | nb user=%d | nb block=%d | first_byte=%d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

  printf("Table inodes :\n");
  for (int i = 0; i < INODE_TABLE_SIZE; i++) {
    printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
  }

  printf("\nTables d'utilisateurs :\n");
  for (int i = 0; i < NB_USERS; i++) {
    printf("uid = %2d | login = %32s| hash_password = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
  }

  if(TEST_ADD_INODE){
    printf("\n\n---------------------------------------------------------------\n");
    printf("#INIT_INODE\n\n");

    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
      char name[20] = "file ";
      char nombre[10];
      sprintf(nombre, "%d", i);
      strcat(name, nombre);
      init_inode(name, 514, virtual_disk_sos->super_block.first_free_byte);
    }
    printf("Superbloc :\n");
    printf("nb file=%2d | nb user=%d | nb block=%6d | first_byte=%6d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

    printf("Table inodes :\n");
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
      printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
    }

    printf("\nTables d'utilisateurs :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("uid = %2d | login = %32s| hash_password = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
    } 

    printf("TEST ------------------------\n");

  }

  if(TEST_DELETE_INODE){
    printf("\n\n---------------------------------------------------------------\n");
    printf("#DELETE_INODE\n\n");

    delete_inode("file 1");
    delete_inode("file 4");
    delete_inode("file 1");

    init_inode("Nouveau.txt", 514, virtual_disk_sos->super_block.first_free_byte);

    printf("Superbloc :\n");
    printf("nb file=%d | nb user=%d | nb block=%d | first_byte=%d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

    printf("Table inodes :\n");
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
      printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
    }

    printf("\nTables d'utilisateurs :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("uid = %2d | login = %32s| hash_password = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
    }

    printf("TEST ------------------------\n");

  }

  if(TEST_ADD_USER){
    printf("\n\n---------------------------------------------------------------\n");
    printf("#ADD_USER\n\n");

    printf("Superbloc :\n");
    printf("nb file=%d | nb user=%d | nb block=%d | first_byte=%d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

    printf("Table inodes :\n");
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
      printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
    }

    printf("\nTables d'utilisateurs :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("uid = %2d | login = %32s| hash_password = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
    }

    printf("\nAJOUT");

    add_user("dorian", "azertyuiop");
    add_user("thomas", "123");
    add_user("caelan", "bonjour");
    add_user("enzo", "ahahahah");

    printf("\nTables d'utilisateurs :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("uid = %2d | login = %32s| hash_password = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
    }


    printf("Liste ->>>>>>>> " ) ; listusers();
  }

  if(TEST_DELETE_USER){
    printf("\n\n---------------------------------------------------------------\n");
    printf("#DELETE_USER\n\n");

    printf("Superbloc :\n");
    printf("nb file=%d | nb user=%d | nb block=%d | first_byte=%d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

    printf("Table inodes :\n");
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
      printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
    }

    printf("\nTables d'utilisateurs :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("uid = %2d | login = %32s| hash_password = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
    }

    printf("\nSUPPRESSION");

    delete_user("dorian");
    delete_user("enzo");
    delete_user("dorian");

    printf("\nTables d'utilisateurs :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("uid = %2d | login = %32s| hash_password = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
    }

    printf("\nUNUSED USER ID = %d\n", get_unused_user());
  }


  if(TEST_SESSION){
    printf("\n\n---------------------------------------------------------------\n");
    printf("#OUVERTURE ET FERMETURE SESSION\n\n");

    new_session("thomas");
    printf("\nSession = %d %s\n",get_session(), virtual_disk_sos->users_table[get_session()].login);


    new_session("caelan");
    printf("\nSession = %d %s\n",get_session(), virtual_disk_sos->users_table[get_session()].login);

    del_session();
    printf("\nSession = %d\n", get_session());
  }


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
              }  
                        }
            }
  }
  if(!utilisateur && !mot_de_passe){
    interprete=0;
    printf("Connexion valide : \n");
    printf("Lancement de l'interprete de {commande ...\n");
    if(!interprete){
      while(!interprete){
        interprete_commande();
      }
    }
}

}
    
  

 
  
  /*
  }*/
    /*
  char str[100];
  cmd_t tab;
  //char *commande[10]; // tableau de pointeur qui va contenir les commandes
  tab.nbArgs = 0;
  const char * separators = " \n \t " " ";

    // On cherche à récupérer, un à un, tous les mots (token) de la phrase
    // et on commence par le premier.
  
  printf("Saisissez une commande : ");
  gets(str);
  int j = 0;
  char * strToken = strtok ( str, separators );
    while ( strToken != NULL ) {
        printf ( "%s\n", strToken );
        //commande[j] = strToken;
        j++;
        tab.nbArgs++;
        strToken = strtok ( NULL, separators );
    }// on prend chaque argument et on les compte

    if(strcmp(commande[0] , "ls")==0 && tab.nbArgs==1){
      ls();
    }

    if(strcmp(commande[0] , "ls")==0 && strcmp(commande[1] , "-l")==0 && tab.nbArgs==2){
      ls_l();
    }
    else{
      printf("Erreur commande");
    }

    printf("Le nombre total de mots dans cette chaine est = %d\n", tab.nbArgs);
*/
  if(save_disk_sos())
    return 1;


  printf("\nSAVE\n");
  return 0;
}
