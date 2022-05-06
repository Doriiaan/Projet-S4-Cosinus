#include <sys/stat.h>
#include <sys/termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Couche1.h"
#include "Couche2.h"
#include "Couche3.h"
#include "Couche4.h"



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

void supp_echo(){
    struct termios term;
    tcgetattr(fileno(stdin),&term);
    term.c_lflag &= ~ECHO;
    tcsetattr(fileno(stdin),TCSANOW,&term);
}
void retablir_echo(){
    struct termios term;
    tcgetattr(fileno(stdin),&term);
    term.c_lflag |= ECHO;
    tcsetattr(fileno(stdin),TCSANOW,&term);
}


int main(void){
    char chemin[200];
    char actu [200];
    char password[200];
    char passwordconfirm[200];
    char* ret;
    struct stat rep_stat;
    int repertoire = 0;
    int retour;
    ret = getcwd(actu,200);
    (void)ret;
    while(actu[1] != '\0' ){
        ret = getcwd(actu,200);
        retour = chdir("..");

    }
    printf("Bienvenue dans l'installation de cOSinus, veuillez spécifiez un chemin d'installation pour votre disque : ( ou 1 pour annuler ) \n");
    do {
    retour = scanf("%s",chemin);
    if (chemin[0] == '1' && chemin[1] == '\0'){
        exit(0);
    }
    if (stat(chemin,&rep_stat) == 0 ){
        if (S_ISDIR(rep_stat.st_mode) != 0 ){
            printf("Chemin d'accès correct...\n\nCréation du disque...\n");
            if(formatage(chemin,300000,0) == 0){
                printf("Disque Créé ! \n\n");
                repertoire = 1;
            }
            else {
                printf("Erreur lors de la création du disque ... \n Veuillez rentrez  à nouveau le chemin d'installation pour réessayer\n");
            }
        }
        else{
            printf("Le chemin d'accès rentré ne mène pas à un dossier ... \n Veuillez rentrez à nouveau le chemin d'installation pour réesayer \n");
        }
    }
    else {
        printf("Chemin d'accès invalide ... \n Veuillez rentrez à nouveau le chemin d'installation pour réesayer \n");
        }
    } while (repertoire == 0);

    printf("Initialisation du Disque ... \n");
    if (init_disk_sos(chemin) == 0 ){
        printf("Initialisation du Disque Réussie ! \n\n");
    }
    else {
        printf("Erreur lors de l'initialisation du Disque ... \nSuppression du disque et fermeture du programme ! ");
        strcat(chemin,"/d0");
        remove(chemin);
        exit(1);
    }
    printf("Création du super block...\n");
    init_first_time_super_block();
    if (write_super_block() == 0){
        printf("Création du super block Réussie ! \n\n");
    }
    else{
        printf("Erreur lors de la création du super block ...\nSupression du disque et fermeture du programme !");
        strcat(chemin,"/d0");
        remove(chemin);
        exit(1);
    }
    do {
    printf("Veuillez rentrez le mot de passe pour l'utilisateur root :  ");
    supp_echo();
    retour = scanf("%s",password);
    printf("\n");
    printf("Veuillez confirmez le mot de passe : ");
    retour = scanf("%s",passwordconfirm);
    printf("\n");
    retablir_echo();
    if(strcmp(password,passwordconfirm) != 0){
        printf("Les mots de passes ne correspondent pas ! \n\n");
    }
    }while (strcmp(password,passwordconfirm) != 0);
    init_first_time_user_table();
    if (add_user("root",password) == 0){
        printf("Utilisateur root ajouté avec succès !\n");
    }
    else {
        printf("Erreur lors de la création de l'utilisateur root !\n Supression du disque et fermeture du programme !\n");
        strcat(chemin,"/d0");
        remove(chemin);
        exit(1);
    }
    printf("Initialisation de la table d'inode... \n");
    init_first_time_inodes_tables();
    if (write_inodes_table() == 0) {
        printf("Table d'inodes Initialisé avec succès ! \n");
    }
    else {
        printf("Erreur lors de l'initialisation de la table d'inodes ! !\n Supression du disque et fermeture du programme !\n");
        strcat(chemin,"/d0");
        remove(chemin);
        exit(1);
    }

    /* reste à write le fichier passwd*/






    retour = save_disk_sos();
    (void)retour;
    return 1;
}
