#define _POSIX_C_SOURCE 1

//include bibliothèques standards
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//include bibliothèques systèmes
#include <sys/stat.h>
#include <sys/termios.h>
#include <unistd.h>

//include bibliothèques locales
#include "Couche1.h"
#include "Couche2.h"
#include "Couche3.h"
#include "Couche4.h"
#include "affichage_logo.h"

#define SIZE_CHEMIN 300
#define MAX_SIZE_PASSWORD 100


void enlever_retour_ligne(char *chaine){

    int taille = strlen(chaine);
    if(chaine[taille-1] == '\n')
    chaine[taille-1] = '\0';
}

// create a file named di (i = diskid) in directory dirname of size bytes
// the file is initialized with 0
// dirname must be a valid directory
// 0 <= diskid < 10
int formatage(char *dirname, int size, int diskid){
  char filename[strlen(dirname)+4];
  snprintf(filename, strlen(dirname)+4, "%s/d%d", dirname, diskid);
  printf("%s\n", filename);
  FILE *fp = fopen(filename, "w+");
  assert(fp!=NULL);
  unsigned char zero=0;
  for(int i=0; i<size; i++) {
    int nb_write = fwrite(&zero, 1, 1, fp);
    assert(nb_write == 1);
    (void)nb_write;

  }
  fclose(fp);
  return 0;
}

void affichage(int nb_chargement){

  char chargement[30] = "";

  for (int i = 0; i < nb_chargement; i++) {
    strcat(chargement, "#");
  }
  for (int i = 0; i < 30-nb_chargement; i++) {
    strcat(chargement, ".");
  }
  /* Affichage */

  printf ("\033[H\033[J"); //effacer
  printf("\033[0;32m"); //couleur
  disp_design_os(false);
  printf("\033[50D"); //remettre au début ligne
  printf("\033[20B"); //decaler de 25 vers le bas
  printf("[%s]", chargement); //chargement
  printf("\033[50D"); //remettre au début ligne
  printf ("\033[12A"); //10 vers le haut
  printf("\033[0m"); //couleur
  /* Fin affichage */
}


int main(void){

  char chemin[SIZE_CHEMIN];
  struct stat element_chemin;
  bool install = false;

  char password_root[MAX_SIZE_PASSWORD];
  char password_root_confirm[MAX_SIZE_PASSWORD];

  /* Page d'arrivé */

  printf ("\033[H\033[J");
  printf("\033[0;32m");
  disp_design_os(true);
  printf("\033[0m");

  affichage(0);
  printf("-[0] Bienvenue dans l'installation du disque\n\n     Tapez entrée pour continuer ");

  fgetc(stdin);


  /* Installation du disque */
  do {

    affichage(0);

    printf("-[1] Rentrez le chemin d'installation pour votre disque :   ");
    fflush(stdin);
    fgets(chemin, SIZE_CHEMIN,stdin);
    enlever_retour_ligne(chemin);
    if(strcmp(chemin, "1") == 0)
      return 0;

    if(stat(chemin,&element_chemin) == 0){
      if(S_ISDIR(element_chemin.st_mode) != 0){

        affichage(5);
        printf(" (*) Chemin d'accès correct \n");
        sleep(3);
        affichage(10);
        printf(" (*) Creation disque : ");
        if(formatage(chemin, 300000, 0) == 0){
          sleep(3);
          affichage(15);
          printf(" (*) Disque Créé ! \n");
          sleep(3);
          install = true;

        }
        else{
          affichage(0);
          printf("\033[0;31m"); //couleur
          printf(" (*) Erreur lors de la création du disque ...\n");
          printf("\033[0m"); //couleur
          sleep(3);
        } //formatage à planté

      }
      else{
        affichage(0);
        printf("\033[0;31m"); //couleur
        printf(" (*) Le chemin d'accès rentré ne mène pas à un dossier ...\n");
        printf("\033[0"); //couleur
        sleep(3);
      } //le chemin n'est pas un dossier

    }
    else{
      affichage(0);
      printf("\033[0;31m"); //couleur
      printf(" (*) Chemin d'accès invalide ...\n");
      printf("\033[0m"); //couleur
      sleep(3);
    } //le chemin est invalide

  } while(!install);


  /* Initialisation du disque */
  if(init_disk_sos(chemin))
    return 1;


  if(init_first_time_super_block()){
    printf("Initialisation échouée");
    return 1;
  }

  if(init_first_time_inodes_tables()){
    printf("Initialisation échouée");
    return 1;
  }
  if(init_first_time_user_table()){
    printf("Initialisation échouée");
    return 1;
  }

  do {

  affichage(15);

  printf("-[2] Veuillez rentrez le mot de passe pour l'utilisateur root : ");
  fflush(stdin);
  fgets(password_root, MAX_SIZE_PASSWORD, stdin);
  enlever_retour_ligne(password_root);
  printf("\n");

  printf("     Veuillez confirmez le mot de passe : ");
  fflush(stdin);
  fgets(password_root_confirm, MAX_SIZE_PASSWORD, stdin);
  enlever_retour_ligne(password_root_confirm);
  printf("\n");

  if(strcmp(password_root, password_root_confirm) != 0){
    affichage(15);
    printf("\033[0;31m"); //couleur
    printf(" (*) Les mots de passes ne correspondent pas !\n");
    printf("\033[0m"); //couleur
    sleep(3);
  }

  }while (strcmp(password_root, password_root_confirm) != 0);

  if(add_user("root", password_root)){
    printf("Erreur lors de la création de l'utilisateur root !\n");
    return 1;
  }

  /* Sauvegarde du disque */
  if(save_disk_sos())
    return 1;

  affichage(25);
  printf("-[3] Création utilisateur root terminé avec succès\n");
  sleep(3);
  affichage(30);
  printf("-[4] Initialisation réussie\n");
  sleep(3);
  printf ("\033[H\033[J"); //effacer
  return 0;
}
