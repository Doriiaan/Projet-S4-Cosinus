/**
* @file Couche4.h
* @author Groupe Cosinus
* @brief Header de l'Implémentation de la couche 4
* @date Avril 2022
*
*/

#ifndef __COUCHE4_H__
#define __COUCHE4_H__

#include "header.h"
#include "Couche1.h"
#include "Couche2.h"
#include "Couche3.h"


/*
* @brief Cherche un fichier dans la table d'unodes
* @param char* filename : Nom du fichier à écrire
* @return int : L'indice du fichier trouvé dans la table d'inodes, -1 par défaut
*/
int find_file(char* filename);


/*
* @brief Créé ou modifie un fichier en utilisant la table d'inodes
* @param char* filename : Nom du fichier à écrire
* @param file_t file : Fichier à écrire sur le système
* @return int : 0 en cas d'erreur, 1 sinon
*/
void write_file(char* filename, file_t file);


/*
* @brief Lit un fichier et enregistre son contenu
* @param char* filename : Nom du fichier à lire
* @param file_t file : Fichier qui enregistre les données du fichier lu
* @return int : 1 si le fichier a été lu, 0 s'il n'existe pas
*/
int read_file(char* filename, file_t file);


/*
* @brief Supprime l'inode correspondant au fichier "filename"
* @param char* filename : Nom du fichier à supprimer
* @return int : 1 si le fichier a été supprimé, 0 s'il n'existe pas, et -1 en cas d'erreur
*/
int delete_file(char* filename);


/*
* @brief Ecrit un fichier du host sur le système
* @param char* filename : Nom du fichier à transférer
* @return int : 1 si le fichier a été chargé, 0 en cas d'erreur
*/
int load_file_from_host(char* filename);


/*
* @brief Ecrit un fichier du système sur l'ordinateur host
* @param char* filename : Nom du fichier à transférer
* @return int : 1 si le fichier a été stocké, 0 en cas d'erreur
*/
int store_file_to_host(char* filename);


#endif // __COUCHE4_H__
