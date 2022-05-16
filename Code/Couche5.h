/**
* @file Couche5.h
* @author Groupe Cosinus
* @brief Header de l'Implémentation de la couche 5
* @date Mai 2022
*
*/

#ifndef __COUCHE5_H__
#define __COUCHE5_H__

#include "header.h"
#include "Couche1.h"
#include "Couche2.h"
#include "Couche3.h"
#include "Couche4.h"
#include "Couche5.h"
#include "term_canon.h"
#include "affichage_logo.h"

/**
* @brief Enleve le \n de fin lors d'une saisie avec fgets
* @param char* chaine
* @return NULL
*/
void enlever_retour_ligne(char *chaine);


/**
* @brief Lis la valeur de la table d'utilisateurs sur le disque et l'écrit sur la variable systeme
* @param char* chaine a traiter , char carac a detecer dans la chaine
* @return int : 0 si caractere pas present ,  1 sinon
*/
int caractere_present(char* chaine , char carac);


/**
* @brief Affiche le logo du groupe + les createurs de l'os
* @param void
* @note Fonction inutile , purement esthetique
* @return NULL
*/
void credit();


/**
* @brief Affiche la liste des utilisateurs du systeme
* @param NULL
* @return void
**/
void listusers();



/**
* @brief Affiche la liste des fichiers et leurs descriptions
* @note affichage de toutes les donnes de l'inode
* @param NULL
* @return void
**/
void ls_l();



/**
* @brief Affiche le contenu d'un fichier du systeme
* @param char* filename : Nom du fichier à ecire sur stdout
* @note utilise la fonction read_file de la couche 4 pour afficher le contenu du fichier filename
* @return int : 1 si le fichier a été trouvé et affiché, 0 en cas d'erreur
**/
int cat(cmd_t *commande);


/**
* @brief vide le terminal
* @param aucun
* @note utilise un printf specifique pour effacer le terminal
* @return : void
**/
void clear();


/**
* @brief ajoute un utilisateur au systeme
* @param NULL
* @note demande un login a l'utilisateur root et si ce login n'est pas dans la table , l'user est ajouté
* @note  seul root a acces a cette commande
* @return int 1 si l'user a pu etre créé , 0 sinon
**/

int adduser(cmd_t* commande);


/**
* @brief affiche le proprietaire et les droits du fichier en parametre
* @note  fonction inutile mais pratique pour avoir un apercu
* @param char* : nom de fichier
* @return int 1 si tout se passe bien (si le fichier existe) , 0 sinon
**/
int getdroit(char* nom_fichier);


/**
* @brief cree le fichier nom_fichier , s'il depasse la taille max on renvoie une erreur
* @param char* : nom de fichier
* @note ajouter de la valeur 3 au debut pour simplifier la verification java
* @return int 1 si tout se passe bien , 0 si le fichier ne peut pas etre crée
**/
int cr(cmd_t *commande);


/**
* @brief modifie le fichier s'il existe , ou le crée et ecrit dedans s'il n'existe pas
* @note  2048 caracteres max a ecrire , saisir @ pour quitter
* @param char* : nom de fichier
* @return int 1 si tout se passe bien (si le fichier existe)
**/

int edit_file(cmd_t *commande);

/**
* @brief supprimer un user du systeme
* @note  utilisable que par root et si le login existe
* @param char* nom de login
* @return int 1 si tout se passe bien (si l'user connecte est le root et si le login existe) , 0 sinon
**/

int rmuser(cmd_t* commande);

/**
* @brief deconnecte l'user en utilisant la fonction delete session
* @note : l'user se deconnecte et met son id a -1
* @param NULL
* @return int 1 si tout se passe bien , 0 sinon
**/

int deconnexion();


/**
* @brief Affiche la liste des fichiers et leurs descriptions
* @note n'affiche que le nom du fichier et sa taille
* @param void
* @return NULL
**/

void ls(cmd_t *commande);

/**
* @brief ferme l'interprete et sauvegarde le systeme sur le disque
* @param NULL
* @return void
**/

void quit();

/**
* @brief efface un fichier du systeme si l'user connecte a les droits (root ou proprietaire du fichier)
* @note impossible d'effacer le fichier de quelqu'un d'autre
* @param char* nom_fichier
* @return int 1 si l'user a les droits et le fichier existe , 0 sinon
**/



int rm(cmd_t *commande);

/**
* @brief change les droits pour les autres utilisateurs si l'user connecte a les droits (root ou proprietaire)
* @note: impossible de changer les droits si le fichier ne nous appartient pas .
* @param char* nom du fichier cible ou les droits doivent etre changees , int droit (0 , 1 , 2 , 3)
* @return int 1 si l'user connecte a les droits et que le fichier existe , 0 sinon
**/

int chmod(cmd_t *commande);

/**
* @brief change le proprietaire d'un fichier si l'user connecte a les droits (root ou proprietaire)
* @note impossible de changer le proprietaire si l'user connecte ne l'est pas ou si l'user connecte n'est pas root
* @param char * nom du fichier , char* login du nouveau proprietaire
* @return int si l'user est le root ou le proprietaire du fichier , si le fichier existe et si le login existe , 0 sinon
**/

int chown(cmd_t* commande);

/**
* @brief Affiche la liste des commandes executables
* @note: a taper a tout moment pour obtenir la liste
* @param void
* @return void
**/

void help();

/**
* @brief charge un fichier du systeme sur l'ordinateur de l'host
* @note: le fichier aura le meme nom que le fichier du systeme et sera crée dans le repertoire Stockage_file du dossier
* @param char* nom_du_fichier a transferer
* @return int si le fichier existe et que le transfert s'est bien passé , 0 sinon
**/

int store(cmd_t* commande);

/**
* @brief charge un fichier de l'ordinateur hote sur le systeme
* @note: le fichier aura le meme nom que le fichier transfere
* @param char* nom_du_fichier a transferer
* @return int si le fichier existe et que le transfert s'est bien passé , 0 sinon
**/

int load(cmd_t* commande);

/**
* @brief demande a l'user un login et un mdp , cherche une correspondance dans le fichier passwd , 
* et si une correspondance existe , l'user se connecte
* @note: l'user aura acces a chaque commande du systeme
* @param void
* @return int : 1 si l'user a pu se connecter , 0 sinon
**/

int connexion();

/**
* @brief interprete de commande qui va executer les cpommandes saisies par l'user connecte
* @note contient un tableau de chaine de caractere commande qui contient les arguments de la commande
* @param void
* @return void
**/

/**
* @brief interprete de commande qui va executer les cpommandes saisies par l'user connecte
* @note contient un tableau de chaine de caractere commande qui contient les arguments de la commande
* @param void
* @return void
**/

void interprete_commande();


#endif
