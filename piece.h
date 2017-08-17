#ifndef PIECE_H
#define PIECE_H

/***********************************
Declaration des includes
************************************/
#include <iostream>
#include <cstdlib>
#include <string>

//declaration de la SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

//fichier internes
#include "gestion.h"

/***********************************
Declaration des constantes
************************************/

/***********************************
Declaration des structures
************************************/
struct Piece
{
	const int LARGEUR_IMAGE = 61;
	const int HAUTEUR_IMAGE = 61;
	SDL_Surface* sprite = chargerImage("pieces.png");
	SDL_Rect image[6];
	int x, y;
	int valeur;
	int xMatrice, yMatrice;
};

/***********************************
Declaration des prototype
************************************/

/*
****************nom de la fonction******************
* cleanPiece *
****************auteur, dates***********************
* maxime *
****************description*************************
* elle libère la surface de l'image*
****************entrées*****************************
* la structure de la pièce *
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void cleanPiece(Piece &unePiece);

#endif
