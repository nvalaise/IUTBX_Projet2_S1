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
void placementPiecesTableau(Plateau &plateau, Piece &unePiece);
void afficherPiecePlateau(Plateau &plateau, Gestion &jeu);
void afficherBonus(Gestion &jeu, Plateau &plateau, int x, int y, int nbBonus);
void cleanBonus(Plateau &plateau);

#endif
