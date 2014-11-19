#ifndef JOUEUR_H
#define JOUEUR_H

/***********************************
Declaration des includes
************************************/
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>


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

    int tabScores[300][300];

	SDL_Surface* sprite = chargerImageCleCouleur("pirates.png", 0, 255, 255);
	SDL_Rect image[2];

	SDL_Surface* imageGagnantVert = chargerImage("gagne1.bmp");
	SDL_Surface* imageGagnantRouge = chargerImage("gagne2.bmp");

	int x, y;
	int score = 0;
	int bonus=10;
	int nbBonus=0;
	int last = 0;
    int tour = 0;


	bool haut = false;
	bool bas = false;
	bool gauche = false;
	bool droite = false;
};

/***********************************
Declaration des prototype
************************************/
void initPirate(Joueur &premier, Joueur &deuxieme);

void afficherPirate(Joueur &pirate, Gestion &jeu, int numeroPirate);

void deplacerPirate(Joueur &pirate, int &numeroPirate, Plateau &plateau, Gestion &jeu, Piece &unePiece);

void score(Joueur &pirate, Gestion &jeu, Plateau &plateau, Piece &unePiece);

int victoire(Joueur &pirate, Gestion &jeu, Plateau &plateau, Piece &unePiece, int numeroPirate);

void cleanPirate(Joueur &pirate);

void afficherScore(Joueur &pirate, Gestion &jeu, int x, int y);

void cleanImageGagnant(Joueur &pirate);

void afficheGagnant(Joueur &pirate, Gestion &jeu, int x, int y, int numeroPirate);

void direction(Joueur &pirate, Gestion &jeu);

void sauvegarder(Joueur &premier, Joueur &deuxieme,  int numeroPirate);

void lireDonnes(Joueur &Joueur);


#endif
