#ifndef PLATEAU_H
#define PLATEAU_H

/***********************************
Declaration des includes
************************************/
#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>

//declaration de la SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//fichier interne
#include "piece.h"
#include "gestion.h"

/***********************************
Declaration des constantes
************************************/
const int NB_BLOCK_HAUTEUR = 7;
const int NB_BLOCK_LARGEUR = 7;

/***********************************
Declaration des structures
************************************/
struct Plateau
{
	Piece matrice[NB_BLOCK_HAUTEUR][NB_BLOCK_LARGEUR];

	SDL_Surface* bonus1 = chargerImage("bonus1.png");
	SDL_Surface* bonus2 = chargerImage("bonus2.png");
	SDL_Surface* bonus3 = chargerImage("bonus3.png");
	SDL_Surface* bonus4 = chargerImage("bonus4.png");
	SDL_Surface* bonus5 = chargerImage("bonus5.png");
};

/***********************************
Declaration des prototype
************************************/

/*
****************nom de la fonction******************
* placementPiecesTableau *
****************auteur, dates***********************
* maxime *
****************description*************************
* elle place les pièces de façon non aléatoire
* c'est à dire qu'on les dispose sur la grille par
* ordre croissant, en respectant le nombre de chaque
* pièce.
* ensuite elle les mélangent *
****************entrées*****************************
* la structure de la pièce et du plateau *
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void placementPiecesTableau(Plateau &plateau, Piece &unePiece);

/*
****************nom de la fonction******************
* afficherPiecePlateau *
****************auteur, dates***********************
* maxime *
****************description*************************
* elle affiche les pièces en fonction des valeurs
* attribuées précédemment *
****************entrées*****************************
* la structure de la pièce et du plateau *
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void afficherPiecePlateau(Plateau &plateau, Gestion &jeu);

/*
****************nom de la fonction******************
* cleanBonus*
****************auteur, dates***********************
* maxime *
****************description*************************
* en fonction de l'atat des bonus
* on va afficher une image différente *
****************entrées*****************************
* la structure de la gestion et du plateau
* les coordonnées et le niveau du bonus
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void afficherBonus(Gestion &jeu, Plateau &plateau, int x, int y, int nbBonus);

/*
****************nom de la fonction******************
* cleanBonus *
****************auteur, dates***********************
* maxime *
****************description*************************
* elle libère la surface de l'image*
****************entrées*****************************
* la structure du plateau *
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void cleanBonus(Plateau &plateau);

#endif
