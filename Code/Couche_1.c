/**
* @file Couche1.c
* @author Groupe Cosinus
* @brief Implémentation de la couche 1
* @date Avril 2022
*
*/

#include "Couche1.h"
#include "Couche2.h"

virtual_disk_t *virtual_disk_sos;


/**
*  @brief Renvoit le nombre de blocs nécessaire pour stocker nb_octets
*  @param int nb_octets : Nombre d'octets
*  @return int : Nombre de blocs nécessaire pour stocker nb_octets
*/
int computenblock(int nb_octets){

  int nb_blocs = (nb_octets / BLOCK_SIZE);
  if(nb_octets%BLOCK_SIZE) nb_blocs++;
  return nb_blocs;
}


/**
* @brief Ecrit un bloc à la position demande sur le disque
* @param int pos : Position à laquelle écrire le bloc
* @param block_t t : Bloc à ecrire dans le disque
* @return nothing
*/
void write_block(int pos , block_t t){

  // on se place au debut avec un decalage de pos
	fseek(virtual_disk_sos->storage , pos , SEEK_SET);	// on se place au debut avec un decalage de pos
	fwrite( t.data, BLOCK_SIZE, 1, virtual_disk_sos->storage );
}


/**
* @brief Lis un bloc à la position pos sur le systeme
* @param int pos : Position à laquelle lire un bloc dans le systeme
* @return : Bloc qui à été lu
*/
block_t read_block(int pos ){

	block_t t;
  // on se place au debut avec un decalage de pos
	fseek(virtual_disk_sos->storage , pos , SEEK_SET);
	fread(t.data , BLOCK_SIZE , 1 , virtual_disk_sos->storage);
	return t;
}


/**
* @brief Création et initialisation de la variable disque
* @param : char* nom_repertoire_disque : Nom du répertoire qui contient le disque
* @return nothing
*/
void init_disk_sos(char* nom_repertoire_disque){

  virtual_disk_sos = malloc(sizeof(virtual_disk_t));

  //creation chemin disque
  char path_disque[SIZE_PATH_DISQUE];
  strcpy(path_disque, nom_repertoire_disque);
  strcat(path_disque, "/d0");

  FILE *disque;
  if(!(disque = fopen(path_disque, "r+"))){
    printf("Erreur ouverture disque\n");
    exit(1);
  }
  virtual_disk_sos->storage = disque;
  read_inodes_table();
}
