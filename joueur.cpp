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

void deplacerPirate(Joueur &pirate, Gestion &jeu, Plateau &plateau, int numeroPirate)
{
    int x = jeu.xSouris / pirate.LARGEUR_IMAGE;
    int y = jeu.ySouris / pirate.HAUTEUR_IMAGE;

    if(((x==pirate.xMatrice) || (y==pirate.yMatrice)) && (uneFois))
    {
        pirate.xMatrice = jeu.xSouris / pirate.LARGEUR_IMAGE;
        pirate.yMatrice = jeu.ySouris / pirate.HAUTEUR_IMAGE;

        pirate.x = pirate.xMatrice * pirate.LARGEUR_IMAGE;
        pirate.y = pirate.yMatrice * pirate.HAUTEUR_IMAGE;
/*************
On peut affecter le score comme ça :
        pirate.score += plateau.matrice[pirate.xMatrice][pirate.yMatrice].valeur;
        cout << pirate.score << endl ;
mais ça fait une boucle infini ...
**************/
    }
}
