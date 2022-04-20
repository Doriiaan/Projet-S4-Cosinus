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
*       Les fonctions qui touchent au super bloc et à la table d'inode, actualisent
*       ces derniers sur le disque et sur la variable systeme sauf si le contraire
*       est précisé.
*/

#ifndef __COUCHE2_H__
#define __COUCHE2_H__

#include "header.h"
#include "Couche1.h"
#include "Couche3.h"



/**
* @brief Ecrit le super bloc de la variable systeme sur le disque
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable systeme déjà initialisé
*/
int write_super_block(void);


/**
* @brief Lis la valeur du super bloc sur le disque et l'écrit sur la variable systeme
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable systeme déjà initialisé
*/
int read_super_block(void);


/**
* @brief Met à jour le premier octet libre du super bloc dans la variable
* du systeme et non sur le disque
* @param uint byte : octet à mettre à jour
* @return void
* @pre variable systeme déjà initialisé
* @note Aucun test de vérification d'espace disque n'est effectué
*/
void update_first_free_byte_super_block(uint byte);


/**
* @brief Lis la valeur de la table d'inodes sur le disque et l'écrit sur la variable systeme
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable systeme déjà initialisé
*/
int read_inodes_table(void);


/**
* @brief Ecrit la table d'inodes de la variable systeme sur le disque
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable systeme déjà initialisé
* @note exit(1) -> erreur curseur : exit(2) -> erreur écriture
*/
int write_inodes_table(void);


/**
* @brief Supprime une inode de la table d'inode et met à jour le super bloc
* @param int indice_inode : indice de l'inode à supprimer
* @return int : 0 si tout s'est bien passé, 1 s'il y a eu une erreur, 2 si l'inode est déjà libre
* @pre variable systeme déjà initialisé
* @note La fonction gère si un indice qui correspond à aucun fichier est donné en paramètre
*/
int delete_inode(int indice_inode);


/**
* @brief Retourne l'indice dans la table d'inode du premier inode libre
* @param void
* @return indice du premier inode libre ou -1 si tous les inodes sont occupés
* @pre variable systeme déjà initialisé
*/
int get_unused_inode(void);


/**
* @brief Ecrit un nouvel inode à la suite des autres sur la table d'inode et sur le disque
* @param char[FILENAME_MAX_SIZE] inclut \'0' name_of_file : nom du fichier
* @param uint size  : taille du fichier
* @param uint first_byte : premier octet du fichier sur le disque
* @return int : 0 si tout s'est bien passé, 1 sinon (ex : taille max table inode attteinte)
* @pre variable systeme déjà initialisé && len(name_of_file) < FILENAME_MAX_SIZE
* @note Met à jour le la table d'inode et le super bloc sur le disque notament
*       first_free_byte, nblock et number_of_files.
*       S'il n'y a plus d'inode libre, erreur 1.
*/
int init_inode(char *name_of_file, uint size, uint first_byte);


/**
* @brief Cette fonction initialise le super bloc pour la première fois (initialisation disque ou tests)
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable systeme déjà initialisé
*/
int init_first_time_super_block(void);


/**
* @brief Cette fonction initialise la table d'inodes pour la première fois (initialisation disque ou tests)
* @param void
* @return void
* @pre variable systeme déjà initialisé
*/
int init_first_time_inodes_tables(void);

#endif
