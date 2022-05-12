
#include "Couche1.h"
#include "Couche2.h"
#include "Couche3.h"
#include "Couche4.h"
#include "Couche5.h"

extern virtual_disk_t *virtual_disk_sos;

//#define FIRST_TIME
//#define TEST_ADD_INODE
//#define TEST_DELETE_INODE
//#define TEST_WRITE_FILE
//#define TEST_READ_FILE
//#define TEST_INTERPRETE


int main() {
  if(init_disk_sos("../Dossier_Disque/Disque"))
    return 1;

  #ifdef FIRST_TIME
    init_first_time_super_block();
    init_first_time_inodes_tables();
    init_first_time_user_table();
    add_user("root", "root");
  #endif

  printf("\nSuperbloc :\n");
  printf("nb file=%d | nb user=%d | nb block=%d | first_byte=%d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

  printf("Table inodes :\n");
  for (int i = 0; i < INODE_TABLE_SIZE; i++) {
    printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
  }

  printf("\nTable users :\n");
  for (int i = 0; i < NB_USERS; i++) {
    printf("user id = %3d | login = %32s | password = %s\n", i, virtual_disk_sos->users_table[i].login,virtual_disk_sos->users_table[i].passwd);
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

    printf("\nADD FILE\n");
    new_session("root");

    file_t file;
    for (int i = 0; i < MAX_FILE_SIZE-1; i++) {
        file.data[i] = 'a';
    }

    file.data[MAX_FILE_SIZE-1] = '\3';
    file.size = MAX_FILE_SIZE;
    write_file("test1",file);
    write_file("test2",file);

    printf("\nSuperbloc :\n");
    printf("nb file=%d | nb user=%d | nb block=%d | first_byte=%d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

    printf("Table inodes :\n");
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
      printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
    }

    printf("\nTable users :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("user id = %3d | login = %32s | password = %s\n", i, virtual_disk_sos->users_table[i].login,virtual_disk_sos->users_table[i].passwd);
    }

  #endif

  #ifdef TEST_READ_FILE
  printf("\nREAD FILE\n\n");
  file_t file2;
  read_file("test", &file2);

  printf("%s\n\n", (char *) file2.data);

  #endif

  #ifdef TEST_INTERPRETE

  printf("\nTable users :\n");
  for (int i = 0; i < NB_USERS; i++) {
    printf("user id = %3d | login = %32s | password = %s\n", i, virtual_disk_sos->users_table[i].login,virtual_disk_sos->users_table[i].passwd);
  }
  printf("\n\n");
  interprete_commande();

  #endif


  #ifndef TEST_INTERPRETE

    if(save_disk_sos())
      return 1;

    printf("SAVE\n");

  #endif



  return 0;
}
