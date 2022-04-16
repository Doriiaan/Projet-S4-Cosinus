/**
* @file Couche3.h
* @author Groupe Cosinus
* @brief Header de l'Implémentation de la couche 3
* @date Avril 2022
*
*/

#ifndef __COUCHE3_H__
#define __COUCHE3_H__

#include "header.h"
#include "Couche1.h"

#define ROOT UID 0


int write_users_table(void);

int read_users_table(void);

int add_user(char[FILENAME_MAX_SIZE] login, char *password);

int del_user(int userid);

int init_user_table(void);

//réfléchir à celle là, voir si faut pas la faire couche 5
//char[SHA256_BLOCK_SIZE*2 + 1] hash_password(char *password);


#endif
