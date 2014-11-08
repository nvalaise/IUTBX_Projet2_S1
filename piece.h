#ifndef PIECE_H
#define PIECE_H

/***********************************
Declaration des includes
************************************/
#include <iostream>
#include <cstdlib>
#include <string>

//declaration de la SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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
void cleanPiece(Piece &unePiece);

#endif
