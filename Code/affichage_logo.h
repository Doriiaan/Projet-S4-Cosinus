#include <stdbool.h>

void no_canon();

/* passage en forme canonique */
void canon();

/* fin de l'affichage et retour en mode canonique pour ecrire au debut
de la ligne "line"
 */
void end_of_display(int line);
/* affiche le design de l'os au dessus de l'editeur de commande
le booleen "starting" permet de mettre ou non l'animation du design
*/
void disp_design_os(bool starting);
