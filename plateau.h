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
#include "joueur.h"
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
	Joueur position[NB_BLOCK_HAUTEUR][NB_BLOCK_LARGEUR];
};

/***********************************
Declaration des prototype
************************************/
<<<<<<< HEAD
void initPlateau(Plateau &plateau);
void afficherPlateau(Plateau &plateau, Gestion &jeu, Joueur &joueur);
=======
void placementPiecesTableau(Plateau &plateau);
void afficherPlateau(Plateau &plateau, Gestion &jeu);
>>>>>>> d7d04689bf5e7163932c09825a09ddc25c7ad70c

#endif
