#include "Couche5.h"
extern virtual_disk_t *virtual_disk_sos;

#define FIRST_TIME 0
#define TEST_ADD_INODE 1
#define TEST_DELETE_INODE 0
#define TEST_ADD_USER 1
#define TEST_DELETE_USER 0
#define TEST_SESSION 0


int interprete = 1;

/**
* @brief retire le caractere \n lors d'une saisie de login avec fgets
* @param char*  chaine de caractere
* @return void
**/
void enlever_retour_ligne(char *chaine){

  int taille = strlen(chaine);
  if(chaine[taille-1] == '\n')
    chaine[taille-1] = '\0';
}

int caractere_present(char* chaine , char carac){
  int taille = strlen(chaine);
  for(int i = 0 ; i<taille ; i++){
    if(chaine[i]==carac){
      return 1;
    }
  }
  return 0;
}

void credit(){
  printf ("\033[H\033[J");
  disp_design_os(true);

  printf("\033[0;34m"); //couleur
  printf("\n\n");
  printf("BY\n");
  printf("Dorian Alary\n\n");
  printf("Enzo Munos\n\n");
  printf("Caelan Hehir\n\n");
  printf("Thomas Lebrun\n\n");
  printf("\033[0m"); //couleur

}

/**
* @brief Affiche la liste des utilisateurs du systeme
* @param NULL
* @return void
**/
void listusers(){

  printf("Nombre d'utilisateurs : %d\n" , virtual_disk_sos->super_block.number_of_users );
  for(uint i = 0 ; i<virtual_disk_sos->super_block.number_of_users ; i++){
    if(virtual_disk_sos->users_table[i].login==NULL){
      i++;
    }
    printf("%s\n"  ,virtual_disk_sos->users_table[i].login);
  }
}


/**
* @brief Affiche la liste des fichiers et leurs descriptions
* @note affichage de toutes les donnes de l'inode
* @param NULL
* @return void
**/
void ls_l(){
  char uright[4];
  char oright[4];

  printf("\n");
  for (uint i = 0; i < virtual_disk_sos->super_block.number_of_files ; i++){

    switch (virtual_disk_sos->inodes[i].uright) {
      case 0:
      strcpy(uright, "rw");
      break;
      case 1:
      strcpy(uright, "rW");
      break;
      case 2:
      strcpy(uright, "Rw");
      break;
      case 3:
      strcpy(uright, "RW");
      break;
    }
    switch (virtual_disk_sos->inodes[i].oright) {
      case 0:
      strcpy(oright, "rw");
      break;
      case 1:
      strcpy(oright, "rW");
      break;
      case 2:
      strcpy(oright, "Rw");
      break;
      case 3:
      strcpy(oright, "RW");
      break;
    }

    printf("  %3s ", uright);
    printf("%3s  ", oright);
    printf("%10s  ", search_id((int)virtual_disk_sos->inodes[i].uid));
    printf("%4d  ", virtual_disk_sos->inodes[i].size);
    printf("%3d  ", virtual_disk_sos->inodes[i].nblock);
    printf("%4d  ", virtual_disk_sos->inodes[i].first_byte);
    printf("%26s  ", virtual_disk_sos->inodes[i].ctimestamp);
    printf("%26s  ", virtual_disk_sos->inodes[i].mtimestamp);
    printf("\033[0;34m");
    printf("%s\n", virtual_disk_sos->inodes[i].filename);
    printf("\033[0m");
  }
  printf("\n");
}


/**
* @brief Affiche le contenu d'un fichier du systeme
* @param char* filename : Nom du fichier à ecire sur stdout
* @note utilise la fonction read_file de la couche 4 pour afficher le contenu du fichier filename
* @return int : 1 si le fichier a été trouvé et affiché, 0 en cas d'erreur
**/
int cat(cmd_t *commande){

  if(commande->nbArgs != 2){
    printf("Usage : %s <nom de fichier>\n", commande->tabArgs[0]);
    return 0;
  }

  char *nom_fichier = commande->tabArgs[1];

  if(search_file_inode(nom_fichier)==-1){
    printf("Fichier inexistant");
    return 0;
  }
  uint user = get_session();
  if(strcmp(nom_fichier , "passwd")==0 && user != 0){
    printf("Impossible d'afficher ce fichier\n");
    return 0;
  }
  file_t file ;
  read_file(nom_fichier , &file);
  printf("Contenu du fichier %s\n" , nom_fichier);
  printf("%s\n" , file.data);
  return 1;
}

/**
* @brief vide le terminal
* @param aucun
* @note utilise un printf specifique pour effacer le terminal
* @return : void
**/
void clear(){
  printf ("\033[H\033[J");
  disp_design_os(false);

}

/**
* @brief ajoute un utilisateur au systeme
* @param NULL
* @note demande un login a l'utilisateur root et si ce login n'est pas dans la table , l'user est ajouté
* @note  seul root a acces a cette commande
* @return int
**/

int adduser(cmd_t* commande){
  if(commande->nbArgs != 2){
    printf("Usage : %s <nom de login>\n", commande->tabArgs[0]);
    return 0;
  }

  char* login = commande->tabArgs[1];

  if(get_session()!=0){
    printf("\033[0;31m"); //couleur
    printf("Commande réservé a l'utilisateur root\n");
    printf("\033[0m"); //couleur

    return 0;
  }

  int confirmer = 0;
  int pos;
  pos = get_unused_user();

  if(pos==-1){
    printf("\033[0;31m"); //couleur
    printf("Nombre d'utilisateurs max atteint\n");
    printf("\033[0m"); //couleur
    return 0;
  }
  if(search_login(login)!=-1){
    printf("\033[0;31m"); //couleur
    printf("Ce nom d'utilisateur existe deja \n");
    printf("\033[0m"); //couleur
    return 0;
  }
  char confirm[FILENAME_MAX_SIZE];
  char password[FILENAME_MAX_SIZE];

  int num = 1;

  printf("Saisissez un mot de passe : " );
  fgets(password , FILENAME_MAX_SIZE , stdin);
  printf("Veuillez confirmer le mot de passe: ");
  fgets(confirm , FILENAME_MAX_SIZE , stdin);
  enlever_retour_ligne(password);
  enlever_retour_ligne(confirm);
  printf("\n");

  while(!confirmer){

    if(strcmp(confirm , password)!=0){
      num++;
      printf("Les mots de passes ne correspondent pas saisissez à nouveau un mot de passe : " );
      fgets(password , FILENAME_MAX_SIZE , stdin);
      printf("Veuillez confirmer le mot de passe: ");
      fgets(confirm , FILENAME_MAX_SIZE , stdin);
      enlever_retour_ligne(password);
      enlever_retour_ligne(confirm);
      printf("\n");
      if(num==3){
        printf("\033[0;31m"); //couleur
        printf("Erreur creation utilisateur , trop de tentative de mot de passe\n");
        printf("\033[0m"); //couleur
        return 0;
      }
    }


    if(strcmp(confirm , password)==0 ){
      add_user(login , password);
      printf("\033[0;34m"); //couleur
      printf("Creation de l utilisateur %s reussi \n" , virtual_disk_sos->users_table[pos].login);
      printf("\033[0m"); //couleur
      confirmer = 1;
      return 1;

    }

  }
  return 0;
}

/**
* @brief affiche le proprietaire et les droits du fichier en parametre
* @note  fonction inutile mais pratique pour avoir un apercu
* @param char* : nom de fichier
* @return int 1 si tout se passe bien (si le fichier existe)
**/
int getdroit(char* nom_fichier){
  int pos = search_file_inode(nom_fichier);
  int prop = virtual_disk_sos->inodes[pos].uid;

  if(pos==-1){
    printf("Fichier inexistant , info indisponible\n");
    return 0;
  }

  printf("Proprietaire du fichier = %s\n" , virtual_disk_sos->users_table[prop].login);
  printf("\n");
  printf("Droit des utilisateurs = %d\n" , virtual_disk_sos->inodes[pos].oright);
  printf("\n");
  printf("Droit du proprietaire = %d\n" , virtual_disk_sos->inodes[pos].uright);
  printf("\n");
  return 1;
}

/**
* @brief cree le fichier nom_fichier , s'il depasse la taille max on renvoie une erreur
* @param char* : nom de fichier
* @note ajouter de la valeur 3 au debut pour simplifier la verification java
* @return int 1 si tout se passe bien , 0 si le fichier ne peut pas etre crée
**/
int cr(cmd_t *commande){

  if(commande->nbArgs != 2){
    printf("Usage : %s <nom de fichier>\n", commande->tabArgs[0]);
    return 0;
  }

  char *nom_fichier = commande->tabArgs[1];
  if(strlen(nom_fichier)>FILENAME_MAX_SIZE){
    printf("\033[0;31m"); //couleur
    printf("Un fichier ne peut contenir que %d caractere maximum\n" , FILENAME_MAX_SIZE);
    printf("\033[0m"); //couleur

    return 0;
  }

  file_t file;
  file.size = 1;
  file.data[0]=3;
  write_file(nom_fichier , file);
  printf("\033[0;34m"); //couleur
  printf("Creation du fichier %s reussi\n" , nom_fichier);
  printf("\033[0m"); //couleur
  getdroit(nom_fichier);
  return 1;

}


/**
* @brief modifie le fichier s'il existe , ou le crée et ecrit dedans il existe pas
* @note  2048 caracteres max a ecrire , saisir @@ pour quitter
* @param char* : nom de fichier
* @return int 1 si tout se passe bien (si le fichier existe)
**/

int edit_file(cmd_t *commande){
  file_t file ;
  char* filename = commande->tabArgs[1];
  if(strcmp(filename , "passwd")==0){
    printf("\033[0;31m"); //couleur
    printf("Impossible de modifier le fichier passwd\n");
    printf("\033[0m"); //couleur
    return 0;
  }
  int pos = search_file_inode(filename);
  if(pos==-1){
    if(cr(commande)!=1){
      printf("\033[0;31m"); //couleur
      printf("Erreur création fichier\n");
      printf("\033[0m"); //couleur
      return 0;
    }
  }
  read_file(filename , &file);
  printf("%s" , (char*)file.data);
  if(!Term_non_canonique())
    return 0;

  char c;
  int fin = 0;

  do {
    printf ("\033[H\033[J");
    printf("*****EDIT*****\n\n");
    printf("Tapez @ à tout moment pour arreter la saisie\n\n");

    for (int i = 0; i < (int)file.size; i++) {
      printf("%c", file.data[i]);
    }

    c=fgetc(stdin);

    switch (c) {
      case '@':
        fin = 1;
        break;
      case '\b':
        if(file.size > 0)
        file.size--;
        printf ("\033[H\033[J");
        break;
      default:
        file.data[file.size] = c;
        file.size++;
    }

  } while(!fin && file.size < MAX_FILE_SIZE);

  write_file(filename , file);

  if(!Term_canonique())
    return 0;

  clear();
  return 1;
}
/**
* @brief supprimer un user du systeme
* @note  utilisable que par root et si le login existe
* @param char* nom de login
* @return int 1 si tout se passe bien (si l'user connecte est le root et si le login existe) , 0 sinon
**/

int rmuser(cmd_t* commande){
  int pos;
  char* login = commande->tabArgs[1];
  if(commande->nbArgs != 2){
    printf("Usage : %s <login>\n", commande->tabArgs[0]);
    return 0;
  }
  pos = search_login(login);
  if(get_session()!=0){
    printf("\033[0;31m"); //couleur
    printf("Commande réservé a l'utilisateur root .\n");
    printf("\033[0m"); //couleur
    return 0;
  }

  if(pos==-1){
    printf("\033[0;31m"); //couleur
    printf("Login inexistant\n");
    printf("\033[0m"); //couleur
    return 0;
  }

  if(pos==0){
    printf("\033[0;31m"); //couleur
    printf("Impossible de supprimer l'utilisateur root\n");
    printf("\033[0m"); //couleur
    return 0;
  }
  printf("\033[0;34m"); //couleur
  printf("Suprresion de l'utilisateur %s" , virtual_disk_sos->users_table[pos].login);
  printf("\033[0m"); //couleur

  delete_user(login);
  return 1;

}

/**
* @brief deconnecte l'user
* @note : l'user se deconnecte et met son id a -1
* @param NULL
* @return int 1 si tout se passe bien
**/

int deconnexion(){
  del_session();
  return 1;
}

/**
* @brief Affiche la liste des fichiers et leurs descriptions
* @note n'affiche que le nom du fichier et sa taille
* @param void
* @return void
**/

void ls(cmd_t *commande){

  if(commande->nbArgs == 2 && strcmp(commande->tabArgs[1],"-l") == 0){
    ls_l();
  }
  else{
    for (int i = 0; i < (int)virtual_disk_sos->super_block.number_of_files ; i++){
      printf("\033[0;34m");
      printf("   %s\t", virtual_disk_sos->inodes[i].filename);
      printf("\033[0m");
      printf("%d\n", virtual_disk_sos->inodes[i].size);
    }
  }


}

/**
* @brief ferme l'interprete et sauvegarde le systeme sur le disque
* @param NULL
* @return void
**/

void quit(){
  interprete = 0;
  printf("Sauvegarde effectue\n");
  save_disk_sos();
}

/**
* @brief efface un fichier du systeme si l'user connecte a les droits (root ou proprietaire du fichier)
* @note impossible d'effacer le fichier de quelqu'un d'autre
* @param char* nom_fichier
* @return int 1 si l'user a les droits et le fichier existe , 0 sinon
**/



int rm(cmd_t *commande){
  uint user = get_session();
  if(commande->nbArgs != 2){
    printf("Usage : %s <nom de fichier>\n", commande->tabArgs[0]);
    return 0;
  }
  char *nom_fichier = commande->tabArgs[1];
  if(strlen(nom_fichier)>FILENAME_MAX_SIZE){
    printf("Un fichier ne peut contenir que %d caractere maximum\n" , FILENAME_MAX_SIZE);
    return 0;
  }
  int pos = search_file_inode(nom_fichier);

  if(pos==-1){
    printf("\033[0;31m"); //couleur
    printf("Nom de fichier inexistant\n");
    printf("\033[0m"); //couleur

    return 0;
  }

  if(virtual_disk_sos->inodes[pos].uid==user){
    if(delete_file(nom_fichier)==-1){
      printf("\033[0;31m"); //couleur
      printf("Erreur suppression\n");
      printf("\033[0m"); //couleur
      return 0;
    }
    printf("\033[0;34m"); //couleur
    printf("Suppression du fichier %s reussi\n" , nom_fichier);
    printf("\033[0m"); //couleur
    return 1;
  }

  if(virtual_disk_sos->inodes[pos].uid!=user && virtual_disk_sos->inodes[pos].oright==3){
    if(delete_file(nom_fichier)==-1){
      printf("\033[0;31m"); //couleur
      printf("Erreur suppression\n");
      printf("\033[0m"); //couleur
      return 0;
    }
    printf("\033[0;34m"); //couleur
    printf("Suppression du fichier %s reussi\n" , nom_fichier);
    printf("\033[0m"); //couleur
    return 1;
  }
  else{
    printf("\033[0;31m"); //couleur
    printf("Vous n'avez pas les droits pour supprimer le fichier %s\n" , nom_fichier);
    printf("\033[0m"); //couleur
    return 0;
  }
  return 0;
}

/**
* @brief change les droits pour les autres utilisateurs si l'user connecte a les droits (root ou proprietaire)
* @note: impossible de changer les droits si le fichier ne nous appartient pas .
* @param char* nom du fichier , int droit (0 , 1 , 2 , 3)
* @return int 1 si l'user connecte a les droits et que le fichier existe , 0 sinon
**/

int chmod(cmd_t *commande){
  char *nom_fichier = commande->tabArgs[1];
  int droit = atoi(commande->tabArgs[2]);
  int pos = search_file_inode(nom_fichier);
  uint user = get_session();
  if(commande->nbArgs != 3){
    printf("Usage : %s <nom de fichier> <droit>\n", commande->tabArgs[0]);
    return 0;
  }
  if(pos==-1){
    printf("\033[0;31m"); //couleur
    printf("Fichier inexistant\n");
    printf("\033[0m"); //couleur
    return 0;
  }

  if(droit>3){
    printf("\033[0;31m"); //couleur
    printf("Le droit maximum est 3 pour lecture et ecriture\n");
    printf("\033[0m"); //couleur
    return 0;
  }

  if(virtual_disk_sos->inodes[pos].uid==user && virtual_disk_sos->inodes[pos].uright==3){
    virtual_disk_sos->inodes[pos].oright=droit;
    getdroit(nom_fichier);
    return 1;
  }

  if(user==0){
    virtual_disk_sos->inodes[pos].oright=droit;
    getdroit(nom_fichier);
    return 1;
  }

  else{
    printf("\033[0;31m"); //couleur
    printf("Vous ne pouvez pas changez les droits du fichier %s\n" , nom_fichier);
    printf("\033[0m"); //couleur
    return 0;
  }

  return 0;
}

/**
* @brief change le proprietaire d'un fichier si l'user connecte a les droits (root ou proprietaire)
* @note impossible de changer le proprietaire si l'user connecte ne l'est pas ou si l'user connecte n'est pas root
* @param char * nom du fichier , char* login du nouveau proprietaire
* @return int si l'user est le root ou le proprietaire du fichier , si le fichier existe et si le login existe , 0 sinon
**/

int chown(cmd_t* commande){
  char *nom_fichier = commande->tabArgs[1];
  char* login = commande->tabArgs[2];
  int pos = search_file_inode(nom_fichier);
  uint user = get_session();
  uint log = search_login(login);
  int logint = search_login(login);
  if(commande->nbArgs != 3){
    printf("Usage : %s <nom de fichier> <login>\n", commande->tabArgs[0]);
    return 0;
  }
  if(pos==-1){
    printf("\033[0;31m"); //couleur
    printf("Fichier inexistant\n");
    printf("\033[0m"); //couleur
    return 0;
  }

  if(virtual_disk_sos->inodes[pos].uid==log){
    printf("\033[0;31m"); //couleur
    printf("%s est déja le proprietaire du fichier\n" , login);
    printf("\033[0m"); //couleur

    return 0;
  }

  if(logint==-1){
    printf("\033[0;31m"); //couleur
    printf("Login inexistant\n");
    printf("\033[0m"); //couleur
    return 0;
  }

  if(virtual_disk_sos->inodes[pos].uid==user || user==0){
    virtual_disk_sos->inodes[pos].uid=log;
    getdroit(nom_fichier);
    return 1;
  }

  return 0;
}

/**
* @brief Affiche la liste des commandes executables
* @note: a taper a tout moment pour obtenir la liste
* @param void
* @return void
**/

void help(){
  printf("\n");
  printf("cat <nom de fichier> : affiche a  l ecran le contenu d un fichier si l utilisateur a les droits\n");
  printf("\n");
  printf("rm <nom de fichier> : supprime un fichier du systeme si l utilisateur a les droits\n");
  printf("\n");
  printf("cr <nom de fichier> : cree un nouveau fichier sur le systeme, le proprietaire est l utilisateur.\n");
  printf("\n");
  printf("edit <nom de fichier> : edite un fichier pour modifier son contenu si l utilisateur a les droits\n") ;
  printf("\n");
  printf("load <nom de fichier> : copie le contenu d un fichier du systeme hote sur le systeme avec le meme nom\n ");
  printf("\n");
  printf("store <nom de fichier> : copie le contenu d un fichier du systeme sur hote avec le meme nom\n");
  printf("\n");
  printf("chown <nom de fichier> <login autre utilisateur> change le proprietaire d un fichier\n");
  printf("\n");
  printf("chmod <nom de fichier> <droit> change les droits d’un fichier pour tous les autres utilisateurs\n");
  printf("\n");
  printf("listusers : affiche la liste des utilisateurs du systeme\n");
  printf("\n");
  printf("adduser : Ajouter un utilisateur , si l'utilisateur est le root\n");
  printf("\n");
  printf("rmuser : Supprimer un utilisateur , si l'utilisateur est le root\n");
  printf("\n");
  printf("quit : Quitter le sytème\n");
  printf("\n");
  printf("exit : Quitter la session en cours\n");
  printf("\n");
  printf("clear : efface le contenu du terminal\n");
  printf("\n");
}

/**
* @brief charge un fichier du systeme sur l'ordinateur de l'host_file
* @note: le fichier aura le meme nom que le fichier du systeme
* @param char* nom_du_fichier a transferer
* @return int si le fichier existe et que le transfert s'est bien passé , 0 sinon
**/

int store(cmd_t* commande){
  char *filename = commande->tabArgs[1];
  if(commande->nbArgs != 2){
    printf("Usage : %s <nom de fichier>\n", commande->tabArgs[0]);
    return 0;
  }
  int pos = search_file_inode(filename);

  if(pos==-1){
    printf("\033[0;31m"); //couleur
    printf("Fichier inexistant\n");
    printf("\033[0m"); //couleur
    return 0;
  }
  printf("\033[0;34m"); //couleur
  printf("Copie du fichier %s dans le repertoire Stockage_file\n" , filename);
  printf("\033[0m"); //couleur

  store_file_to_host(filename);
  return 1;
}

/**
* @brief charge un fichier de l'ordinateur hote sur le systeme
* @note: le fichier aura le meme nom que le fichier transfere
* @param char* nom_du_fichier a transferer
* @return int si le fichier existe et que le transfert s'est bien passé , 0 sinon
**/

int load(cmd_t* commande){

  if(commande->nbArgs != 2){

    printf("Usage : %s <nom de fichier>\n", commande->tabArgs[0]);
    return 0;
  }

  if(load_file_from_host(commande->tabArgs[1])==0){
    printf("Erreur\n");
    return 0;
  }
  int pos = search_file_inode(commande->tabArgs[1]);
  strcpy(virtual_disk_sos->inodes[pos].filename , commande->tabArgs[1]);
  printf("\033[0;34m"); //couleur
  printf("Copie du fichier %s sur le systeme\n", commande->tabArgs[1]);
  printf("\033[0m"); //couleur

  return 1;
}

/**
* @brief demande a l'user un login et un mdp , cherche une correspondance dans le fichier passwd , et si une correspondance existe , l'user se connecte
* @note: l'user aura acces a chaque commande du systeme
* @param void
* @return int : 1 si l'user a pu se connecter , 0 sinon
**/

int connexion(){
  char password[FILENAME_MAX_SIZE];
  char login[FILENAME_MAX_SIZE];
  int erreur = 0;
  char hash[SHA256_BLOCK_SIZE*2 + 1];
  int utilisateur = 1;
  int mot_de_passe = 1;
  int connexion = 1;
  int id;

  while(connexion){
    while(utilisateur){
      printf("Veuillez saisir un nom d'utilisateur : ");
      fgets(login , FILENAME_MAX_SIZE , stdin);
      enlever_retour_ligne(login);
      id = search_login(login);

      if(id==-1 || strlen(login)==0){
        printf("\033[0;31"); //couleur
        printf("   Nom d'utilisateur incorrect\n");
        printf("\033[0m"); //couleur
      }

      else{
        utilisateur = 0;
      }
    }

    if(!utilisateur){

      while(mot_de_passe && erreur!=3){
        printf("Saisissez le mot de passe : ");
        fgets(password , FILENAME_MAX_SIZE , stdin);
        enlever_retour_ligne(password);
        sha256ofString((BYTE *) password, hash);

        if(strcmp(virtual_disk_sos->users_table[id].passwd , hash) ==0){
          mot_de_passe = 0;
        }

        else{
          printf("\033[0;31m"); //couleur
          printf("Mot de passe incorrect\n ");
          printf("\033[0m"); //couleur
          erreur++;

          if(erreur==3){
            printf("\033[0;31m"); //couleur
            printf("Nombre d'essai max atteint , fermeture système\n");
            printf("\033[0m"); //couleur
            save_disk_sos();
            return 0;
          }
        }
      }
    }

    if(!utilisateur && !mot_de_passe){
      printf("\nTapez -help a tout moment pour connaitre les commandes utilisables\n");
      new_session(login);
      connexion=0;
      return 1;

    }
  }
  return 0;
}

/**
* @brief interprete de commande qui va executer les cpommandes saisies par l'user connecte
* @note contient un tableau de chaine de caractere commande qui contient les arguments de la commande
* @param void
* @return void
**/

void interprete_commande(){

  /* On cherche à récupérer, un à un, tous les mots (token) de la phrase
  et on commence par le premier.
  exemple: l'user rentre la chaine "listusers 3" , le tableau commande va prendre ces 2 valeurs
  commande[0] = listusers , commande[1] = 3 , la fonction strtoken coupe la chaine de caractere avec le separateur espace
  et affecte les valeurs entre les espaces dans le tableau commande ,  dans ce cas la , la fonction listusers ne marcherait pas car on
  aurait 2 arguments . */

  if(connexion()==1){//si l'user a pu se connecter

  cmd_t *commande = malloc(sizeof(cmd_t));
  commande->tabArgs = malloc(10*sizeof(char*));
  int max = 10;

  int user;
  char pseudo[FILENAME_MAX_SIZE];

  char str[50];
  char *separators =" ";
  char *strToken;

  while(interprete){

    //récupérer le pseudo
    user = get_session();
    strcpy(pseudo, virtual_disk_sos->users_table[user].login);

    //taper la commande
    printf("\n[%s] Saisissez une commande $ " , pseudo );
    fgets(str, 50 , stdin);
    enlever_retour_ligne(str);
    printf("\n");

    //creer un tab de commande argv et le nombre de commande argc
    commande->nbArgs = 0;
    strToken = strtok (str, separators);
    while (strToken != NULL){

      commande->tabArgs[commande->nbArgs] = strToken;
      commande->nbArgs++;
      if(commande->nbArgs == max){
        commande->tabArgs = realloc(commande->tabArgs, max*2*sizeof(char*));
        max *= 2;
      }

      strToken = strtok (NULL, separators);
    }


    //debut appel des commandes
    if(commande->nbArgs > 0){

      if(strcmp(commande->tabArgs[0], "cr") == 0)
      cr(commande);

    }

    if(strcmp(commande->tabArgs[0], "rm") == 0){
      rm(commande);

    }

    if(strcmp(commande->tabArgs[0], "ls") == 0){
      ls(commande);
    }

    if(strcmp(commande->tabArgs[0], "edit") == 0){
      edit_file(commande);
    }

    if(strcmp(commande->tabArgs[0], "cat") == 0){
      cat(commande);
    }

    if(strcmp(commande->tabArgs[0], "chmod") == 0){
      chmod(commande);
    }

    if(strcmp(commande->tabArgs[0] , "-help")==0){
      help();
    }

    if(strcmp(commande->tabArgs[0] , "rmuser")==0){
      rmuser(commande);
    }

    if(strcmp(commande->tabArgs[0] , "adduser")==0){
      adduser(commande);
    }

    if(strcmp(commande->tabArgs[0] , "listusers")==0){
      listusers();
    }

    if(strcmp(commande->tabArgs[0] , "chown")==0){
      chown(commande);
    }

    if(strcmp(commande->tabArgs[0] , "store")==0){
      store(commande);
    }
                //pas de else
    if(strcmp(commande->tabArgs[0] , "load")==0){
      load(commande);
    }

    if(strcmp(commande->tabArgs[0] , "exit")==0){
      deconnexion();
      connexion();
    }

    if(strcmp(commande->tabArgs[0] , "clear")==0){
      clear();
    }

    if(strcmp(commande->tabArgs[0] , "credit")==0){
      credit();
    }

    if(strcmp(commande->tabArgs[0] , "quit")==0){
      quit();
    }

  }
  free(commande->tabArgs);
  free(commande);
}
}

int main(void) {
  if(init_disk_sos("../Dossier_Disque/Disque"))
  return 1;

  disp_design_os(true);
  interprete_commande();



  return 0;
}
