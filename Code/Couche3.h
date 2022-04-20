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

#define USERS_START ((SUPER_BLOCK_SIZE + INODE_TABLE_SIZE*(INODE_SIZE))*BLOCK_SIZE + 1) // en octets
#define USER_SIZE ((FILENAME_MAX_SIZE + SHA256_BLOCK_SIZE*2)/BLOCK_SIZE + 1) // login + hash (\'0' + 3 octet libre pour finir le bloc)
#define ROOT UID 0


int write_users_table(void);

int read_users_table(void);

int add_user(char login[FILENAME_MAX_SIZE], char password[SHA256_BLOCK_SIZE*2 + 1]);

int del_user(int userid);

int init_user_table(void);


#endif
