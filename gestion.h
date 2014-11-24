#ifndef GESTION_H
#define GESTION_H

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
#include <SDL_mixer.h>

/***********************************
Declaration des constantes
************************************/

/***********************************
Declaration des structures
************************************/
struct Gestion
{
	const int LARGEUR_ECRAN = 877;
	const int HAUTEUR_ECRAN = 427;
	const int BPP_ECRAN = 24;

	const int LARGEUR_BOUTON = 109;
	const int HAUTEUR_BOUTON = 30;

	SDL_Surface *ecran, *sonOn, *sonOff = NULL;
	SDL_Event event;

	//pour appuyer sur les touches du clavier
	Uint8 *kestates = SDL_GetKeyState(NULL);

	//quitter le jeu
	bool quit = false;
	bool menu = true;
	bool solo = false;
	bool duo = false;
	bool finTour = false;
	bool sonBientotFin = true;
	bool sonActive = true;

	Mix_Chunk *sonPiece, *sonNiveauTermine, *sonPieceCent, *sonResteCinquante, *sonPerdu;

	int ySouris, xSouris;
	int nbZero = 0;
};

/***********************************
Declaration des prototype
************************************/

SDL_Surface* chargerImage(std::string nomFichier);

SDL_Surface* chargerImageCleCouleur(std::string nomFichier, int rouge, int vert, int bleu);

void appliquerImage(int x, int y, SDL_Surface* source, SDL_Surface* destination);

void appliquerClip(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

void afficheMot(std::string message, int x, int y, int taillePolice, Gestion &jeu, std::string nomPolice);

#endif
