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

	SDL_Surface* bonus1 = chargerImageCleCouleur("bonus1.png", 0, 255, 255);
	SDL_Surface* bonus2 = chargerImageCleCouleur("bonus2.png", 0, 255, 255);
	SDL_Surface* bonus3 = chargerImageCleCouleur("bonus3.png", 0, 255, 255);
	SDL_Surface* bonus4 = chargerImageCleCouleur("bonus4.png", 0, 255, 255);
	SDL_Surface* bonus5 = chargerImageCleCouleur("bonus5.png", 0, 255, 255);
};

/***********************************
Declaration des prototype
************************************/
void placementPiecesTableau(Plateau &plateau, Piece &unePiece);
void afficherPiecePlateau(Plateau &plateau, Gestion &jeu);
void afficherBonus(Gestion &jeu, Plateau &plateau, int x, int y, int nbBonus);
void cleanBonus(Plateau &plateau);

#endif
