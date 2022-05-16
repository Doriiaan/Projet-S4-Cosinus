/**
* @file Couche5.h
* @author Groupe Cosinus
* @brief Header de l'Implementation de la couche 5
* @date Mai 2022
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
* @brief retire le caractere \n lors d'une saisie de login avec fgets
* @param char*  chaine de caractere
* @return void
**/
void enlever_retour_ligne(char *chaine);


/**
* @brief Cherche dans une chaine de caractere si un caractere est present
* @param char* chaine : chaine a traiter
* @param char carac : caractere a detecer dans la chaine
* @return int : 0 si caractere pas present,  1 sinon
*/
int caractere_present(char* chaine , char carac);


/**
* @brief Fonction bonus, credite les programmeurs
* @param void
* @return void
*/
void credit(void);


/**
* @brief Affiche la liste des utilisateurs du systeme
* @param void
* @return void
**/
void listusers(void);


/**
* @brief Affiche la liste des fichiers et leurs descriptions
* @param void
* @return void
* @note affichage de toutes les donnees de l'inode
**/
void ls_l(void);


/**
* @brief Affiche le contenu d'un fichier du systeme
* @param cmd_t* commande : commande[1] nom du fichier
* @return int : 1 si le fichier a été trouvé et affiché, 0 en cas d'erreur
* @note utilise la fonction read_file de la couche 4 pour afficher le contenu du fichier filename
**/
int cat(cmd_t *commande);


/**
* @brief vide le terminal
* @param void
* @return void
* @note utilise un printf specifique pour effacer le terminal
**/
void clear(void);


/**
* @brief ajoute un utilisateur au systeme
* @param cmd_t* commande : commande[1] est le login de l'utilisateur
* @return int : 1 si tout c'est bien passe, 0 sinon
* @note Si le login n'est pas dans la table, l'utilisateur est ajouté
*       Seul root a acces a cette commande
**/
int adduser(cmd_t* commande);


/**
* @brief Affiche le proprietaire et les droits du fichier en parametre
* @param char* : nom de fichier
* @return int 1 si tout se passe bien (si le fichier existe)
* @note Fonction inutile mais pratique pour avoir un apercu
**/
int getdroit(char* nom_fichier);


/**
* @brief Cree le fichier nom_fichier, s'il depasse la taille max on renvoie une erreur
* @param cmd_t *commande : commande[1] nom de fichier
* @return int : 1 si tout se passe bien, 0 si le fichier ne peut pas etre crée
**/
int cr(cmd_t *commande);


/**
* @brief Modifie le fichier s'il existe , ou le crée et ecrit dedans il existe pas
* @param cmd_t *commande : commande[1] nom de fichier
* @return int 1 si tout se passe bien (si le fichier existe)
* @note 2048 caracteres max a ecrire, saisir @ pour quitter
**/
int edit_file(cmd_t *commande);


/**
* @brief Supprimer un user du systeme
* @param cmd_t* commande : commande[1] nom de login
* @return int : 1 si tout se passe bien (si l'user connecte est le root et si le login existe), 0 sinon
* @note  utilisable que par root et si le login existe
**/
int rmuser(cmd_t* commande);


/**
* @brief deconnecte l'user
* @param void
* @return int 1 si tout se passe bien
* @note : l'user se deconnecte et met son id a -1
**/
int deconnexion(void);


/**
* @brief Affiche la liste des fichiers et leurs descriptions
* @param cmd_t *commande : commande[1] [-l]
* @return void
* @note N'affiche que le nom du fichier et sa taille
**/
void ls(cmd_t *commande);


/**
* @brief Ferme l'interprete et sauvegarde le systeme sur le disque
* @param void
* @return void
**/
void quit();


/**
* @brief Efface un fichier du systeme si l'user connecte a les droits (root ou proprietaire du fichier)
* @param cmd_t *commande : commande[1] nom_fichier
* @return int 1 si l'user a les droits et le fichier existe, 0 sinon
* @note impossible d'effacer le fichier de quelqu'un d'autre
**/
int rm(cmd_t *commande);


/**
* @brief Change les droits pour les autres utilisateurs si l'user connecte a les droits (root ou proprietaire)
* @param cmd_t *commande : commande[1] nom du fichier, commande[2] droit (0 , 1 , 2 , 3)
* @return int 1 si l'user connecte a les droits et que le fichier existe, 0 sinon
* @note: impossible de changer les droits si le fichier ne nous appartient pas.
**/
int chmod(cmd_t *commande);


/**
* @brief Change le proprietaire d'un fichier si l'user connecte a les droits (root ou proprietaire)
* @param cmd_t* commande : commande[1] nom du fichier, commande[2] login du nouveau proprietaire
* @return int : 1 si l'user est le root ou le proprietaire du fichier, si le fichier existe et si le login existe, 0 sinon
* @note impossible de changer le proprietaire si l'user connecte ne l'est pas ou si l'user connecte n'est pas root
**/
int chown(cmd_t* commande);


/**
* @brief Affiche la liste des commandes executables
* @param void
* @return void
* @note: a taper a tout moment pour obtenir la liste
**/
void help(void);


/**
* @brief Charge un fichier du systeme sur l'ordinateur de l'host_file
* @param cmd_t* commande : commande[0] nom_du_fichier a transferer
* @return int : 1 si le fichier existe et que le transfert s'est bien passé, 0 sinon
* @note: le fichier aura le meme nom que le fichier du systeme
**/
int store(cmd_t* commande);


/**
* @brief Charge un fichier de l'ordinateur hote sur le systeme
* @param cmd_t* commande : commande[1] nom_du_fichier a transferer
* @return int : 1 si le fichier existe et que le transfert s'est bien passé, 0 sinon
* @note: le fichier aura le meme nom que le fichier transfere
**/
int load(cmd_t* commande);


/**
* @brief Demande a l'user un login et un mdp , cherche une correspondance dans le fichier passwd , et si une correspondance existe , l'user se connecte
* @param void
* @return int : 1 si l'user a pu se connecter , 0 sinon
* @note: l'user aura acces a chaque commande du systeme
**/
int connexion(void);


/**
* @brief interprete de commande qui va executer les commandes saisies par l'user connecte
* @param void
* @return void
* @note contient un tableau de chaine de caractere commande qui contient les arguments de la commande
**/
void interprete_commande(void);

#endif
