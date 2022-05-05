/**
* @file Couche3.h
* @author Groupe Cosinus
* @brief Header de l'Implémentation de la couche 3
* @date Avril 2022
*
*/

#include "Couche3.h"

extern virtual_disk_t *virtual_disk_sos;

session_t *session;


/**
* @brief Ecrit la table d'utilisateurs de la variable systeme sur le disque
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable systeme déjà initialisé
*/
int write_users_table(void){

  file_t file;
  file.size = 0;
  char c[1]; c[0] = '\n'; //obligatoire si je ne veux pas de problème de segmentation (pas propre)

  for (int i = 0; i < NB_USERS; i++) {
    if(strcmp(virtual_disk_sos->users_table[i].login, "\0") != 0){
      if(i == 0)
        strcpy((char *)file.data, virtual_disk_sos->users_table[i].login);
      else
        strcat((char *)file.data, virtual_disk_sos->users_table[i].login);
      strcat((char *)file.data, ":");
      strcat((char *)file.data, virtual_disk_sos->users_table[i].passwd);
      strcat((char *)file.data, c);
      file.size += (strlen(virtual_disk_sos->users_table[i].login) + (SHA256_BLOCK_SIZE*2) + 2) ;
    }
  }

  write_file("passwd", file);

  return 0;
}


/**
* @brief Lis la valeur de la table d'utilisateurs sur le disque et l'écrit sur la variable systeme
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable systeme déjà initialisé
*/
int read_users_table(void){

  file_t file;
  if(read_file("passwd", &file) == 0){
    return 0;
  }

  int nb_users = 0;
  int i = 0;
  int i_champs;

  while(i < (int)file.size){

    i_champs = 0;
    while(file.data[i] != ':'){
      virtual_disk_sos->users_table[nb_users].login[i_champs] = file.data[i];
      i_champs++;
      i++;
    }
    i++;
    i_champs = 0;
    while(i_champs < 64){
      virtual_disk_sos->users_table[nb_users].passwd[i_champs] = file.data[i];
      i_champs++;
      i++;
    }
    i++;

    nb_users++;
  }

  if(nb_users < NB_USERS){
    for (int i = nb_users; i < NB_USERS; i++) {
      strcpy(virtual_disk_sos->users_table[nb_users].login, "\0");
    }
  }

  return 0;
}


/**
* @brief Retourne l'incide d'un utilisateur libre sur la table d'utilisateurs
* @param void
* @return int : indice d'utilisateur libre
* @pre variable systeme déjà initialisé
*/
int get_unused_user(void){

  if(virtual_disk_sos->super_block.number_of_users == NB_USERS)
    return -1;

  for (int i = 0; i < NB_USERS; i++) {
    if(strcmp(virtual_disk_sos->users_table[i].login, "\0") == 0)
      return i;
  }

  return -1;
}


/**
* @brief Retourne l'indice de l'utilisateur rechercher dans la table d'utilisateurs
* @param char *login : login de l'utilisateur rechercher
* @return int : indice de l'utilisateur dans la table d'utilisateurs
* @pre variable systeme déjà initialisé && len(name_of_file) < FILENAME_MAX_SIZE
*/
int search_login(char *login){
  assert(strlen(login) < FILENAME_MAX_SIZE); //strlen compte pas le '\0'

  int id = -1;
  for (int i = 0; i < NB_USERS; i++) {
    if(strcmp(login, virtual_disk_sos->users_table[i].login) == 0){
      id =  i;
    }
  }
  return id;
}


/**
* @brief Ajoute un utilisateur au systeme
* @param char *login : login de l'utilisateur
* @param char *password : password non hashe de l'utilisateur
* @return int : id de l'utilisateur créer ou -1 en cas d'erreurs
* @pre variable systeme déjà initialisé && len(name_of_file) < FILENAME_MAX_SIZE
* @note Si le login est déjà existant ou qu'il n'y a plus d'utilisateurs libres
* retourne -1
*/
int add_user(char *login, char *password_clair){
  assert(strlen(login) < FILENAME_MAX_SIZE); //strlen compte pas le '\0'
  if(search_login(login) != -1){
    return -1;
  }

  int id;
  if((id = get_unused_user()) == -1){
    return -1;
  }

  user_t new_user;
  char hash_password[SHA256_BLOCK_SIZE*2 + 1];

  sha256ofString((BYTE *) password_clair, hash_password);

  strcpy(new_user.passwd, hash_password);
  strcpy(new_user.login, login);
  virtual_disk_sos->users_table[id] = new_user;
  virtual_disk_sos->super_block.number_of_users++;

  write_users_table();

  return id;
}


/**
* @brief Supprime l'utilisateur de nom login dans la table d'utilisateur et de
* la session si nécessaire
* @param char *login: login de l'utilisateur à supprimer
* @return int : id de l'utilisateur supprimé ou -1 en cas d'erreurs
* @pre variable systeme déjà initialisé && len(name_of_file) < FILENAME_MAX_SIZE
* @note Impossible de supprimé l'utilisateur root
*/
int delete_user(char *login){
  assert(strlen(login) < FILENAME_MAX_SIZE); //strlen compte pas le '\0'

  int id;
  if((id=search_login(login)) == -1 || id == 0){
    return -1;
  }

  strcpy(virtual_disk_sos->users_table[id].login, "\0");
  virtual_disk_sos->super_block.number_of_users--;
  if(session->userid == id){
    del_session();
  }

  write_users_table();
  return id;
}


/**
* @brief Cette fonction initialise la table d'utilisateurs pour la première fois
* @param void
* @return void
* @pre variable systeme déjà initialisé
*/
void init_first_time_user_table(void){

  for (int i = 0; i < NB_USERS; i++) {
    strcpy(virtual_disk_sos->users_table[i].login, "\0");
  }
  write_users_table();
}


/**
* @brief Ouvre une nouvelle session pour l'utilisateur et supprime les autres
* @param char *login : login de l'utilisateur pour lequel une session est ouverte
* @return int : 0 si tout c'est bien passé, 1 sinon
* @pre variables systeme et session déjà initialisé && len(name_of_file) < FILENAME_MAX_SIZE
*/
int new_session(char *login){
  assert(strlen(login) < FILENAME_MAX_SIZE); //strlen compte pas le '\0'

  int id;
  if((id=search_login(login)) == -1){
    return 1;
  }

  session->userid = id;
  return 0;
}


/**
* @brief Supprime la session en cours
* @param void
* @return void
* @pre variable session déjà initialisé
*/
void del_session(void){

  session->userid = -1;
}


/**
* @brief Retourne l'id d'utilisateur de la session en cours
* @param void
* @return int : id de l'utilisateur ou -1
* @pre variable session déjà initialisé
*/
int get_session(void){

  return session->userid;
}
