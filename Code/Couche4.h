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


/**
* @brief Fonction interne, non visible par l'utilisateur, écrit un fichier sur le disque
* @param file_t file : fichier à écrire
* @param uint first_byte : emplacement de fichier sur le disque
* @return int : 0 si tout c'est bien passé, 1 sinon
**/
int write_file_on_disk(file_t file, uint first_byte);


/**
* @brief Créer ou modifier un fichier
* @param char* filename : Nom du fichier à écrire
* @param file_t file : Fichier à écrire sur le système
* @return int : 1 si le fichier a été écrit, 0 en cas d'erreur
* @pre variable système et session initialisé
* @note ne pas créer de fichier si aucune session n'est ouverte
**/
int write_file(char* filename, file_t file);


/**
* @brief Lit un fichier et enregistre son contenu
* @param char* filename : Nom du fichier à lire
* @param file_t file : Fichier qui enregistre les données du fichier lu
* @return int : 1 si le fichier a été lu, 0 s'il n'existe pas
**/
int read_file(char* filename, file_t* file);


/**
* @brief Supprime l'inode correspondant au fichier "filename"
* @param char* filename : Nom du fichier à supprimer
* @return int : 1 si le fichier a été supprimé, 0 s'il n'existe pas, et -1 en cas d'erreur
**/
int delete_file(char* filename);


/**
* @brief Ecrit un fichier du host sur le système
* @param char* filename : Nom du fichier à transférer
* @return int : 1 si le fichier a été chargé, 0 en cas d'erreur
**/
int load_file_from_host(char* filename);


/**
* @brief Ecrit un fichier du système sur l'ordinateur host
* @param char* filename : Nom du fichier à transférer
* @return int : 1 si le fichier a été stocké, 0 en cas d'erreur
**/
int store_file_to_host(char* filename);

#endif
