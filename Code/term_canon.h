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


/* ANSI/VT100 term color and formatting from			*/
/* https://misc.flogisoft.com/bash/tip_colors_and_formatting	*/

/* Term_non_canonique =================================
//  Permet de lire le clavier touche par touche, sans
// écho.
//===================================================*/
int Term_non_canonique ();

/* Term_canonique =====================================
//  Mode normal du clavier: lecture par ligne et écho.
//===================================================*/
int Term_canonique ();
