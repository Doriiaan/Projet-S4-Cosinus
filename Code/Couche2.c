#include "Couche2.h"


/**
* @brief function init and write the super block at the start of the disk
* @param nothing
* @return nothing
*/
void write_super_block(){

  super_block_t *super_block = malloc(sizeof(super_block_t));
  super_block->number_of_files = 0;
  super_block->number_of_users = 0;
  super_block->nb_blocks_used = 0;
  super_block->first_free_byte = INODES_START;
}
