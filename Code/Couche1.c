/**
* @file Couche1.c
* @author Groupe Cosinus
* @brief Implémentation de la couche 1
* @date Avril 2022
*
*/

#include "Couche1.h"
#include "Couche2.h"
#include "Couche3.h"

virtual_disk_t *virtual_disk_sos;

extern session_t *session;


/**
*  @brief Renvoit le nombre de blocs nécessaire pour stocker nb_octets
*  @param int nb_octets : Nombre d'octets
*  @return int : Nombre de blocs nécessaire pour stocker nb_octets
*/
int computenblock(int nb_octets){

  int nb_blocs = (nb_octets / BLOCK_SIZE);
  if(nb_octets%BLOCK_SIZE != 0) nb_blocs++;
  return nb_blocs;
}


/**
* @brief Ecrit un bloc à la position demande sur le disque
* @param int pos : Position à laquelle écrire le bloc
* @param block_t t : Bloc à écrire dans le disque
* @return 0 si tout c'est bien passé, 1 sinon
*/
int write_block(int pos , block_t t){

  if(fseek(virtual_disk_sos->storage, pos, SEEK_SET) != 0){
    return 1;
  }

  if(fwrite(t.data, BLOCK_SIZE, 1, virtual_disk_sos->storage) != 1){
    return 1;
  }
  return 0;
}


/**
* @brief Lis un bloc à la position pos sur le systeme
* @param int pos : Position à laquelle lire un bloc dans le systeme
* @param block_t *t : Variable qui stocke le bloc lu
* @return : Bloc qui à été lu
*/
int read_block(int pos, block_t *t){

  if(fseek(virtual_disk_sos->storage, pos, SEEK_SET) != 0){
    return 1;
  }

	if(fread(t->data, BLOCK_SIZE, 1, virtual_disk_sos->storage) != 1){
    return 1;
  }
	return 0;
}


/**
* @brief Création et initialisation de la variable disque
* @param : char* nom_repertoire_disque : Nom du répertoire qui contient le disque
* @return 0 si tout c'est bien passé, 1 sinon
*/
int init_disk_sos(char* nom_repertoire_disque){

  if((virtual_disk_sos = malloc(sizeof(virtual_disk_t))) == NULL)
    return 1;

  //creation chemin disque
  char path_disque[SIZE_PATH_DISQUE];
  strcpy(path_disque, nom_repertoire_disque);
  strcat(path_disque, "/d0");

  FILE *disque;
  if((disque = fopen(path_disque, "r+")) == NULL){
    return 1;
  }
  virtual_disk_sos->storage = disque;
  if(read_super_block() || read_inodes_table() || read_users_table())
    return 1;

  if((session = malloc(sizeof(session_t))) == NULL) // init variable globale session
    return 1;
  session->userid = -1;

  return 0;
}


/**
* @brief Ferme le sytème correctement et enregistre les données système sur le disque
* @param void
* @return int : 0 si tout c'est bien passé, 1 sinon
* @pre variable système déjà initialisé
* @note A n'utiliser qu'en cas de fermeture système
*/
int save_disk_sos(void){

  if(write_super_block() || write_inodes_table() || write_users_table()){
    return 1;
  }


  if(fclose(virtual_disk_sos->storage) == EOF){
    return 1;
  }

  free(session);
  free(virtual_disk_sos);
  return 0;
}
