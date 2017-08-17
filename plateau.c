#include "plateau.h"

using namespace std;

void placementPiecesTableau(Plateau &plateau, Piece &unePiece)
{

	int x = 0;
	int y = 0;
	int nbPieceDix = 0, nbPieceVingt = 0, nbPieceTrente = 0, nbPieceCinquante = 0, nbPieceCent = 0;
	srand(time(NULL));

    //on place les pièces par ordre croissante suivant les règles du jeu
	for (int i = 0; i < NB_BLOCK_HAUTEUR; i++)
	{
		for (int j = 0; j < NB_BLOCK_LARGEUR; j++)
		{
		    //la case du milieu doit être vide
			if (i != 3 || j != 3)
			{
				if (nbPieceDix < 14)
				{
					nbPieceDix++;
					plateau.matrice[i][j].valeur = 10;
				}
				else if (nbPieceVingt < 14)
				{
					nbPieceVingt++;
					plateau.matrice[i][j].valeur = 20;
				}
				else if (nbPieceTrente < 14)
				{
					nbPieceTrente++;
					plateau.matrice[i][j].valeur = 30;
				}
				else if (nbPieceCinquante < 5)
				{
					nbPieceCinquante++;
					plateau.matrice[i][j].valeur = 50;
				}
				else if (nbPieceCent < 1)
				{
					nbPieceCent++;
					plateau.matrice[i][j].valeur = 100;
				}
			}
			else
			{
				plateau.matrice[i][j].valeur = 0;
			}
			//on donne les coordonnées réelles sur la grille
			plateau.matrice[i][j].x = x;
			plateau.matrice[i][j].y = y;
			//on donne la position de la pièce sur la matrice
			plateau.matrice[i][j].xMatrice = j;
			plateau.matrice[i][j].yMatrice = i;
			x += unePiece.LARGEUR_IMAGE;
		}
		y += unePiece.HAUTEUR_IMAGE;
		x = 0;
	}

    //on va mélanger la grille
	for (int i = 0; i < 50; i++)
	{
	    //génération de valeurs aléatoires
		int x1 = rand() % 7;
		int y1 = rand() % 7;
		int x2 = rand() % 7;
		int y2 = rand() % 7;
		int tmp1, tmp2, tmp3;

		// si source au centre, on recalcul la source
		while (x1 == 3 && y1 == 3)
		{
			x1 = rand() % 7;
			y1 = rand() % 7;
		}
		// si destination au centre on recalcul la destination
		while (x2 == 3 && y2 == 3)
		{
			x2 = rand() % 7;
			y2 = rand() % 7;
		}
		// si la piece source vaut 100 on verifie que la destination n'est pas sur la colone de la croix
		if (plateau.matrice[y1][x1].valeur == 100)
		{
			while (x2 == 3 || y2 == 3)
			{
				x2 = rand() % 7;
				y2 = rand() % 7;
			}
		}

		// si la piece destination vaut 100 on verifie que la source n'est pas sur la colone de la croix
		if (plateau.matrice[y2][x2].valeur == 100)
		{
			while (x1 == 3 || y1 == 3)
			{
				x1 = rand() % 7;
				y1 = rand() % 7;
			}
		}

		// on interverti les pieces
		tmp1 = plateau.matrice[y1][x1].valeur;
		plateau.matrice[y1][x1].valeur = plateau.matrice[y2][x2].valeur;
		plateau.matrice[y2][x2].valeur = tmp1;

		tmp2 = plateau.matrice[y1][x1].xMatrice;
		plateau.matrice[y1][x1].xMatrice = plateau.matrice[y2][x2].xMatrice;
		plateau.matrice[y2][x2].xMatrice = tmp2;

		tmp3 = plateau.matrice[y1][x1].yMatrice;
		plateau.matrice[y1][x1].yMatrice = plateau.matrice[y2][x2].yMatrice;
		plateau.matrice[y2][x2].yMatrice = tmp3;
	}
}

void afficherPiecePlateau(Plateau &plateau, Gestion &jeu)
{
    //affichage des pièces sur l'écran
	for (int i = 0; i < NB_BLOCK_HAUTEUR; i++)
	{
		for (int j = 0; j < NB_BLOCK_LARGEUR; j++)
		{
			if (plateau.matrice[i][j].valeur == 0)
			{
			    //on sélectionne l'image à afficher (car elle est divisé en plusieurs clips)
				plateau.matrice[i][j].image[0].x = 0;
				plateau.matrice[i][j].image[0].y = 0;
				//hauteur et largeur de l'image
				plateau.matrice[i][j].image[0].h = plateau.matrice[i][j].HAUTEUR_IMAGE;
				plateau.matrice[i][j].image[0].w = plateau.matrice[i][j].LARGEUR_IMAGE;
				//affiche l'image sur la grille
				appliquerClip(plateau.matrice[i][j].x, plateau.matrice[i][j].y, plateau.matrice[i][j].sprite, jeu.ecran, &plateau.matrice[i][j].image[0]);
			}
			else if (plateau.matrice[i][j].valeur == 10)
			{
				plateau.matrice[i][j].image[1].x = plateau.matrice[i][j].LARGEUR_IMAGE;
				plateau.matrice[i][j].image[1].y = 0;
				plateau.matrice[i][j].image[1].h = plateau.matrice[i][j].HAUTEUR_IMAGE;
				plateau.matrice[i][j].image[1].w = plateau.matrice[i][j].LARGEUR_IMAGE;
				appliquerClip(plateau.matrice[i][j].x, plateau.matrice[i][j].y, plateau.matrice[i][j].sprite, jeu.ecran, &plateau.matrice[i][j].image[1]);
			}
			else if (plateau.matrice[i][j].valeur == 20)
			{
				plateau.matrice[i][j].image[2].x = plateau.matrice[i][j].LARGEUR_IMAGE * 2;
				plateau.matrice[i][j].image[2].y = 0;
				plateau.matrice[i][j].image[2].h = plateau.matrice[i][j].HAUTEUR_IMAGE;
				plateau.matrice[i][j].image[2].w = plateau.matrice[i][j].LARGEUR_IMAGE;
				appliquerClip(plateau.matrice[i][j].x, plateau.matrice[i][j].y, plateau.matrice[i][j].sprite, jeu.ecran, &plateau.matrice[i][j].image[2]);
			}
			else if (plateau.matrice[i][j].valeur == 30)
			{
				plateau.matrice[i][j].image[3].x = plateau.matrice[i][j].LARGEUR_IMAGE * 3;
				plateau.matrice[i][j].image[3].y = 0;
				plateau.matrice[i][j].image[3].h = plateau.matrice[i][j].HAUTEUR_IMAGE;
				plateau.matrice[i][j].image[3].w = plateau.matrice[i][j].LARGEUR_IMAGE;
				appliquerClip(plateau.matrice[i][j].x, plateau.matrice[i][j].y, plateau.matrice[i][j].sprite, jeu.ecran, &plateau.matrice[i][j].image[3]);
			}
			else if (plateau.matrice[i][j].valeur == 50)
			{
				plateau.matrice[i][j].image[4].x = plateau.matrice[i][j].LARGEUR_IMAGE * 4;
				plateau.matrice[i][j].image[4].y = 0;
				plateau.matrice[i][j].image[4].h = plateau.matrice[i][j].HAUTEUR_IMAGE;
				plateau.matrice[i][j].image[4].w = plateau.matrice[i][j].LARGEUR_IMAGE;
				appliquerClip(plateau.matrice[i][j].x, plateau.matrice[i][j].y, plateau.matrice[i][j].sprite, jeu.ecran, &plateau.matrice[i][j].image[4]);
			}
			else if (plateau.matrice[i][j].valeur == 100)
			{
				plateau.matrice[i][j].image[5].x = plateau.matrice[i][j].LARGEUR_IMAGE * 5;
				plateau.matrice[i][j].image[5].y = 0;
				plateau.matrice[i][j].image[5].h = plateau.matrice[i][j].HAUTEUR_IMAGE;
				plateau.matrice[i][j].image[5].w = plateau.matrice[i][j].LARGEUR_IMAGE;
				appliquerClip(plateau.matrice[i][j].x, plateau.matrice[i][j].y, plateau.matrice[i][j].sprite, jeu.ecran, &plateau.matrice[i][j].image[5]);
			}
		}
	}
}

void afficherBonus(Gestion &jeu, Plateau &plateau, int x, int y, int nbBonus)
{
    //suivant le niveau du bonus, on affiche une image différente
	if (nbBonus == 0)
	{
		appliquerImage(x, y, plateau.bonus1, jeu.ecran);
	}
	else if (nbBonus == 1)
	{
		appliquerImage(x, y, plateau.bonus2, jeu.ecran);
	}
	else if(nbBonus == 2)
	{
		appliquerImage(x, y, plateau.bonus3, jeu.ecran);
	}
	else if(nbBonus == 3)
	{
		appliquerImage(x, y, plateau.bonus4, jeu.ecran);
	}
	else if(nbBonus == 4)
	{
		appliquerImage(x, y, plateau.bonus5, jeu.ecran);
	}
}

void cleanBonus(Plateau &plateau)
{
    //on libère les surfaces
	SDL_FreeSurface(plateau.bonus1);
	SDL_FreeSurface(plateau.bonus2);
	SDL_FreeSurface(plateau.bonus3);
	SDL_FreeSurface(plateau.bonus4);
	SDL_FreeSurface(plateau.bonus5);
}
