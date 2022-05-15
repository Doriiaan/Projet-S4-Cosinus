#ifndef __AFFICHAGE_LOGO_H__
#define __AFFICHAGE_LOGO_H__


/**
* @brief Passage du terminal en mode non canonique
* @param void
* @return void
*/
void no_canon(void);


/**
* @brief Passage du terminal en mode canonique
* @param void
* @return void
*/
void canon(void);


/**
* @brief Fin de l'affichage et retour en mode canonique pour ecrire au debut de la ligne "line"
* @param int line : ligne à laquelle il faut revenir
* @return void
*/
void end_of_display(int line);


/**
* @brief Affiche le design de l'os au dessus de l'editeur de commande
* @param bool starting : permet de mettre ou non l'animation du design
* @return void
* @note Couleur différente possible (la couleur doit être présente à l'appel)
*/
void disp_design_os(bool starting);


#endif
