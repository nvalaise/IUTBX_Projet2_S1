#include "joueur.h"

using namespace std;

void initPirate(Joueur &premier, Joueur &deuxieme)
{
    premier.xMatrice = 3;
    premier.yMatrice = 3;

    premier.image[0].x = 0;
    premier.image[0].y = 0;
    premier.image[0].h = premier.HAUTEUR_IMAGE;
    premier.image[0].w = premier.LARGEUR_IMAGE;

    deuxieme.image[1].x = premier.LARGEUR_IMAGE;
    deuxieme.image[1].y = 0;
    deuxieme.image[1].h = premier.HAUTEUR_IMAGE;
    deuxieme.image[1].w = premier.LARGEUR_IMAGE;
}

void afficherPirate(Joueur &premier, Joueur &deuxieme, Gestion &jeu, int numeroPirate)
{

    if (numeroPirate == 0)
    {
		//position réelle à l'écran
		premier.x = premier.xMatrice * premier.LARGEUR_IMAGE;
		premier.y = premier.yMatrice * premier.HAUTEUR_IMAGE;
        appliquerClip(premier.x, premier.y, premier.sprite, jeu.ecran, &premier.image[0]);
    }
    else if (numeroPirate == 1)
    {
		//position réelle à l'écran
		deuxieme.x = premier.xMatrice * premier.LARGEUR_IMAGE;
		deuxieme.y = premier.yMatrice * premier.HAUTEUR_IMAGE;
        appliquerClip(deuxieme.x, deuxieme.y, deuxieme.sprite, jeu.ecran, &deuxieme.image[1]);
    }
}

void deplacerPirate(Joueur &premier, Joueur &deuxieme , Plateau &plateau ,Gestion &jeu, int &numeroPirate)
{
    int x1 = jeu.xSouris / premier.LARGEUR_IMAGE;
    int y1 = jeu.ySouris / premier.HAUTEUR_IMAGE;

    int x2 = jeu.xSouris / premier.LARGEUR_IMAGE;
    int y2 = jeu.ySouris / premier.HAUTEUR_IMAGE;

    //si le joueur 1 clique sur une case non vide horizontale ou verticale à sa position, on le déplace
    if(((x1 == premier.xMatrice) || (y1 == premier.yMatrice)) && (numeroPirate == 0) && (plateau.matrice[y1][x1].valeur != 0))
    {
        //sélection de la case
        premier.xMatrice = x1;
        premier.yMatrice = y1;

        //score de la case addition au score cumulé du joueur
        premier.score += plateau.matrice[y1][x1].valeur;

        //on enlève la case
        plateau.matrice[y1][x1].valeur = 0;

        //on prévoit de changer de personnage
        numeroPirate = 1;

        //on veut que l'autre joueur démarre d'où le joueur précédent à cliqué
        deuxieme.xMatrice = premier.xMatrice;
        deuxieme.yMatrice = premier.yMatrice;

        cout << "j1:" << premier.score << " j2:"<< deuxieme.score << endl ;
    }

    //si le joueur 2 clique sur une case non vide horizontale ou verticale à sa position, on le déplace
    else if(((x2 == deuxieme.xMatrice) || (y2 == deuxieme.yMatrice)) && (numeroPirate == 1) && (plateau.matrice[y2][x2].valeur != 0))
    {
        //pareil que précédemment
        deuxieme.xMatrice = x2;
        deuxieme.yMatrice = y2;

        deuxieme.score += plateau.matrice[y2][x2].valeur;

        plateau.matrice[y2][x2].valeur = 0;

        numeroPirate = 0;

        premier.xMatrice = deuxieme.xMatrice;
        premier.yMatrice = deuxieme.yMatrice;

        cout << "j1:" << premier.score << " j2:"<< deuxieme.score << endl ;
    }
}

void cleanPirate(Joueur &pirate)
{
	SDL_FreeSurface(pirate.sprite);
}