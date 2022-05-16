/**
* @file Couche4.h
* @author Groupe Cosinus
* @brief Header de l'Implementation de la couche 4
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
* @brief Fonction interne, non visible par l'utilisateur, ecrit un fichier sur le disque
* @param file_t file : fichier a ecrire
* @param uint first_byte : emplacement de fichier sur le disque
* @return int : 0 si tout c'est bien passe, 1 sinon
**/
int write_file_on_disk(file_t file, uint first_byte);


/**
* @brief Creer ou modifier un fichier
* @param char* filename : Nom du fichier a ecrire
* @param file_t file : Fichier a ecrire sur le systeme
* @return int : 1 si le fichier a ete ecrit, 0 en cas d'erreur
* @pre variable systeme et session initialise
* @note ne pas creer de fichier si aucune session n'est ouverte
**/
int write_file(char* filename, file_t file);


/**
* @brief Lit un fichier et enregistre son contenu
* @param char* filename : Nom du fichier a lire
* @param file_t file : Fichier qui enregistre les donnees du fichier lu
* @return int : 1 si le fichier a ete lu, 0 s'il n'existe pas
**/
int read_file(char* filename, file_t* file);


/**
* @brief Supprime l'inode correspondant au fichier "filename"
* @param char* filename : Nom du fichier a supprimer
* @return int : 1 si le fichier a ete supprime, 0 s'il n'existe pas, et -1 en cas d'erreur
**/
int delete_file(char* filename);


/**
* @brief Ecrit un fichier du host sur le systeme
* @param char* filename : Nom du fichier a transferer
* @return int : 1 si le fichier a ete charge, 0 en cas d'erreur
**/
int load_file_from_host(char* filename);


/**
* @brief Ecrit un fichier du systeme sur l'ordinateur host
* @param char* filename : Nom du fichier a transferer
* @return int : 1 si le fichier a ete stocke, 0 en cas d'erreur
**/
int store_file_to_host(char* filename);

#endif
