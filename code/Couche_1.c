#define _POSIX_C_SOURCE_1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
/* constantes symboliques pour les droits d’accès */
#include <fcntl.h> /* constantes symboliques pour les différents types d’ouverture */
#include<header.h>


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


int main(void){
    int a ;
    a = computenblock(40);

}
