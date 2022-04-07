/**
* @file Couche2.h
* @author Groupe Cosinus
* @brief Header de liImplémentation  de la couche 2
* @date Avril 2022
* @note La table d'inode contient 10 inodes. Les inodes sont soit utilisé, ils
*       ont une position first_byte !=0, soit libre ils ont une postion first_byte == 0.
*       Les fonctions de lectures et ecrire du super bloc et de la table d'inodes
*       n'initialise rien, ils ne font que lire et ecrire sur le disque et sur
*       la variable systeme.
*/
#ifndef __COUCHE2_H__
#define __COUCHE2_H__

#include "header.h"
#include "Couche1.h"


/**
* @brief Ecrit le super bloc de la variable systeme sur le disque
* @param void
* @return void
* @pre variable systeme déjà initialisé
* @note exit(1) -> erreur curseur : exit(2) -> erreur écriture
*/
void write_super_block(void);


/**
* @brief Lis la valeur du super bloc sur le disque et l'écrit sur la variable systeme
* @param void
* @return void
* @pre variable systeme déjà initialisé
* @note exit(1) -> erreur curseur : exit(2) -> erreur lecture
*/
void read_super_block(void);


/**
* @brief Met à jour le premier octet libre du super bloc dans la variable
* du systeme et sur le disque
* @param octet à mettre à jour
* @return void
* @pre variable systeme déjà initialisé
* @note La focntion se charge du cas ou byte > first_free_byte
*/
void update_first_free_byte_super_block(uint byte);


/**
* @brief Retourne le premier octet libre du disque
* @param void
* @return premier octet libre du disque ou -1 si il n'y a pas d'octet libre
* @pre variable systeme déjà initialisé
*/
int search_free_bytes(void);


/**
* @brief Lis la valeur de la table d'inodes sur le disque et l'écrit sur la variable systeme
* @param void
* @return void
* @pre variable systeme déjà initialisé
* @note exit(1) -> erreur curseur : exit(2) -> erreur lecture
*/
void read_inodes_table(void);


/**
* @brief Ecrit la table d'inodes de la variable systeme sur le disque
* @param void
* @return void
* @pre variable systeme déjà initialisé
* @note exit(1) -> erreur curseur : exit(2) -> erreur écriture
*/
void write_inodes_table(void);


/**
* @brief Supprime une inode de la table d'inode et met à jour le super bloc
* @param int indice_inode : indice de l'inode à supprimer
* @return void
* @pre variable systeme déjà initialisé
* @note La fonction gère si un indice qui correspond à aucun fichier est donné en paramètre
*/
void delete_inode(int indice_inode);


/**
* @brief Retourne l'indice dans la table d'inode du premier inode libre
* @param void
* @return indice du premier inode libre ou -1 si tous les inodes sont occupés
* @pre variable systeme déjà initialisé
*/
int get_unused_inode(void);

#endif
