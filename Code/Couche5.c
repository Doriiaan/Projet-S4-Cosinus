#include "Couche5.h"
#include "header.h"
extern virtual_disk_t *virtual_disk_sos;

int interprete = 1;
void listusers(){
  if(virtual_disk_sos->super_block.number_of_users == 0){
    printf("0 utilisateurs");
  }
  printf("Nombre d'utilisateurs : %d" , virtual_disk_sos->super_block.number_of_users );
  for(uint i = 0 ; i<virtual_disk_sos->super_block.number_of_users ; i++){
    printf("%s\n"  ,virtual_disk_sos->users_table[i].login);
  }
}
/*
int cat(char* nom_fichier){
  if(find_file(nom_fichier)==-1){
    return 0;
  }
  block_t *t;
  int indice = find_file(nom_fichier);
  int bit = virtual_disk_sos->inodes[indice].first_byte;
  int taille = virtual_disk_sos->inodes[indice].size;
  int nb_bloc = computenblock(taille);
  for(int i = 0 ; i<nb_bloc ; i++){
    read_block(bit , t);
    printf("%s" , t->data);
    bit+=BLOCK_SIZE;
  }
  return 1;
}
*/
/*int rm(char* nom_fichier){
  if(find_file(nom_fichier)==-1){
    return 0;
  }
  delete_file(nom_fichier);
  return 1;
}  
  */
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

void ls(){
  for (uint i = 0; i < virtual_disk_sos->super_block.number_of_files ; i++){
    printf("%s | %d\n " , virtual_disk_sos->inodes[i].filename , virtual_disk_sos->inodes[i].size);
    fflush(stdout);
    
  }
}

void interprete_commande(){
  //je recupere les arguments grace au separateur espace.
  char str[100];
  cmd_t tab;
  char *commande[10] = {" " }; // tableau de pointeur qui va contenir les commandes
  tab.nbArgs = 0;
  const char * separators = " \n \t " " ";
  printf("Saisissez une commande :\n ");
  fgets(str , FILENAME_MAX_SIZE , stdin);
  int j = 0;
  char concat[10];
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
 }

 int main(void){ //procedure de connexion 

   char password[15];
   char login[15];
   int erreur = 0;
   char hash[100];
   int utilisateur = 1;
   int mot_de_passe = 1;
   int connexion = 1;
   int id;
   while(connexion){ // tant qu'on arrete pas le prog
    while(utilisateur){ // tant que la saisie utilisateur est fausse
      printf("Veuillez saisir un nom d'utilisateur : \n");
      fgets(login , 20 , stdin);
      id = search_login(login);
      if(id==-1){
        printf("Nom d'utilisateur incorrect\n");
      }
      else{
        printf("Nom d'utilisateur correct\n");
        utilisateur = 0;
      }
    }
    if(!utilisateur){ //si l'utilisateur est correct
      while(mot_de_passe && erreur!=3){ // tant que le mdp est faux ou 3 tentatives
        printf("Saisissez le mot de passe : ");
        fgets(password , 20 , stdin);
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
    if(!utilisateur && !mot_de_passe){ // si mdp ok et utilisateur ok on demarre l'interprete
      printf("Connexion valide : \n");
      printf("Lancement de l'interprete de commande ...\n");
      while(interprete){
        interprete_commande();
      }
      if(interprete==0){ // si on quitte l'interprete on ferme le programme
        connexion=0;
      }
    }
  }

  return 0;

}
