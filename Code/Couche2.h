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
* @brief fonction pour écrire le super bloc déjà initilisé sur le disque
* @param super_block_t *super_block : Pointeur sur le super block déjà initilisé
* @return nothing
*/
void write_super_block(super_block_t *super_block);


/**
* @brief Lis la valeur du super bloc et la rentre dans une variable déjà initilisé
* @param super_block_t *super_block : Super block déjà initialisé
* @return nothing
*/
void read_super_block(super_block_t *super_block);
#endif
