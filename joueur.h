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
#include "plateau.h"
#include "gestion.h"

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

	SDL_Surface* imageGagnantVert = chargerImage("gagne1.bmp");
	SDL_Surface* imageGagnantRouge = chargerImage("gagne2.bmp");

	int x, y;
	int score = 0;
	int bonus=10;
	int nbBonus=0;
	int last = 0;

	bool haut = false;
	bool bas = false;
	bool gauche = false;
	bool droite = false;
};

/***********************************
Declaration des prototype
************************************/
void initPirate(Joueur &prem, Joueur &deux);

void afficherPirate(Joueur &prem, Joueur &deux, Gestion &jeu, int numJoueur);

void deplacerPirate(Joueur &premier, Joueur &deuxieme , Plateau &plateau ,Gestion &jeu, int &numeroPirate, Piece &unePiece);

void score(Joueur &premier, Joueur &deuxieme, Gestion &jeu, Plateau &plateau, int numJoueur, Piece &unePiece);

void victoire(Joueur &premier, Joueur &deuxieme, Gestion &jeu, Plateau &plateau, int &numJoueur, Piece &unePiece);

void cleanPirate(Joueur &pirate);

void afficherScore(Joueur &pirate, Gestion &jeu, int x, int y);

void cleanImageGagnant(Joueur &pirate);

void afficheGagnant(Joueur &pirate, Gestion &jeu, int x, int y, int numeroPirate);

void marcher(Joueur &premier, Joueur &deuxieme, int &x1, int &x2, int &y1, int &y2, Plateau &plateau, int numeroPirate);

void direction(Joueur &premier, Joueur &deuxieme, Gestion &jeu, int numeroPirate);

#endif
