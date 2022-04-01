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
* @brief function to write super_block on the disk
* @param super_block_t *super_block a pointer on the super_block
* @return nothing
*/
void write_super_block(super_block_t *super_block){

  if(fseek(virtual_disk_sos->storage , 0 , SEEK_SET) != 0){
    printf("Erreur déplacement curseur sur disque\n");
    exit(1);
  }
	if(fwrite(super_block, BLOCK_SIZE, SUPER_BLOCK_SIZE, virtual_disk_sos->storage) != SUPER_BLOCK_SIZE){
    printf("Erreur lecture sur disque\n");
    exit(2);
  }
}


/**
* @brief Lis la valeur du super bloc et la rentre dans une variable déjà initilisé
* @param super_block_t *super_block : Super block déjà initialisé
* @return nothing
*/
void read_super_block(super_block_t *super_block){

  if(fseek(virtual_disk_sos->storage , 0 , SEEK_SET) != 0){
    printf("Erreur déplacement curseur sur disque\n");
    exit(1);
  }

	if(fread(super_block , BLOCK_SIZE , SUPER_BLOCK_SIZE , virtual_disk_sos->storage) != SUPER_BLOCK_SIZE){
    printf("Erreur lecture sur disque\n");
    exit(2);
  }
}
