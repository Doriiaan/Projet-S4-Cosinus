/**
* @file Couche1.h
* @author Groupe Cosinus
* @brief Header de l'Implementation de la couche 1
* @date Avril 2022
*
*/

#ifndef __COUCHE1_H__
#define __COUCHE1_H__

#include "header.h"

#define SIZE_PATH_DISQUE 100

/**
*  @brief Renvoit le nombre de blocs necessaire pour stocker nb_octets
*  @param int nb_octets : Nombre d'octets
*  @return int : Nombre de blocs necessaires pour stocker nb_octets
*/
int computenblock(int nb_octets);


/**
* @brief Ecrit un bloc a la position demande sur le disque
* @param int pos : Position a laquelle ecrire le bloc
* @param block_t t : Bloc a ecrire dans le disque
* @return 0 si tout c'est bien passe, 1 sinon
*/
int write_block(int pos , block_t t);


/**
* @brief Lis un bloc a la position pos sur le systeme
* @param int pos : Position a laquelle lire un bloc dans le systeme
* @param block_t *t : Variable qui stocke le bloc lu
* @return : Bloc qui a ete lu
*/
int read_block(int pos, block_t *t);

/**
* @brief Creation et initialisation de la variable disque
* @param : char* nom_repertoire_disque : Nom du repertoire qui contient le disque
* @return 0 si tout c'est bien passe, 1 sinon
*/
int init_disk_sos(char* nom_repertoire_disque);


/**
* @brief Ferme le syteme correctement et enregistre les donnees systeme sur le disque
* @param void
* @return int : 0 si tout c'est bien passe, 1 sinon
* @pre variable systeme deja initialisee
* @note A n'utiliser qu'en cas de fermeture systeme
*/
int save_disk_sos(void);


#endif
