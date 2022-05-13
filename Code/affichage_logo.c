#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "term_canon.h"

#define EXIT_ERROR_N_CAN 1
#define EXIT_ERROR_CAN 2

/* passage en forme non canonique */
void no_canon(){
    if (!Term_non_canonique())
        exit (EXIT_ERROR_N_CAN);
    printf("\033[?25l\n");//masquage curseur
}

/* passage en forme canonique */
void canon(){
    if (!Term_canonique())
        exit (EXIT_ERROR_CAN);
    printf("\033[?25h");//affichage curseur
}

/* fin de l'affichage et retour en mode canonique pour ecrire au debut
de la ligne "line"
 */
void end_of_display(int line){
    printf("\033[%d;%dH", line, 1);
    fflush (stdout);
    canon();
}

/* affiche le design de l'os au dessus de l'editeur de commande
le booleen "starting" permet de mettre ou non l'animation du design
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
