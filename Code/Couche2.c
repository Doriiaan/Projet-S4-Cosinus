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
*/

#include "Couche2.h"

extern virtual_disk_t *virtual_disk_sos;


/**
* @brief Ecrit le super bloc de la variable systeme sur le disque
* @param void
* @return void
* @pre variable systeme déjà initialisé
* @note exit(1) -> erreur curseur : exit(2) -> erreur écriture
*/
void write_super_block(void){

  if(fseek(virtual_disk_sos->storage, 0, SEEK_SET) != 0){
    printf("Erreur déplacement curseur sur disque\n");
    exit(1);
  }
	if(fwrite(&(virtual_disk_sos->super_block), BLOCK_SIZE, SUPER_BLOCK_SIZE, virtual_disk_sos->storage) != SUPER_BLOCK_SIZE){
    printf("Erreur écriture sur disque\n");
    exit(2);
  }
}


/**
* @brief Lis la valeur du super bloc sur le disque et l'écrit sur la variable systeme
* @param void
* @return void
* @pre variable systeme déjà initialisé
* @note exit(1) -> erreur curseur : exit(2) -> erreur lecture
*/
void read_super_block(void){

  if(fseek(virtual_disk_sos->storage, 0, SEEK_SET) != 0){
    printf("Erreur déplacement curseur sur disque\n");
    exit(1);
  }

	if(fread(&(virtual_disk_sos->super_block), BLOCK_SIZE, SUPER_BLOCK_SIZE, virtual_disk_sos->storage) != SUPER_BLOCK_SIZE){
    printf("Erreur lecture sur disque\n");
    exit(2);
  }
}


/**
* @brief Met à jour le premier octet libre du super bloc dans la variable
* du systeme et sur le disque
* @param octet à mettre à jour
* @return void
* @pre variable systeme déjà initialisé
* @note La focntion se charge du cas ou byte > first_free_byte
*/
void update_first_free_byte_super_block(uint byte){

  if(byte < virtual_disk_sos->super_block.first_free_byte){
    virtual_disk_sos->super_block.first_free_byte = byte;
    write_super_block();
  }
}


/**
* @brief Retourne le premier octet libre du disque
* @param void
* @return premier octet libre du disque ou -1 si il n'y a pas d'octet libre
* @pre variable systeme déjà initialisé
*/
int search_free_bytes(void){

  int i = 0;
  while(i < INODE_TABLE_SIZE && virtual_disk_sos->inodes[i].first_byte != 0){
    i++;
  }
  return (i >= INODE_TABLE_SIZE) ? -1 : (int)virtual_disk_sos->inodes[i].first_byte;
}

/**
* @brief Lis la valeur de la table d'inodes sur le disque et l'écrit sur la variable systeme
* @param void
* @return void
* @pre variable systeme déjà initialisé
* @note exit(1) -> erreur curseur : exit(2) -> erreur lecture
*/
void read_inodes_table(void){

  if(fseek(virtual_disk_sos->storage, 0, SEEK_SET) != 0){
    printf("Erreur déplacement curseur sur disque\n");
    exit(1);
  }

  if(fread(&(virtual_disk_sos->inodes), INODE_SIZE, INODE_TABLE_SIZE, virtual_disk_sos->storage) != INODE_TABLE_SIZE){
    printf("Erreur lecture sur disque\n");
    exit(2);
  }
}


/**
* @brief Ecrit la table d'inodes de la variable systeme sur le disque
* @param void
* @return void
* @pre variable systeme déjà initialisé
* @note exit(1) -> erreur curseur : exit(2) -> erreur écriture
*/
void write_inodes_table(void){

  if(fseek(virtual_disk_sos->storage , 0 , SEEK_SET) != 0){
    printf("Erreur déplacement curseur sur disque\n");
    exit(1);
  }
  if(fwrite(&(virtual_disk_sos->inodes), INODE_SIZE, INODE_TABLE_SIZE, virtual_disk_sos->storage) != INODE_TABLE_SIZE){
    printf("Erreur écriture sur disque\n");
    exit(2);
  }
}


/**
* @brief Supprime une inode de la table d'inode et met à jour le super bloc
* @param int indice_inode : indice de l'inode à supprimer
* @return void
* @pre variable systeme déjà initialisé
* @note La fonction gère si un indice qui correspond à aucun fichier est donné en paramètre
*/
void delete_inode(int indice_inode){


  if(virtual_disk_sos->inodes[indice_inode].first_byte == 0){
    return;
  }
  else{
    // mettre à jour super_block
    update_first_free_byte_super_block(virtual_disk_sos->inodes[indice_inode].first_byte);
    virtual_disk_sos->super_block.number_of_files--;
    virtual_disk_sos->super_block.nb_blocks_used -= virtual_disk_sos->inodes[indice_inode].nblock;

    // reecrire la table d'inodes
    int i = indice_inode;
    while(i < INODE_TABLE_SIZE-1 && virtual_disk_sos->inodes[i].first_byte != 0){
      virtual_disk_sos->inodes[i] = virtual_disk_sos->inodes[i+1];
      i++;
    }
    virtual_disk_sos->inodes[i].first_byte = 0; // -> rend l'inode disponible

    // mettre a jour disque
    write_inodes_table();
    write_super_block();
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
