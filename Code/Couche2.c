/**
* @file Couche2.c
* @author Groupe Cosinus
* @brief Implémentation de la couche 2
* @date Avril 2022
* @note La table d'inode contient 10 inodes. Les inodes sont soit utilisé, ils
*       ont une position first_byte !=0, soit libre ils ont une postion first_byte == 0.
*       Les fonctions de lectures et ecrire du super bloc et de la table d'inodes
*       n'initialise rien, ils ne font que lire et ecrire sur le disque et sur
*       la variable systeme.
*       Les fonctions qui touchent au super bloc et à la table d'inode, actualisent
*       ces derniers sur le disque et sur la variable systeme sauf si le contraire
*       est précisé.
*/

#include "Couche2.h"

extern virtual_disk_t *virtual_disk_sos;


/**
* @brief Ecrit le super bloc de la variable systeme sur le disque
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable systeme déjà initialisé
*/
int write_super_block(void){

  if(fseek(virtual_disk_sos->storage, 0, SEEK_SET) != 0){
    return 1;
  }
	if(fwrite(&(virtual_disk_sos->super_block), BLOCK_SIZE, SUPER_BLOCK_SIZE, virtual_disk_sos->storage) != SUPER_BLOCK_SIZE){
    return 1;
  }
  return 0;
}


/**
* @brief Lis la valeur du super bloc sur le disque et l'écrit sur la variable systeme
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable systeme déjà initialisé
*/
int read_super_block(void){

  if(fseek(virtual_disk_sos->storage, 0, SEEK_SET) != 0){
    return 1;
  }

	if(fread(&(virtual_disk_sos->super_block), BLOCK_SIZE, SUPER_BLOCK_SIZE, virtual_disk_sos->storage) != SUPER_BLOCK_SIZE){
    return 1;
  }
  return 0;
}


/**
* @brief Met à jour le premier octet libre du super bloc dans la variable
* du systeme et non sur le disque
* @param uint byte : octet à mettre à jour
* @return void
* @pre variable systeme déjà initialisé
* @note Aucun test de vérification d'espace disque n'est effectué
*/
void update_first_free_byte_super_block(uint byte){

  virtual_disk_sos->super_block.first_free_byte = byte;
}


/**
* @brief Lis la valeur de la table d'inodes sur le disque et l'écrit sur la variable systeme
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable systeme déjà initialisé
*/
int read_inodes_table(void){

  if(fseek(virtual_disk_sos->storage, INODES_START, SEEK_SET) != 0){
    return 1;
  }

  if(fread(&(virtual_disk_sos->inodes), BLOCK_SIZE, (INODE_SIZE)*INODE_TABLE_SIZE, virtual_disk_sos->storage) != (INODE_SIZE)*INODE_TABLE_SIZE){
    return 1;
  }
  return 0;
}


/**
* @brief Ecrit la table d'inodes de la variable systeme sur le disque
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable systeme déjà initialisé
* @note exit(1) -> erreur curseur : exit(2) -> erreur écriture
*/
int write_inodes_table(void){

  if(fseek(virtual_disk_sos->storage , INODES_START , SEEK_SET) != 0){
    return 1;
  }

  if(fwrite(&(virtual_disk_sos->inodes), BLOCK_SIZE, (INODE_SIZE)*INODE_TABLE_SIZE, virtual_disk_sos->storage) != (INODE_SIZE)*INODE_TABLE_SIZE){
    return 1;
  }
  return 0;
}


/**
* @brief Supprime une inode de la table d'inode et met à jour le super bloc
* @param int indice_inode : indice de l'inode à supprimer
* @return int : 0 si tout s'est bien passé, 1 s'il y a eu une erreur, 2 si l'inode est déjà libre
* @pre variable systeme déjà initialisé && len(name_of_file) < FILENAME_MAX_SIZE
* @note La fonction gère si un indice qui correspond à aucun fichier est donné en paramètre
*/
int delete_inode(char *name_of_file){
  assert(strlen(name_of_file) < FILENAME_MAX_SIZE); //strlen compte pas le '\0'

  int indice_inode;
  if((indice_inode=search_file_inode(name_of_file)) == -1){
    return 2;
  }
  else{
    // mettre à jour super_block
    virtual_disk_sos->super_block.number_of_files--;
    virtual_disk_sos->super_block.nb_blocks_used -= virtual_disk_sos->inodes[indice_inode].nblock;

    /*
      si l'inode à supprimer est la dernière inode dans la table qui représente un fichier
      alors l'octet qui suit l'inode est le first_free_byte ou c'est la derniere inode,
      donc on decale le first_free_byte au first_byte de l'inode qu'on va supprimer
    */
    if(indice_inode + 1 == INODE_TABLE_SIZE || virtual_disk_sos->inodes[indice_inode+1].first_byte == 0){
         update_first_free_byte_super_block(virtual_disk_sos->inodes[indice_inode].first_byte);
       }

    // reecrire la table d'inodes
    int i = indice_inode;
    while(i < INODE_TABLE_SIZE-1 && virtual_disk_sos->inodes[i].first_byte != 0){
      virtual_disk_sos->inodes[i] = virtual_disk_sos->inodes[i+1];
      i++;
    }
    virtual_disk_sos->inodes[i].first_byte = 0; // -> rend l'inode disponible


    return 0;
  }
}


/**
* @brief Retourne l'indice dans la table d'inode du premier inode libre
* @param void
* @return indice du premier inode libre ou -1 si tous les inodes sont occupés
* @pre variable systeme déjà initialisé
*/
int get_unused_inode(void){

  int i = 0;
  while(i < INODE_TABLE_SIZE && virtual_disk_sos->inodes[i].first_byte != 0){
    i++;
  }
  return (i >= INODE_TABLE_SIZE) ? -1 : i;
}


/**
* @brief Ecrit un nouvel inode à la suite des autres sur la table d'inode
* @param char[FILENAME_MAX_SIZE] inclut \'0' name_of_file : nom du fichier
* @param uint size  : taille du fichier
* @param uint first_byte : premier octet du fichier sur le disque
* @return int : 0 si tout s'est bien passé, 1 sinon (ex : taille max table inode attteinte)
* @pre variable systeme déjà initialisé && len(name_of_file) < FILENAME_MAX_SIZE
* @note Met à jour le la table d'inode et le super bloc
*       first_free_byte, nblock et number_of_files.
*/
int init_inode(char *name_of_file, uint size, uint first_byte){
  assert(strlen(name_of_file) < FILENAME_MAX_SIZE); //strlen compte pas le '\0'

  if(search_file_inode(name_of_file) != -1)
    return 1;

  int indice_new;
  if((indice_new = get_unused_inode()) == -1 ){
    return 1;
  }
  inode_t new;
  strcpy(new.filename, name_of_file);
  new.size = size;
  new.first_byte = first_byte;
  new.nblock = computenblock(size);
  virtual_disk_sos->inodes[indice_new] = new;

  uint first_free_byte_sb = (first_byte + size) + (4 - (first_byte + size)%4); //positione au debut du prochain bloc
  update_first_free_byte_super_block(first_free_byte_sb);
  virtual_disk_sos->super_block.nb_blocks_used += new.nblock;
  virtual_disk_sos->super_block.number_of_files++;

  return 0;
}


/**
* @brief Retourne l'indice de l'inode qui pointe vers un fichier de nom name_of_file
* @param char name_of_file[MAX_FILE_SIZE] : nom du fichier à chercher
* @return int : indice de l'inode ou -1 s'il n'existe pas
* @pre variable systeme déjà initialisé && len(name_of_file) <= FILENAME_MAX_SIZE
*/
int search_file_inode(char *name_of_file){
  assert(strlen(name_of_file) < FILENAME_MAX_SIZE); //strlen compte pas le '\0'

  int indice = -1;
  for (int i = 0; i < INODE_TABLE_SIZE; i++) {
    if(virtual_disk_sos->inodes[i].first_byte != 0 && strcmp(name_of_file, virtual_disk_sos->inodes[i].filename) == 0){
      indice =  i;
    }
  }
  return indice;
}


/**
* @brief Cette fonction initialise le super bloc pour la première fois
* @param void
* @return void
* @pre variable systeme déjà initialisé
*/
void init_first_time_super_block(void){
  virtual_disk_sos->super_block.number_of_files = 0;
  virtual_disk_sos->super_block.number_of_users = 1; //root
  virtual_disk_sos->super_block.nb_blocks_used = (SUPER_BLOCK_SIZE + INODE_TABLE_SIZE*(INODE_SIZE) + USER_SIZE*NB_USERS ); //root
  virtual_disk_sos->super_block.first_free_byte = (USER_SIZE*NB_USERS + SUPER_BLOCK_SIZE + INODE_TABLE_SIZE*(INODE_SIZE))*BLOCK_SIZE + 1;

}


/**
* @brief Cette fonction initialise la table d'inodes pour la première fois
* @param void
* @return void
* @pre variable systeme déjà initialisé
*/
void init_first_time_inodes_tables(void){

  for (int i = 0; i < INODE_TABLE_SIZE; i++) {
    virtual_disk_sos->inodes[i].first_byte = 0;
    virtual_disk_sos->inodes[i].size = 0;
    strcpy(virtual_disk_sos->inodes[i].filename, "");
  }
}
