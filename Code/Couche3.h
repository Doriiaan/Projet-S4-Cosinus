/**
* @file Couche3.h
* @author Groupe Cosinus
* @brief Header de l'Implémentation de la couche 3
* @date Avril 2022
* @note La table d'utilisateur est un fichier systeme nommé "passwd", au tout début
* le fichier ne contient que l'utilisateur root, le format et le suivant :
* <login1>:<hash1>\n
* ...
* <loginN>:<hashN>\n\3
*/

#ifndef __COUCHE3_H__
#define __COUCHE3_H__

#include "header.h"
#include "Couche1.h"
#include "Couche4.h"


/**
* @brief Ecrit la table d'utilisateurs de la variable système sur le disque
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable système déjà initialisée
*/
int write_users_table(void);


/**
* @brief Lis la valeur de la table d'utilisateurs sur le disque et l'écrit sur la variable système
* @param void
* @return int : 0 si tout s'est bien passé, 1 sinon
* @pre variable système déjà initialisée
*/
int read_users_table(void);


/**
* @brief Retourne l'incide d'un utilisateur libre sur la table d'utilisateurs
* @param void
* @return int : indice d'utilisateur libre
* @pre variable système déjà initialisée
*/
int get_unused_user(void);


/**
* @brief Retourne l'indice de l'utilisateur recherché dans la table d'utilisateurs
* @param char *login : login de l'utilisateur recherché
* @return int : indice de l'utilisateur dans la table d'utilisateurs
* @pre variable système déjà initialisée && len(name_of_file) < FILENAME_MAX_SIZE
*/
int search_login(char *login);


/**
* @brief Retourne le login de l'utilisateur recherché dans la table d'utilisateurs
* @param int id : id de l'utilisateur recherché
* @return char* : login de l'utilisateur dans la table d'utilisateurs
* @pre variable système déjà initialisée && 0 <= id && id < NB_USERS
*/
char* search_id(int id);


/**
* @brief Ajoute un utilisateur au système
* @param char *login : login de l'utilisateur
* @param char *password : password non hashé de l'utilisateur
* @return int : id de l'utilisateur créer ou -1 en cas d'erreurs
* @pre variable système déjà initialisée && len(name_of_file) < FILENAME_MAX_SIZE
* @note Si le login est déjà existant ou qu'il n'y a plus d'utilisateurs libres
* retourne -1
*/
int add_user(char *login, char *password_clair);


/**
* @brief Supprime l'utilisateur de nom login dans la table d'utilisateur et de
* la session si nécessaire
* @param char *login: login de l'utilisateur à supprimer
* @return int : id de l'utilisateur supprimer ou -1 en cas d'erreurs
* @pre variable système déjà initialisée && len(name_of_file) < FILENAME_MAX_SIZE
* @note Impossible de supprimer l'utilisateur root
*/
int delete_user(char *login);


/**
* @brief Cette fonction initialise la table d'utilisateurs pour la première fois
* @param void
* @return 0 si tout c'est bien passé, 1 sinon
* @pre variable système déjà initialisée
*/
int init_first_time_user_table(void);


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
* @return int : id de l'utilisateur ou -1
* @pre variable session déjà initialisé
*/
int get_session(void);

#endif
