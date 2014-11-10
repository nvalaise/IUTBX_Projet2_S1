#include "joueur.h"

using namespace std;

void initPirate(Joueur &pirate)
{
	pirate.xMatrice = 3;
	pirate.yMatrice = 3;

	pirate.x = pirate.xMatrice * pirate.LARGEUR_IMAGE;
	pirate.y = pirate.yMatrice * pirate.HAUTEUR_IMAGE;
	
	pirate.image[0].x = 0;
	pirate.image[0].y = 0;
	pirate.image[0].h = pirate.HAUTEUR_IMAGE;
	pirate.image[0].w = pirate.LARGEUR_IMAGE;

	pirate.image[1].x = pirate.LARGEUR_IMAGE;
	pirate.image[1].y = 0;
	pirate.image[1].h = pirate.HAUTEUR_IMAGE;
	pirate.image[1].w = pirate.LARGEUR_IMAGE;
}

void afficherPirate(Joueur &pirate, Gestion &jeu, int numeroPirate)
{
	if (numeroPirate == 0)
	{
		appliquerClip(pirate.x, pirate.y, pirate.sprite, jeu.ecran, &pirate.image[0]);
	}
	else if (numeroPirate == 1)
	{
		appliquerClip(pirate.x, pirate.y, pirate.sprite, jeu.ecran, &pirate.image[1]);
	}
}