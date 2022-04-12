#include "header.h"
#include "Couche1.h"
#include "Couche2.h"

extern virtual_disk_t *virtual_disk_sos;

int main() {
  init_disk_sos("../Dossier_Disque/Disque");
  init_first_time_super_block();
  init_first_time_inodes_tables();

  printf("\nnb file=%d | nb user=%d | nb block=%d | first_byte=%d\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);
  printf("\n\nINIT_INODE\n\n");
  printf("Superbloc :\n");
  for (int i = 0; i < INODE_TABLE_SIZE; i++) {
    init_inode("0123456789"+i, 514, virtual_disk_sos->super_block.first_free_byte);
    printf("nb file=%2d | nb user=%d | nb block=%6d | first_byte=%6d\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);
  }


  printf("\n");

  printf("table inodes :\n");
  for (int i = 0; i < INODE_TABLE_SIZE; i++) {
    printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
  }

  printf("\n\nDELETE_INODE\n\n");

  delete_inode(4);
  delete_inode(2);
  delete_inode(6);
  init_inode("Nouveau.txt", 514, virtual_disk_sos->super_block.first_free_byte);

  printf("Superbloc :\n");
  printf("nb file=%d | nb user=%d | nb block=%d | first_byte=%d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

  printf("table inodes :\n");
  for (int i = 0; i < INODE_TABLE_SIZE; i++) {
    printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
  }
  return 0;
}
