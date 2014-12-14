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
	bool score = false;
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

/*
****************nom de la fonction******************
* cherger image*
****************auteur, dates***********************
* maxime *
****************description*************************
* permet de charger une image *
****************entrées*****************************
* le nom du fichier *
****************sorties*****************************
* un sdl_surface en fonction de l'image demandé *
****************************************************
*/
SDL_Surface* chargerImage(std::string nomFichier);

/*
****************nom de la fonction******************
* charger image clé couleur*
****************auteur, dates***********************
* maxime *
****************description*************************
* charge une image avec un couleur en transparence*
****************entrées*****************************
* le nom du fichier *
****************sorties*****************************
* un sdl_surface en fonction de l'image demandé *
****************************************************
*/
SDL_Surface* chargerImageCleCouleur(std::string nomFichier, int rouge, int vert, int bleu);

/*
****************nom de la fonction******************
* appliquer image*
****************auteur, dates***********************
* maxime *
****************description*************************
* applique l'image sur l'ecran, (affichage de l'image)*
****************entrées*****************************
* sa position x et y, l'image, et l'ecran *
****************sorties*****************************
* rien *
****************************************************
*/
void appliquerImage(int x, int y, SDL_Surface* source, SDL_Surface* destination);

/*
****************nom de la fonction******************
* appliquer clip*
****************auteur, dates***********************
* maxime *
****************description*************************
* afficher un morceau d'image sur l'ecran*
****************entrées*****************************
* sa position x et y, l'image, et l'ecran, et le morceau *
****************sorties*****************************
* rien *
****************************************************
*/
void appliquerClip(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

/*
****************nom de la fonction******************
* affiche mot*
****************auteur, dates***********************
* maxime *
****************description*************************
* afficher un mot sur l'ecran*
****************entrées*****************************
* le message, sa position en x et y, la taille de 
la police, la gestion du jeu pour les variables
et le nom de la police*
****************sorties*****************************
* rien *
****************************************************
*/
void afficheMot(std::string message, int x, int y, int taillePolice, Gestion &jeu, std::string nomPolice);

#endif
