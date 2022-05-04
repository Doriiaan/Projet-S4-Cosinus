
#include "Couche1.h"
#include "Couche2.h"
#include "Couche3.h"

extern virtual_disk_t *virtual_disk_sos;

#define FIRST_TIME
//#define TEST_ADD_INODE
//#define TEST_DELETE_INODE
#define TEST_WRITE_FILE

int main() {

  init_disk_sos("../Dossier_Disque/Disque");


  #ifdef FIRST_TIME
    init_first_time_super_block();
    init_first_time_inodes_tables();
    init_first_time_user_table();
  #endif


  printf("Superbloc :\n");
  printf("nb file=%d | nb user=%d | nb block=%d | first_byte=%d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

  printf("Table inodes :\n");
  for (int i = 0; i < INODE_TABLE_SIZE; i++) {
    printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
  }


  #ifdef TEST_ADD_INODE
    printf("\n\n---------------------------------------------------------------\n");
    printf("#INIT_INODE\n\n");

    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
      char name[20] = "file ";
      char nombre[10];
      sprintf(nombre, "%d", i);
      strcat(name, nombre);
      init_inode(name, 514, virtual_disk_sos->super_block.first_free_byte);
    }
    printf("Superbloc :\n");
    printf("nb file=%2d | nb user=%d | nb block=%6d | first_byte=%6d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

    printf("Table inodes :\n");
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
      printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
    }
  #endif

  #ifdef TEST_DELETE_INODE
    printf("\n\n---------------------------------------------------------------\n");
    printf("#DELETE_INODE\n\n");

    delete_inode("file 1");
    delete_inode("file 4");
    delete_inode("file 1");

    init_inode("Nouveau.txt", 514, virtual_disk_sos->super_block.first_free_byte);

    printf("Superbloc :\n");
    printf("nb file=%d | nb user=%d | nb block=%d | first_byte=%d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

    printf("Table inodes :\n");
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
      printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
    }

  #endif

  #ifdef TEST_WRITE_FILE

    add_user("root", "root");
    new_session("root");

    file_t file;
    for (int i = 0; i < MAX_FILE_SIZE-1; i++) {
      if((i%30) == 0)
        file.data[i] = '\n';
      else
        file.data[i] = 'a';
    }
    file.data[MAX_FILE_SIZE-1] = (uchar)EOF;
    file.size = MAX_FILE_SIZE;
    write_file("test",file);

    printf("Superbloc :\n");
    printf("nb file=%d | nb user=%d | nb block=%d | first_byte=%d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

    printf("Table inodes :\n");
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
      printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
    }

    printf("\nTable user :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("userid = %8d | login = %32s | passeword = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
    }

    printf("\nEDIT FILE\n");
    file_t file2;
    for (int i = 0; i < 99; i++) {
      if((i%30) == 0)
        file2.data[i] = '\n';
      else
        file2.data[i] = 'a';
    }
    file2.data[99] = (uchar)EOF;
    file2.size = 100;
    write_file("test",file2);

    printf("Superbloc :\n");
    printf("nb file=%d | nb user=%d | nb block=%d | first_byte=%d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

    printf("Table inodes :\n");
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
      printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
    }

    printf("\nTable user :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("userid = %8d | login = %32s | passeword = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
    }
  #endif

  if(save_disk_sos())
    return 1;


  printf("\nSAVE\n");
  return 0;
}
