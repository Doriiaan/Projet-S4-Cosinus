/**
* @file Couche2.c
* @author Groupe Cosinus
* @brief Implémentation de la couche 2
* @date Avril 2022
*
*/

#include "Couche2.h"

extern virtual_disk_t *virtual_disk_sos;


/**
* @brief fonction pour ecrire le superbloc sur le disque
* @param void
* @return void
* @pre variable systeme déjà initialisé
*/
void write_super_block(void){

  if(fseek(virtual_disk_sos->storage , 0 , SEEK_SET) != 0){
    printf("Erreur déplacement curseur sur disque\n");
    exit(1);
  }
	if(fwrite(&(virtual_disk_sos->super_block), BLOCK_SIZE, SUPER_BLOCK_SIZE, virtual_disk_sos->storage) != SUPER_BLOCK_SIZE){
    printf("Erreur lecture sur disque\n");
    exit(2);
  }
}


/**
* @brief Lis la valeur du super bloc et l'écrit sur le systeme
* @param void
* @return void
* @pre variable systeme déjà initialisé
*/
void read_super_block(void){

  if(fseek(virtual_disk_sos->storage , 0 , SEEK_SET) != 0){
    printf("Erreur déplacement curseur sur disque\n");
    exit(1);
  }

	if(fread(&(virtual_disk_sos->super_block) , BLOCK_SIZE , SUPER_BLOCK_SIZE , virtual_disk_sos->storage) != SUPER_BLOCK_SIZE){
    printf("Erreur lecture sur disque\n");
    exit(2);
  }
}


void update_first_free_byte_super_block(){

}


void read_inodes_table(void){

  if(fseek(virtual_disk_sos->storage , INODES_START , SEEK_SET) != 0){
    printf("Erreur déplacement curseur sur disque\n");
    exit(1);
  }

  if(fread(&(virtual_disk_sos->inodes) , BLOCK_SIZE , INODE_TABLE_SIZE*INODE_SIZE , virtual_disk_sos->storage) != INODE_TABLE_SIZE*INODE_SIZE){
    printf("Erreur lecture sur disque\n");
    exit(2);
  }
}

void write_inodes_table(void){

}
