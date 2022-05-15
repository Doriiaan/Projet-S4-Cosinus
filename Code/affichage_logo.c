#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "term_canon.h"
#include "affichage_logo.h"

#define EXIT_ERROR_N_CAN 1
#define EXIT_ERROR_CAN 2

/**
* @brief Passage du terminal en mode non canonique
* @param void
* @return void
*/
void no_canon(void){
    if (!Term_non_canonique())
        exit (EXIT_ERROR_N_CAN);
    printf("\033[?25l\n");//masquage curseur
}


/**
* @brief Passage du terminal en mode canonique
* @param void
* @return void
*/
void canon(void){
    if (!Term_canonique())
        exit (EXIT_ERROR_CAN);
    printf("\033[?25h");//affichage curseur
}



/**
* @brief Fin de l'affichage et retour en mode canonique pour ecrire au debut de la ligne "line"
* @param int line : ligne à laquelle il faut revenir
* @return void
*/
void end_of_display(int line){
    printf("\033[%d;%dH", line, 1);
    fflush (stdout);
    canon();
}

/**
* @brief Affiche le design de l'os au dessus de l'editeur de commande
* @param bool starting : permet de mettre ou non l'animation du design
* @return void
* @note Couleur différente possible (la couleur doit être présente à l'appel)
*/
void disp_design_os(bool starting){
    char matr[5][53] = {
        {"                          _                         "},
        {"  _____  ____    _____   (_)   ____   __  __   _____"},
        {" / ___/ / __ \\  / ___/  / /   / __ \\ / / / /  / ___/"},
        {"/ /__  / /_/ / (__  )  / /   / / / // /_/ /  (__  ) "},
        {"\\___/  \\____/ /____/  /_/   /_/ /_/ \\____/  /____/  "},
    };
    int len_line = 5, len_col = 53;
    if (matr == NULL){
        printf("erreur: affichage impossible\n");
        return;
    }
    no_canon();
    printf("\033[H\033[J\n");
    for (int j=0;j<len_col;j++){
        for (int i=0;i<len_line;i++){
            printf ("\033[%d;%dH%c", i+1, j+2, matr[i][j]);
            fflush (stdout);
            if (starting)
                usleep(8000);
        }
    }
    end_of_display(len_line+2);
}
