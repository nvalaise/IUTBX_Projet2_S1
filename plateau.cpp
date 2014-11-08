#include "plateau.h"

using namespace std;

void initPlateau(Plateau &plateau)
{

	int x = 0;
	int y = 0;
	int valeurPiece = 0;
	int nombreAleatoire = 0;
	int nbPieceDix = 0, nbPieceVingt = 0, nbPieceTrente = 0, nbPieceCinquante = 0, nbPieceCent = 0;
	srand(time(NULL));

	for (int i = 0; i < NB_BLOCK_HAUTEUR; i++)
	{
		for (int j = 0; j < NB_BLOCK_LARGEUR; j++)
		{
			nombreAleatoire = rand() % 5 + 1;

            if((i==3) && (j==3))
            {
                plateau.position[i][j].valeurJ = 2;
            }

			if (nombreAleatoire == 1 && nbPieceDix < 14 && (i != 3 || j != 3) && (plateau.matrice[i][j-1].valeur != 10 ||
			plateau.matrice[i][j-2].valeur != 10))
			{
				nbPieceDix++;
				plateau.matrice[i][j].valeur = 10;
			}
			else if (nombreAleatoire == 2 && nbPieceVingt < 14 && (i != 3 || j != 3) && (plateau.matrice[i][j - 1].valeur != 20 ||
			plateau.matrice[i][j - 2].valeur != 20))
			{
				nbPieceVingt ++;
				plateau.matrice[i][j].valeur = 20;
			}
			else if (nombreAleatoire == 3 && nbPieceTrente < 14 && (i != 3 || j != 3) && (plateau.matrice[i][j - 1].valeur != 30 ||
			plateau.matrice[i][j - 2].valeur != 30))
			{
				nbPieceTrente++;
				plateau.matrice[i][j].valeur = 30;
			}
			else if (nombreAleatoire == 4 && nbPieceCinquante < 5 && (i != 3 || j != 3) && (plateau.matrice[i][j - 1].valeur != 50 ||
			plateau.matrice[i][j - 2].valeur != 50))
			{
				nbPieceCinquante++;
				plateau.matrice[i][j].valeur = 50;
			}
			else if (nombreAleatoire == 5 && nbPieceCent < 1 && (i != 3 || j != 3) && (plateau.matrice[i][j - 1].valeur != 100 ||
			plateau.matrice[i][j - 2].valeur != 100))
			{
				nbPieceCent++;
				plateau.matrice[i][j].valeur = 100;
			}

			else
			{
				if (nbPieceDix < 14 && (i != 3 || j != 3) && (plateau.matrice[i][j - 1].valeur != 10 || plateau.matrice[i][j - 2].valeur != 10))
				{
					nbPieceDix++;
					plateau.matrice[i][j].valeur = 10;
				}
				else if (nbPieceVingt < 14 && (i != 3 || j != 3) && (plateau.matrice[i][j - 1].valeur != 20 ||
				plateau.matrice[i][j - 2].valeur != 20))
				{
					nbPieceVingt++;
					plateau.matrice[i][j].valeur = 20;
				}
				else if (nbPieceTrente < 14 && (i != 3 || j != 3) && (plateau.matrice[i][j - 1].valeur != 30 ||
                plateau.matrice[i][j - 2].valeur != 30))
				{
					nbPieceTrente++;
					plateau.matrice[i][j].valeur = 30;
				}
				else if (nbPieceCinquante < 5 && (i != 3 || j != 3) && (plateau.matrice[i][j - 1].valeur != 50 ||
				plateau.matrice[i][j - 2].valeur !=50))
				{
					nbPieceCinquante++;
					plateau.matrice[i][j].valeur = 50;
				}
				else if (nbPieceCent < 1 && (i != 3 || j != 3) && (plateau.matrice[i][j - 1].valeur != 100 ||
				plateau.matrice[i][j - 2].valeur != 100))
				{
					nbPieceCent++;
					plateau.matrice[i][j].valeur = 100;
				}
				else
				{
					if (nbPieceDix < 14 && (i != 3 || j != 3))
					{
						nbPieceDix++;
						plateau.matrice[i][j].valeur = 10;
					}
					else if (nbPieceVingt < 14 && (i != 3 || j != 3))
					{
						nbPieceVingt++;
						plateau.matrice[i][j].valeur = 20;
					}
					else if (nbPieceTrente < 14 && (i != 3 || j != 3))
					{
						nbPieceTrente++;
						plateau.matrice[i][j].valeur = 30;
					}
					else if (nbPieceCinquante < 5 && (i != 3 || j != 3))
					{
						nbPieceCinquante++;
						plateau.matrice[i][j].valeur = 50;
					}
					else if (nbPieceCent < 1 && (i != 3 || j != 3))
					{
						nbPieceCent++;
						plateau.matrice[i][j].valeur = 100;
					}
				}
			}

			plateau.matrice[i][j].x = x;
			plateau.matrice[i][j].y = y;
			plateau.matrice[i][j].xMatrice = j;
			plateau.matrice[i][j].yMatrice = i;

			x += 61;
		}
		y += 61;
		x = 0;
	}
}

void afficherPlateau(Plateau &plateau, Gestion &jeu, Joueur &joueur)
{
	for (int i = 0; i < NB_BLOCK_HAUTEUR; i++)
	{
		for (int j = 0; j < NB_BLOCK_LARGEUR; j++)
		{
			if (plateau.matrice[i][j].valeur == 0)
			{
				plateau.matrice[i][j].image[0].x = 0;
				plateau.matrice[i][j].image[0].y = 0;
				plateau.matrice[i][j].image[0].h = plateau.matrice[i][j].HAUTEUR_IMAGE;
				plateau.matrice[i][j].image[0].w = plateau.matrice[i][j].LARGEUR_IMAGE;
				appliquerClip(plateau.matrice[i][j].x, plateau.matrice[i][j].y, plateau.matrice[i][j].sprite,
				jeu.ecran, &plateau.matrice[i][j].image[0]);
			}
			else if (plateau.matrice[i][j].valeur == 10)
			{
				plateau.matrice[i][j].image[1].x = plateau.matrice[i][j].LARGEUR_IMAGE;
				plateau.matrice[i][j].image[1].y = 0;
				plateau.matrice[i][j].image[1].h = plateau.matrice[i][j].HAUTEUR_IMAGE;
				plateau.matrice[i][j].image[1].w = plateau.matrice[i][j].LARGEUR_IMAGE;
				appliquerClip(plateau.matrice[i][j].x, plateau.matrice[i][j].y, plateau.matrice[i][j].sprite,
				jeu.ecran, &plateau.matrice[i][j].image[1]);
			}
			else if (plateau.matrice[i][j].valeur == 20)
			{
				plateau.matrice[i][j].image[2].x = plateau.matrice[i][j].LARGEUR_IMAGE * 2;
				plateau.matrice[i][j].image[2].y = 0;
				plateau.matrice[i][j].image[2].h = plateau.matrice[i][j].HAUTEUR_IMAGE;
				plateau.matrice[i][j].image[2].w = plateau.matrice[i][j].LARGEUR_IMAGE;
				appliquerClip(plateau.matrice[i][j].x, plateau.matrice[i][j].y, plateau.matrice[i][j].sprite,
				jeu.ecran, &plateau.matrice[i][j].image[2]);
			}
			else if (plateau.matrice[i][j].valeur == 30)
			{
				plateau.matrice[i][j].image[3].x = plateau.matrice[i][j].LARGEUR_IMAGE * 3;
				plateau.matrice[i][j].image[3].y = 0;
				plateau.matrice[i][j].image[3].h = plateau.matrice[i][j].HAUTEUR_IMAGE;
				plateau.matrice[i][j].image[3].w = plateau.matrice[i][j].LARGEUR_IMAGE;
				appliquerClip(plateau.matrice[i][j].x, plateau.matrice[i][j].y, plateau.matrice[i][j].sprite,
				jeu.ecran, &plateau.matrice[i][j].image[3]);
			}
			else if (plateau.matrice[i][j].valeur == 50)
			{
				plateau.matrice[i][j].image[4].x = plateau.matrice[i][j].LARGEUR_IMAGE * 4;
				plateau.matrice[i][j].image[4].y = 0;
				plateau.matrice[i][j].image[4].h = plateau.matrice[i][j].HAUTEUR_IMAGE;
				plateau.matrice[i][j].image[4].w = plateau.matrice[i][j].LARGEUR_IMAGE;
				appliquerClip(plateau.matrice[i][j].x, plateau.matrice[i][j].y, plateau.matrice[i][j].sprite,
				jeu.ecran, &plateau.matrice[i][j].image[4]);
			}
			else if (plateau.matrice[i][j].valeur == 100)
			{
				plateau.matrice[i][j].image[5].x = plateau.matrice[i][j].LARGEUR_IMAGE * 5;
				plateau.matrice[i][j].image[5].y = 0;
				plateau.matrice[i][j].image[5].h = plateau.matrice[i][j].HAUTEUR_IMAGE;
				plateau.matrice[i][j].image[5].w = plateau.matrice[i][j].LARGEUR_IMAGE;
				appliquerClip( plateau.matrice[i][j].x, plateau.matrice[i][j].y, plateau.matrice[i][j].sprite,
				jeu.ecran, &plateau.matrice[i][j].image[5]);
			}

			else if (plateau.position[i][j].valeurJ == 2)
			{
				plateau.position[i][j].pirates[1].x=0;
				plateau.position[i][j].pirates[1].y=0;
				plateau.position[i][j].pirates[1].h= plateau.position[i][j].HAUTEUR_PIRATE;
				plateau.position[i][j].pirates[1].w= plateau.position[i][j].LARGEUR_PIRATE;
				appliquerClip(plateau.matrice[i][j].x, plateau.matrice[i][j].y, plateau.position[i][j].pirate,
				jeu.ecran, &plateau.position[i][j].pirates[1]);
			}
		}
	}
}
