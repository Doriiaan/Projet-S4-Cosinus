#include "header.h"
#include "Couche1.h"
#include "Couche2.h"
#include "Couche3.h"

extern virtual_disk_t *virtual_disk_sos;

#define FIRST_TIME 1
#define TEST_ADD_INODE 1
#define TEST_DELETE_INODE 1
#define TEST_ADD_USER 1
#define TEST_DELETE_USER 1
#define TEST_SESSION 1

int main() {

  init_disk_sos("../Dossier_Disque/Disque");


  if(FIRST_TIME){
    init_first_time_super_block();
    init_first_time_inodes_tables();
    init_first_time_user_table();
  }


  printf("Superbloc :\n");
  printf("nb file=%d | nb user=%d | nb block=%d | first_byte=%d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

  printf("Table inodes :\n");
  for (int i = 0; i < INODE_TABLE_SIZE; i++) {
    printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
  }

  printf("\nTables d'utilisateurs :\n");
  for (int i = 0; i < NB_USERS; i++) {
    printf("uid = %2d | login = %32s| hash_password = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
  }

  if(TEST_ADD_INODE){
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

    printf("\nTables d'utilisateurs :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("uid = %2d | login = %32s| hash_password = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
    }

  }

  if(TEST_DELETE_INODE){
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

    printf("\nTables d'utilisateurs :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("uid = %2d | login = %32s| hash_password = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
    }

  }

  if(TEST_ADD_USER){
    printf("\n\n---------------------------------------------------------------\n");
    printf("#ADD_USER\n\n");

    printf("Superbloc :\n");
    printf("nb file=%d | nb user=%d | nb block=%d | first_byte=%d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

    printf("Table inodes :\n");
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
      printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
    }

    printf("\nTables d'utilisateurs :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("uid = %2d | login = %32s| hash_password = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
    }

    printf("\nAJOUT");

    add_user("dorian", "azertyuiop");
    add_user("thomas", "123");
    add_user("caelan", "bonjour");
    add_user("enzo", "ahahahah");

    printf("\nTables d'utilisateurs :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("uid = %2d | login = %32s| hash_password = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
    }
  }

  if(TEST_DELETE_USER){
    printf("\n\n---------------------------------------------------------------\n");
    printf("#DELETE_USER\n\n");

    printf("Superbloc :\n");
    printf("nb file=%d | nb user=%d | nb block=%d | first_byte=%d\n\n", virtual_disk_sos->super_block.number_of_files, virtual_disk_sos->super_block.number_of_users, virtual_disk_sos->super_block.nb_blocks_used, virtual_disk_sos->super_block.first_free_byte);

    printf("Table inodes :\n");
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
      printf("nom fichier = %30s | taille fichier = %6d | first_byte = %10d\n", virtual_disk_sos->inodes[i].filename, virtual_disk_sos->inodes[i].size, virtual_disk_sos->inodes[i].first_byte);
    }

    printf("\nTables d'utilisateurs :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("uid = %2d | login = %32s| hash_password = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
    }

    printf("\nSUPPRESSION");

    delete_user("dorian");
    delete_user("enzo");
    delete_user("dorian");

    printf("\nTables d'utilisateurs :\n");
    for (int i = 0; i < NB_USERS; i++) {
      printf("uid = %2d | login = %32s| hash_password = %s\n", i, virtual_disk_sos->users_table[i].login, virtual_disk_sos->users_table[i].passwd);
    }

    printf("\nUNUSED USER ID = %d\n", get_unused_user());
  }

  if(TEST_SESSION){
    printf("\n\n---------------------------------------------------------------\n");
    printf("#OUVERTURE ET FERMETURE SESSION\n\n");

    new_session("thomas");
    printf("\nSession = %d %s\n",get_session(), virtual_disk_sos->users_table[get_session()].login);


    new_session("caelan");
    printf("\nSession = %d %s\n",get_session(), virtual_disk_sos->users_table[get_session()].login);

    del_session();
    printf("\nSession = %d\n", get_session());
  }


  if(save_disk_sos())
    return 1;


  printf("\nSAVE\n");
  return 0;
}
