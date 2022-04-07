#include "Couche3.h"


user_t* init_user(){
    user_t* table_user = malloc(sizeof(user_t)*NB_USERS);
    user_t root {"Root","password"}
    table_user[ROOT_UID] = root;
    return table_user;
}


user_t* add_user(user_t user, user_t* table_user){
    i = 0;
    while (table_user[i] != NULL){
        if (i == NB_USERS){
            printf("Nombre d'utilisateur Maximum déjà atteint , veuillez vous connecter avec un utilisateur déjà existant ou le supprimer\n\n");
            exit(1);
        }
        i++;
    }
    table_user[i] = user;
    return table_user;
}

user_t* delete_user(int userid, user_t* table_user){
    if (userid == ROOT_UID){
        printf("IMPOSSIBLE DE SUPPRIMER LE ROOT !");
        exit(1);
    }
    else if (userid >= NB_USERS){
        printf("Il n'y a pas d'utilisateur avec cet ID , veuillez réesayer");
        exit(1);
    }
    else {
        if (table_user[userid] == NULL){
            printf("Il n'y a pas d'utilisateur avec cet ID , veuillez réesayer");
            exit(1);
        }
        else{
            table_user[userid] = NULL;
            printf("Utilisateur Supprimé !");

        }
    }
    return table_user;
}