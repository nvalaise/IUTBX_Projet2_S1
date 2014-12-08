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
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

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
	const int LARGEUR_IMAGE = 40;
	const int HAUTEUR_IMAGE = 60;

    int tabScores[100][100];

	SDL_Surface* sprite = chargerImage("sprite.png");
	SDL_Rect image[32];

	SDL_Surface* imageGagnantVert = chargerImage("gagne1.png");
	SDL_Surface* imageGagnantRouge = chargerImage("gagne2.png");
	SDL_Surface* imagePerdant = chargerImage("perdu.png");

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

	int nbVictoireIA = 0 ;
	int nbParties = 0 ;
};

/***********************************
Declaration des prototype
************************************/
void initPirate(Joueur &premier, Joueur &deuxieme);

void afficherPirate(Joueur &pirate, Gestion &jeu, int numeroPirate, int numeroSprite);

void deplacerPirate(Joueur &pirate, int &numeroPirate, Plateau &plateau, Gestion &jeu, Piece &unePiece);

void score(Joueur &pirate, int x, int y, Gestion &jeu, Plateau &plateau, Piece &unePiece);

int victoire(Joueur &pirate, Gestion &jeu, Plateau &plateau, Piece &unePiece, int numeroPirate);

void cleanPirate(Joueur &pirate);

void afficherScoreFinal(Joueur &pirate, Gestion &jeu, int x, int y, int i , int num);

void afficherScore(Joueur &pirate, Gestion &jeu, int x, int y, int num);

void cleanImageGagnant(Joueur &pirate);

void afficheGagnant(Joueur &pirate, Gestion &jeu, int x, int y, int numeroPirate);

void direction(Joueur &pirate, Gestion &jeu);

void sauvegarder(Joueur &premier, Joueur &deuxieme,  int numeroPirate);

void lireDonnes(Joueur &Joueur);

#endif
