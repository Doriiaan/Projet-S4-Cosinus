/**
* @file Couche2.h
* @author Groupe Cosinus
* @brief Header de l'Implémentation de la couche 2
* @date Avril 2022
*
*/
#ifndef __COUCHE2_H__
#define __COUCHE2_H__

#include "header.h"
#include "Couche1.h"


/**
* @brief fonction pour ecrire le superbloc sur le disque
* @param void
* @return void
* @pre variable systeme déjà initlisé
*/
void write_super_block(void);


/**
* @brief Lis la valeur du super bloc et l'écrit sur le systeme
* @param void
* @return void
* @pre variable systeme déjà initlisé
*/
void read_super_block(void);


void read_inodes_table(void);

#endif
