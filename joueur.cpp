#include "joueur.h"

using namespace std;

/******FONCTION D'INITIALISATION DU PIRATE******
  Prend en entrée
  -les deux joueurs
***********************************************/

void initPirate(Joueur &premier, Joueur &deuxieme)
{
    //initialisation des coordonnées du premier joueur
    premier.x = 3 * premier.LARGEUR_IMAGE;
	premier.y = 3 * premier.HAUTEUR_IMAGE;
    premier.score = 0;
    premier.bonus = 0;
    premier.nbBonus = 0;
    premier.last = 0;

	deuxieme.x = 3 * deuxieme.LARGEUR_IMAGE;
	deuxieme.y = 3 * deuxieme.HAUTEUR_IMAGE;
    deuxieme.score = 0;
    deuxieme.bonus = 0;
    deuxieme.nbBonus = 0;
    deuxieme.last = 0;

    //sprite du premier joueur
    premier.image[0].x = 0;
    premier.image[0].y = 0;
    premier.image[0].h = premier.HAUTEUR_IMAGE;
    premier.image[0].w = premier.LARGEUR_IMAGE;

    //sprite du deuxième joueur
    deuxieme.image[1].x = premier.LARGEUR_IMAGE;
    deuxieme.image[1].y = 0;
    deuxieme.image[1].h = premier.HAUTEUR_IMAGE;
    deuxieme.image[1].w = premier.LARGEUR_IMAGE;
}

/******FONCTION D'AFFICHAGE DU PIRATE******
  Prend en entrée
  - les deux joueurs,
  - la gestion pour la gestion des event souris
  - le numéro du joueur à gérer
***********************************************/
void afficherPirate(Joueur &pirate, Gestion &jeu, int numeroPirate)
{
	if (numeroPirate == 0){
		appliquerClip(pirate.x, pirate.y, pirate.sprite, jeu.ecran, &pirate.image[0]);
	}
	else if (numeroPirate == 1){
		appliquerClip(pirate.x, pirate.y, pirate.sprite, jeu.ecran, &pirate.image[1]);
	}
}

/******FONCTION DE DEPLACEMENT DU PIRATE******
  Prend en entrée
  - les deux joueurs,
  - le plateau pour le modifier une fois la pièce
  selectionnée
  - la gestion pour la gestion des events souris
  - le numéro du joueur pour alterner
***********************************************/
void deplacerPirate(Joueur &pirate, int &numeroPirate, Plateau &plateau ,Gestion &jeu, Piece &unePiece)
{
	int xSourisMatrice = jeu.xSouris / 61;
	int ySourisMatrice = jeu.ySouris / 61;

	const int VITESSE = 3;
	if (jeu.xSouris >= 0 && jeu.xSouris <= 427 && jeu.ySouris >= 0 && jeu.ySouris <= 427 && plateau.matrice[ySourisMatrice][xSourisMatrice].valeur != 0)
	{
		direction(pirate, jeu);
		if (pirate.bas)
		{
			score(pirate, jeu, plateau, unePiece);
			while (pirate.y < ySourisMatrice * 61)
			{
				pirate.y += VITESSE;
				plateau.matrice[ySourisMatrice][xSourisMatrice].valeur = 0;
				afficherPiecePlateau(plateau, jeu);

				afficherPirate(pirate, jeu, numeroPirate);
				SDL_Flip(jeu.ecran);
				jeu.finTour = false;
			}
			jeu.finTour = true;
		}
		else if (pirate.haut)
		{
			score(pirate, jeu, plateau, unePiece);
			while (pirate.y > ySourisMatrice * 61)
			{
				pirate.y -= VITESSE;
				plateau.matrice[ySourisMatrice][xSourisMatrice].valeur = 0;
				afficherPiecePlateau(plateau, jeu);

				afficherPirate(pirate, jeu, numeroPirate);
				SDL_Flip(jeu.ecran);
			}
			jeu.finTour = true;
		}
		else if (pirate.droite)
		{
			score(pirate, jeu, plateau, unePiece);
			while (pirate.x < xSourisMatrice * 61)
			{
				pirate.x += VITESSE;
				plateau.matrice[ySourisMatrice][xSourisMatrice].valeur = 0;
				afficherPiecePlateau(plateau, jeu);

				afficherPirate(pirate, jeu, numeroPirate);
				SDL_Flip(jeu.ecran);
			}
			jeu.finTour = true;
		}
		else if (pirate.gauche)
		{
			score(pirate, jeu, plateau, unePiece);
			while (pirate.x > xSourisMatrice * 61)
			{
				pirate.x -= VITESSE;
				plateau.matrice[ySourisMatrice][xSourisMatrice].valeur = 0;
				afficherPiecePlateau(plateau, jeu);

				afficherPirate(pirate, jeu, numeroPirate);
				SDL_Flip(jeu.ecran);
			}
			jeu.finTour = true;
		}
	}
}

void score(Joueur &pirate, Gestion &jeu, Plateau &plateau, Piece &unePiece)
{
    //gestion des scores en fonction du joueur en cours

    //son score = score précédent + valeur de la pièce
    pirate.score += plateau.matrice[jeu.ySouris / 61][jeu.xSouris / 61].valeur;

    //si la case cliqué precédemment est la même que la case cliqué par la suite
    //et ceci 4 fois maximum
    //le bonus est multiplié par 2
	if ((pirate.last == plateau.matrice[jeu.ySouris / 61][jeu.xSouris / 61].valeur) && (pirate.nbBonus < 4))
    {
		pirate.score += pirate.bonus;
		pirate.bonus = 2 * pirate.bonus;
		pirate.nbBonus++;
    }
    else
    {
		pirate.nbBonus = 0;
		pirate.bonus = 10;
    }

    //si le max est atteint, on réinitialise le bonus

	if (pirate.nbBonus > 4)
    {
		pirate.nbBonus = 0;
		pirate.bonus = 10;
    }

    //la case est enregistré pour la traiter p
	pirate.last = plateau.matrice[jeu.ySouris / 61][jeu.xSouris / 61].valeur;

    //on regarde si une des conditions de victoire est validé
	//victoire(pirate, jeu, plateau, unePiece);

	/*
	//si on joue contre l'ia
	case 2:

	x = deuxieme.x / 61;
	y = deuxieme.y / 61;

	deuxieme.score += plateau.matrice[y][x].valeur;

	if((deuxieme.last == plateau.matrice[y][x].valeur ) && (deuxieme.nbBonus < 4))
	{
	deuxieme.score += deuxieme.bonus;
	deuxieme.bonus=2*deuxieme.bonus;
	deuxieme.nbBonus++;
	}
	else
	{
	deuxieme.nbBonus = 0;
	deuxieme.bonus = 10;
	}

	if(deuxieme.nbBonus > 4)
	{
	deuxieme.nbBonus=0;
	deuxieme.bonus=10;
	}
	deuxieme.last = plateau.matrice[y][x].valeur;

	victoire(premier, deuxieme,  jeu, plateau, numJoueur, unePiece);
	break;
	*/
}

int victoire(Joueur &pirate, Gestion &jeu, Plateau &plateau, Piece &unePiece, int numeroPirate)
{
    //pour le joueur 1, si son score est supérieur à 500 ou que le joueur 2 ne peut plus bouger

	if (pirate.score >= 500)
	{
		return numeroPirate;
	}
	else
	{
		return -1;
	}
    /*//encore pleins de fonction à appliquer
    SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
	if (numeroPirate == 0)
	{
		return 0;
	}
	else if 
    afficheGagnant(premier, jeu, 240, 13, 0);
    SDL_Flip(jeu.ecran);
    SDL_Delay(2000);
    numJoueur = 0;
    initPirate(premier, deuxieme);
    placementPiecesTableau(plateau, unePiece);
    jeu.solo = false;
    jeu.duo = false;
    jeu.menu = true;
	*/
	/*
    //pour l'ia, si son score est supérieur à 500 ou que le joueur 1 ne peut plus bouger
    if((numJoueur==2) && ((deuxieme.score>=500) || (nbZero==12)))
    {
        SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
        afficheGagnant(deuxieme, jeu, 240, 13, 1);
        SDL_Flip(jeu.ecran);
        SDL_Delay(2000);
        numJoueur = 0;
        initPirate(premier, deuxieme);
        placementPiecesTableau(plateau, unePiece);
        jeu.solo = false;
        jeu.duo = false;
        jeu.menu = true;
    }
	*/
}

void cleanPirate(Joueur &pirate)
{
    //on efface les images
    SDL_FreeSurface(pirate.sprite);
}

void afficherScore(Joueur &pirate, Gestion &jeu, int x, int y)
{
    ostringstream score;

    score.flush();
    score << pirate.score;

    afficheMot(score.str(), x, y, 30, jeu, "police.ttf");
}

void afficheGagnant(Joueur &pirate, Gestion &jeu, int x, int y, int numeroPirate)
{
    switch(numeroPirate)
    {
    case 0:
        appliquerImage(x, y, pirate.imageGagnantVert, jeu.ecran);
        break;
    case 1:
        appliquerImage(x, y, pirate.imageGagnantRouge, jeu.ecran);
        break;
    }
}

void cleanImageGagnant(Joueur &pirate)
{
	SDL_FreeSurface(pirate.imageGagnantRouge);
	SDL_FreeSurface(pirate.imageGagnantVert);
}

void direction(Joueur &pirate, Gestion &jeu)
{
	pirate.bas = false;
	pirate.haut = false;
	pirate.gauche = false;
	pirate.droite = false;

	if (pirate.y / 61 < jeu.ySouris / 61 && pirate.x / 61 == jeu.xSouris / 61)
	{
		pirate.bas = true;
		pirate.haut = false;
		pirate.gauche = false;
		pirate.droite = false;
	}
	else if (pirate.y / 61 > jeu.ySouris / 61 && pirate.x / 61 == jeu.xSouris / 61)
	{
		pirate.bas = false;
		pirate.haut = true;
		pirate.gauche = false;
		pirate.droite = false;
	}
	else if (pirate.x / 61 < jeu.xSouris / 61 && pirate.y / 61 == jeu.ySouris / 61)
	{
		pirate.bas = false;
		pirate.haut = false;
		pirate.droite = true;
		pirate.gauche = false;
	}
	else if (pirate.x / 61 > jeu.xSouris / 61 && pirate.y / 61 == jeu.ySouris / 61)
	{
		pirate.bas = false;
		pirate.haut = false;
		pirate.droite = false;
		pirate.gauche = true;
	}
}