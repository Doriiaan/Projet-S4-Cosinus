/**
* @file Couche2.h
* @author Groupe Cosinus
* @brief Header de liImplementation  de la couche 2
* @date Avril 2022
* @note La table d'inode contient 10 inodes. Les inodes sont soit utilise, ils
*       ont une position first_byte !=0, soit libre ils ont une postion first_byte == 0.
*       Les fonctions de lectures et ecrire du super bloc et de la table d'inodes
*       n'initialise rien, ils ne font que lire et ecrire sur le disque et sur
*       la variable systeme.
*       Les fonctions qui touchent au super bloc et a la table d'inode, actualisent
*       ces derniers sur le disque et sur la variable systeme sauf si le contraire
*       est precise.
*/

#ifndef __COUCHE2_H__
#define __COUCHE2_H__

#include "header.h"
#include "Couche1.h"
#include "Couche3.h"


/**
* @brief Ecrit le super bloc de la variable systemesur le disque
* @param void
* @return int : 0 si tout s'est bien passe, 1 sinon
* @pre variable systeme deja initialisee
*/
int write_super_block(void);


/**
* @brief Lis la valeur du super bloc sur le disque et l'ecrit sur la variable systeme
* @param void
* @return int : 0 si tout s'est bien passe, 1 sinon
* @pre variable systeme deja initialisee
*/
int read_super_block(void);


/**
* @brief Met a jour le premier octet libre du super bloc dans la variable
* du systeme et non sur le disque
* @param uint byte : octet a mettre a jour
* @return void
* @pre variable systeme deja initialisee
* @note Aucun test de verification d'espace disque n'est effectue, ajoute le first_free_byte
* au debut d'un nouveau bloc
*/
void update_first_free_byte_super_block(uint byte);


/**
* @brief Lis la valeur de la table d'inodes sur le disque et l'ecrit sur la variable systeme
* @param void
* @return int : 0 si tout s'est bien passe, 1 sinon
* @pre variable systeme deja initialisee
*/
int read_inodes_table(void);


/**
* @brief Ecrit la table d'inodes de la variable systeme sur le disque
* @param void
* @return int : 0 si tout s'est bien passe, 1 sinon
* @pre variable systeme deja initialisee
*/
int write_inodes_table(void);


/**
* @brief Supprime une inode de la table d'inode et met a jour le super bloc
* @param int indice_inode : indice de l'inode a supprimer
* @return int : 0 si tout s'est bien passe, 1 s'il y a eu une erreur, 2 si l'inode est deja libre
* @pre variable systeme deja initialisee && len(name_of_file) < FILENAME_MAX_SIZE
* @note La fonction gere si un indice qui correspond a aucun fichier est donne en parametre
*/
int delete_inode(char *name_of_file);


/**
* @brief Retourne l'indice dans la table d'inode du premier inode libre
* @param void
* @return indice du premier inode libre ou -1 si tous les inodes sont occupes
* @pre variable systeme deja initialisee
*/
int get_unused_inode(void);


/**
* @brief Ecrit un nouvel inode a la suite des autres sur la table d'inode
* @param name_of_file : nom du fichier
* @param uint size : taille du fichier
* @param uint first_byte : premier octet du fichier sur le disque
* @return int : indice du nouvel inode, -1 si erreurs (ex : taille max table inode atteinte)
* @pre variable systeme deja initialisee && len(name_of_file) < FILENAME_MAX_SIZE
* @note Met a jour le super bloc first_free_byte, nblock et number_of_files.
*/
int init_inode(char *name_of_file, uint size, uint first_byte);


/**
* @brief Retourne l'indice de l'inode qui pointe vers un fichier de nom name_of_file
* @param char name_of_file[MAX_FILE_SIZE] : nom du fichier a chercher
* @return int : indice de l'inode ou -1 s'il n'existe pas
* @pre variable systeme deja initialisee && len(name_of_file) <= FILENAME_MAX_SIZE
*/
int search_file_inode(char *name_of_file);


/**
* @brief Cette fonction initialise le super bloc pour la premiere fois
* @param void
* @return 0 si tout c'est bien passe, 1 sinon
* @pre variable systeme deja initialisee
*/
int init_first_time_super_block(void);


/**
* @brief Cette fonction initialise la table d'inodes pour la premiere fois
* @param void
* @return 0 si tout c'est bien passe, 1 sinon
* @pre variable systeme deja initialisee
*/
int init_first_time_inodes_tables(void);

#endif
