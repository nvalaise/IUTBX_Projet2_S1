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

/*
****************nom de la fonction******************
* init pirate*
****************auteur, dates***********************
* maxime *
****************description*************************
* elle initialise la position des pirates et leurs
* images *
****************entrées*****************************
* les 2 joueurs *
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void initPirate(Joueur &premier, Joueur &deuxieme);

/*
****************nom de la fonction******************
* afficher pirate*
****************auteur, dates***********************
* maxime *
****************description*************************
* affiche le pirate sélectionné et prend un sprite 
 pour qu'il puisse marcher *
****************entrées*****************************
* un joueur, son numéro, le plateau avec les pieces
la gestion du jeu avec les variables utiles, et 
l'image du sprite qu'on veut*
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void afficherPirate(Joueur &pirate, Gestion &jeu, int numeroPirate, int numeroSprite);

/*
****************nom de la fonction******************
* deplacer pirate*
****************auteur, dates***********************
* maxime pour les pirates qui ne sont pas des IA
 et pour faire marcher le personnage et nicolas
 pour l'IA*
****************description*************************
* fait marcher les personnages en l'IA en fonction
de la case sélectionnée *
****************entrées*****************************
* un joueur, son numéron, le plateau avec les pieces
la gestion du jeu pour les variables(event ...), 
et la structure d'une piece *
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void deplacerPirate(Joueur &pirate, int &numeroPirate, Plateau &plateau, Gestion &jeu, Piece &unePiece);

/*
****************nom de la fonction******************
* score *
****************auteur, dates***********************
* nicolas pour les bonus et la gestion des scores
maxime pour le bruitage des pieces *
****************description*************************
* augmente le score du pirate qui attrape la piece
et gère les bonus. Quand on attrape une piece, 
ca joue un son (différent selon les pieces)*
****************entrées*****************************
* un joueur, sa position dans la matrice, la gestion
du jeu pour les variables, le plateau avec les
pieces, et la structure d'une piece*
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void score(Joueur &pirate, int x, int y, Gestion &jeu, Plateau &plateau, Piece &unePiece);

/*
****************nom de la fonction******************
* victoire*
****************auteur, dates***********************
* maxime *
****************description*************************
* regarde si on a dépassé le score max (500) ou si
on peut encore bouger (si il y a moins de 14 trou
sur la ligne et la colone du pirate)*
****************entrées*****************************
* un pirate, la gestion du jeu pour connaitre les 
variables, le plateau de pieces, la structure d'une
piece, et le numéro du pirate*
****************sorties*****************************
* elle renvoie le numéro du pirate qui a gagné si
le score est > 500 ou le pirate qui a perdu si le
nombre de zéro > 14. Sinon ça renvoie -1 pour 
dire que personne n'a encore perdu ou gagné*
****************************************************
*/
int victoire(Joueur &pirate, Gestion &jeu, Plateau &plateau, Piece &unePiece, int numeroPirate);

/*
****************nom de la fonction******************
* clean pirate*
****************auteur, dates***********************
* maxime *
****************description*************************
* supprime le sprite qu'on a chargé au début qui
contient les images des personnages*
****************entrées*****************************
* la structure d'un pirate *
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void cleanPirate(Joueur &pirate);

/*
****************nom de la fonction******************
* afficherScoreFinal*
****************auteur, dates***********************
* nicolas *
****************description*************************
* affiche le score dans le menu score *
****************entrées*****************************
* un joueur, la gestion du jeu pour les variables, 
la position en x et en y pour l'afficher, la colonne
du tableau qui contient les scores et le numrero du
pirate *
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void afficherScoreFinal(Joueur &pirate, Gestion &jeu, int x, int y, int i , int num);

/*
****************nom de la fonction******************
* afficher score*
****************auteur, dates***********************
* nicolas *
****************description*************************
* affiche les scores en cours de partie *
****************entrées*****************************
* un joueur, la gestion du jeu, une position x et y 
pour l'affichage et le numero du pirate*
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void afficherScore(Joueur &pirate, Gestion &jeu, int x, int y, int num);

/*
****************nom de la fonction******************
* clean image gagnant*
****************auteur, dates***********************
* maxime *
****************description*************************
* efface les images des gagnant*
****************entrées*****************************
* un joueur *
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void cleanImageGagnant(Joueur &pirate);

/*
****************nom de la fonction******************
* affiche gagnant*
****************auteur, dates***********************
* maxime *
****************description*************************
* affiche l'image correspondant au gagnant *
****************entrées*****************************
* un joueur, la gestion du jeu pour les variables, 
une positio x et y pour l'affichage et le numero du 
pirate*
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void afficheGagnant(Joueur &pirate, Gestion &jeu, int x, int y, int numeroPirate);

/*
****************nom de la fonction******************
* directio,*
****************auteur, dates***********************
* maxime *
****************description*************************
* choisit la direction du pirate en fonction du clic
du joueur *
****************entrées*****************************
* les 2 joueurs *
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void direction(Joueur &pirate, Gestion &jeu);

/*
****************nom de la fonction******************
* sauvegarder*
****************auteur, dates***********************
* nicolas *
****************description*************************
* sauvegarde les données nécessaire pour le menu 
score *
****************entrées*****************************
* les 2 joueurs et le numero du pirate *
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void sauvegarder(Joueur &premier, Joueur &deuxieme,  int numeroPirate);

/*
****************nom de la fonction******************
* lire donnees*
****************auteur, dates***********************
* nicolas *
****************description*************************
* lis les données qu'on a sauvegarder*
****************entrées*****************************
* un joueur *
****************sorties*****************************
* elle renvoie rien *
****************************************************
*/
void lireDonnes(Joueur &Joueur);

#endif
