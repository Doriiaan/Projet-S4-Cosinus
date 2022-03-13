/******************************************
 * Quand on écrit des focntions, rajouter *
 * les définitions des fonctions dans le  *
 * fichier Couche1.h avec commentaires    *
 ******************************************/

#include "header.h"

/* Varibales globales */


/**
  Renvoit le nombre de blocs nécessaire au stockage de n octet
  input : n octets (int)
  ouput : n blocs  (int)
*/
int computenblock(int nb_octet){
    int somme = 0;
    while(nb_octet>=BLOCK_SIZE){
            nb_octet-=BLOCK_SIZE;
            somme+=1;
        }
    if(nb_octet>0){
        somme+=1;
    }
    return somme;
}

void write_block(int pos , char buffer[BLOCK_SIZE]){
	FILE* fichier = NULL;
	fichier = fopen("text.txt" , "r+");
	fseek(fichier , pos , SEEK_SET);
	fwrite( buffer, BLOCK_SIZE, 1, fichier );                       // Avant C99
}

block_t lire_block(int pos ){
	block_t t;
	FILE* fichier = NULL;
	fichier = fopen("text.txt" , "r+");
	fseek(fichier , pos , SEEK_SET);
	fread(t.data , BLOCK_SIZE , 1 , fichier);
	return t;

}


/**
  Initialise la variable globale de type virtual_disk_t
  input : nom du repertoire contenant le disque
*/
void init_disk_sos(char* nom_repertoire_disque){

}
