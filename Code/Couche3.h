/**
* @file Couche3.h
* @author Groupe Cosinus
* @brief Header de l'Implémentation de la couche 3
* @date Avril 2022
*
*/

#ifndef __COUCHE3_H__
#define __COUCHE3_H__

#include "header.h"
#include "Couche1.h"

#define USERS_START ((SUPER_BLOCK_SIZE + INODE_TABLE_SIZE*(INODE_SIZE))*BLOCK_SIZE + 1) // en octets
#define USER_SIZE ((FILENAME_MAX_SIZE + SHA256_BLOCK_SIZE*2 + 1)/BLOCK_SIZE + 1)// login + hash + 1 pour le \0 dans le hash = 25
#define ROOT UID 0


/**
* @brief Ecrit la table d'utilisateurs de la variable systeme sur le disque
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable systeme déjà initialisé
*/
int write_users_table(void);


/**
* @brief Lis la valeur de la table d'utilisateurs sur le disque et l'écrit sur la variable systeme
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable systeme déjà initialisé
*/
int read_users_table(void);


/**
* @brief Retourne l'incide d'un utilisateur libre sur la table d'utilisateurs
* @param void
* @return int : indice d'utilisateur libre
* @pre variable systeme déjà initialisé
*/
int get_unused_user(void);


/**
* @brief Retourne l'indice de l'utilisateur rechercher dans la table d'utilisateurs
* @param char *login : login de l'utilisateur rechercher
* @return int : indice de l'utilisateur dans la table d'utilisateurs
* @pre variable systeme déjà initialisé && len(name_of_file) < FILENAME_MAX_SIZE
*/
int search_login(char *login);


/**
* @brief Ajoute un utilisateur au systeme
* @param char *login : login de l'utilisateur
* @param char *password : password non hashe de l'utilisateur
* @return int : id de l'utilisateur créer ou -1 en cas d'erreurs
* @pre variable systeme déjà initialisé && len(name_of_file) < FILENAME_MAX_SIZE
* @note Si le login est déjà existant ou qu'il n'y a plus d'utilisateurs libres
* retourne -1
*/
int add_user(char *login, char *password_clair);


/**
* @brief Supprime l'utilisateur de nom login dans la table d'utilisateur et de
* la session si nécessaire
* @param char *login: login de l'utilisateur à supprimer
* @return int : id de l'utilisateur supprimé ou -1 en cas d'erreurs
* @pre variable systeme déjà initialisé && len(name_of_file) < FILENAME_MAX_SIZE
* @note Impossible de supprimé l'utilisateur root
*/
int delete_user(char *login);


/**
* @brief Cette fonction initialise la table d'utilisateurs pour la première fois
* @param void
* @return void
* @pre variable systeme déjà initialisé
*/
void init_first_time_user_table(void);


/**
* @brief Ouvre une nouvelle session pour l'utilisateur et supprime les autres
* @param char *login : login de l'utilisateur pour lequel une session est ouverte
* @return int : 0 si tout c'est bien passé, 1 sinon
* @pre variables systeme et session déjà initialisé && len(name_of_file) < FILENAME_MAX_SIZE
*/
int new_session(char *login);


/**
* @brief Supprime la session en cours
* @param void
* @return void
* @pre variable session déjà initialisé
*/
void del_session(void);


/**
* @brief Retourne l'id d'utilisateur de la session en cours
* @param void
* @return int : id de l'utilisateur
* @pre variable session déjà initialisé
*/
int get_session(void);

#endif
