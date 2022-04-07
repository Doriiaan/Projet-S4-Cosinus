#ifndef __COUCHE2_H__
#define __COUCHE2_H__
#include "header.h"
#include "Couche1.h"
#include "Couche2.h"

user_t* init_user(void);
user_t* add_user(user_t user, user_t*);
user_t* delete_user(int userid, user_t*);