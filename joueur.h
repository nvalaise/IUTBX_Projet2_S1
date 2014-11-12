#ifndef JOUEUR_H
#define JOUEUR_H

/***********************************
Declaration des includes
************************************/
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

//declaration de la SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

//fichier internes
#include "gestion.h"
#include "plateau.h"

/***********************************
Declaration des constantes
************************************/

/***********************************
Declaration des structures
************************************/
struct Joueur
{
	const int LARGEUR_IMAGE = 61;
	const int HAUTEUR_IMAGE = 61;

	SDL_Surface* sprite = chargerImageCleCouleur("pirates.png", 0, 255, 255);
	SDL_Rect image[2];

	int x, y;
	int xMatrice, yMatrice;
	int score = 0;
	int bonus=10;
	int nbBonus=0;
	int last = 0;
};

/***********************************
Declaration des prototype
************************************/
void initPirate(Joueur &prem, Joueur &deux);

void afficherPirate(Joueur &prem, Joueur &deux, Gestion &jeu, int numJoueur);

void deplacerPirate(Joueur &prem, Joueur &deux, Plateau &plateau, Gestion &jeu, int &numJoueur);

void score(Joueur &premier, Joueur &deuxieme, Gestion &jeu, Plateau &plateau, int numJoueur);

void victoire(Joueur &premier, Joueur &deuxieme, Gestion & jeu, Plateau &plateau , int numJoueur);

void cleanPirate(Joueur &pirate);

void afficherScore(Joueur &pirate, Gestion &jeu, int x, int y);

#endif
