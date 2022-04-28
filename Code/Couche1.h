/**
* @file Couche1.h
* @author Groupe Cosinus
* @brief Header de l'Implémentation de la couche 1
* @date Avril 2022
*
*/

#ifndef __COUCHE1_H__
#define __COUCHE1_H__

#include "header.h"

#define SIZE_PATH_DISQUE 100


/**
*  @brief Renvoit le nombre de blocs nécessaire pour stocker nb_octets
*  @param int nb_octets : Nombre d'octets
*  @return int : Nombre de blocs nécessaire pour stocker nb_octets
*/
int computenblock(int nb_octets);


/**
* @brief Ecrit un bloc à la position demande sur le disque
* @param int pos : Position à laquelle écrire le bloc
* @param block_t t : Bloc à écrire dans le disque
* @return 0 si tout c'est bien passé, 1 sinon
*/
int write_block(int pos , block_t t);


/**
* @brief Lis un bloc à la position pos sur le systeme
* @param int pos : Position à laquelle lire un bloc dans le systeme
* @param block_t *t : Variable qui stocke le bloc lu
* @return : Bloc qui à été lu
*/
int read_block(int pos, block_t *t);


/**
* @brief Création et initialisation de la variable disque
* @param : char* nom_repertoire_disque : Nom du répertoire qui contient le disque
* @return nothing
*/
void init_disk_sos(char* nom_repertoire_disque);


#endif
