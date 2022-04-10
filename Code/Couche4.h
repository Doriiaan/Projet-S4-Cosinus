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
* @brief Créé ou modifie un fichier en utilisant
* la table d'inodes
* @param String filename : Nom du fichier à écrire
* @param file_t file : Fichier à écrire sur le système
* @return void
*/
void write_file(String filename, file_t file);


/*
* @brief Lit un fichier et enregistre son contenu
* @param String filename : Nom du fichier à lire
* @param file_t file : Fichier qui enregistre les données du fichier lu
* @return int : 1 si le fichier a été lu, 0 s'il n'existe pas
*/
int read_file(String filename, file_t file);


/*
* @brief Supprime l'inode correspondant au fichier "filename"
* @param String filename : Nom du fichier à supprimer
* @return int : 1 si le fichier a été supprimé, 0 s'il n'existe pas
*/
int delete_file(String filename);


/*
* @brief Ecrit un fichier du host sur le système
* @param String filename : Nom du fichier à transférer
* @return void
*/
void load_file_from_host(String filename);


/*
* @brief Ecrit un fichier du système sur l'ordinateur host
* @param String filename : Nom du fichier à transférer
* @return void
*/
void store_file_to_host(String filename);

#endif // __COUCHE4_H__