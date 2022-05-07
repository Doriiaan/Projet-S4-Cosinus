/* Term canon VT100 ===================================	*/
/* deux fonctions pour passer du mode de communication	  */
/* canonique au mode non-canonique avec le terminal :	  */
/*  mode canonique : communication du terminal en mode	  */
/*    interactif, c-à-d : écho, les touches frappées   */
/*    au clavier sont affichées sur le terminal ; et	  */
/*    entrée par ligne : la lecture se fait lorsqu'une   */
/*    ligne complète est saisie (terminée par la touche */
/*    Entrée). 					  */
/*  mode non-canonique : l'écho est supprimé et la	  */
/*    lecture se fait caractère par caractère sans	  */
/*    attendre la fin de la ligne.			  */
/* 							  */
/*  Created on: 2017					  */
/* 	Author: C. Collet				  */
/*  Copyright 2017 IRIT-Université Toulouse 3   	  */
/*	Paul Sabatier, France. All rights reserved.	*/
/* ====================================================	*/

#define _POSIX_C_SOURCE 200809L	/* Pour respecter la norme POSIX 200809 : IEEE Std 1003.1-2008 */
/* Ligne précédente a commenter si _POSIX_C_SOURCE a été définie par ailleurs */
#include "term_canon.h"
#include <stdio.h>
#include <sys/termios.h>	/* le terminal non canonique */
#include <unistd.h>

/* ANSI/VT100 term color and formatting from			*/
/* https://misc.flogisoft.com/bash/tip_colors_and_formatting	*/

/* Term_non_canonique =================================
//  Permet de lire le clavier touche par touche, sans
// écho.
//===================================================*/

int Term_non_canonique ()
{
    struct termios	term;

    tcgetattr( fileno(stdin), &term );	/* lit les flags du terminal dans term */
    term.c_lflag &= ~ICANON;		/* mode non-canonique */
    term.c_lflag &= ~ECHO;		/* supprime l'écho */
    term.c_cc[VMIN]  = 1;		/* nombre min de caractères */
    term.c_cc[VTIME] = 1;		/* latence (timeout) 1/10e de seconde (0: pas de latence) */
    if (tcsetattr( fileno(stdin), TCSANOW, &term)<0) /* écrit les flags depuis term */
    {
	perror("Term_non_canonique: problème d'initialisation ");
	return 0;
    }
    return 1;
}

/* Term_canonique =====================================
//  Mode normal du clavier: lecture par ligne et écho.
//===================================================*/

int Term_canonique ()
{
    struct termios	term;
			/* retour en mode ligne */
    tcgetattr( fileno(stdin), &term );	/* lit les flags du terminal dans term */
    term.c_lflag |= ICANON;		/* mode canonique */
    term.c_lflag |= ECHO;		/* rétablit l'écho */
    if (tcsetattr( fileno(stdin), TCSANOW, &term)<0) /* écrit les flags depuis term */
    {
	perror("Term_canonique: problème d'initialisation ");
	return 0;
    }
    return 1;
}
