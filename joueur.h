#ifndef JOUEUR_H
#define JOUEUR_H

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
struct Joueur
{
    const int LARGEUR_PIRATE = 61;
	const int HAUTEUR_PIRATE = 61;

	SDL_Surface* pirate = chargerImage("piratesSprite2.bmp");
	SDL_Rect pirates[2];

	int xJ, yJ;
	int valeur;
	int score;
};

/***********************************
Declaration des prototype
************************************/

//void deplacementPirate(Joueur &joueur, Plateau &plateau);

#endif
