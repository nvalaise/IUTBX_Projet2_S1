#include "plateau.h"

using namespace std;

void placementPiecesTableau(Plateau &plateau)
{

	int x = 0;
	int y = 0;
	int valeurPiece = 0;
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
=======
			if (i != 3 || j != 3)
>>>>>>> d7d04689bf5e7163932c09825a09ddc25c7ad70c
			{
				if (nbPieceDix < 14)
				{
					nbPieceDix++;
					plateau.matrice[i][j].valeur = 10;
				}
<<<<<<< HEAD
				else if (nbPieceVingt < 14 && (i != 3 || j != 3) && (plateau.matrice[i][j - 1].valeur != 20 ||
				plateau.matrice[i][j - 2].valeur != 20))
=======
				else if (nbPieceVingt < 14)
>>>>>>> d7d04689bf5e7163932c09825a09ddc25c7ad70c
				{
					nbPieceVingt++;
					plateau.matrice[i][j].valeur = 20;
				}
<<<<<<< HEAD
				else if (nbPieceTrente < 14 && (i != 3 || j != 3) && (plateau.matrice[i][j - 1].valeur != 30 ||
                plateau.matrice[i][j - 2].valeur != 30))
=======
				else if (nbPieceTrente < 14)
>>>>>>> d7d04689bf5e7163932c09825a09ddc25c7ad70c
				{
					nbPieceTrente++;
					plateau.matrice[i][j].valeur = 30;
				}
<<<<<<< HEAD
				else if (nbPieceCinquante < 5 && (i != 3 || j != 3) && (plateau.matrice[i][j - 1].valeur != 50 ||
				plateau.matrice[i][j - 2].valeur !=50))
=======
				else if (nbPieceCinquante < 5)
>>>>>>> d7d04689bf5e7163932c09825a09ddc25c7ad70c
				{
					nbPieceCinquante++;
					plateau.matrice[i][j].valeur = 50;
				}
<<<<<<< HEAD
				else if (nbPieceCent < 1 && (i != 3 || j != 3) && (plateau.matrice[i][j - 1].valeur != 100 ||
				plateau.matrice[i][j - 2].valeur != 100))
=======
				else if (nbPieceCent < 1)
>>>>>>> d7d04689bf5e7163932c09825a09ddc25c7ad70c
				{
					nbPieceCent++;
					plateau.matrice[i][j].valeur = 100;
				}
			}
			else
			{
				plateau.matrice[i][j].valeur = 0;
			}
			plateau.matrice[i][j].x = x;
			plateau.matrice[i][j].y = y;
			plateau.matrice[i][j].xMatrice = j;
			plateau.matrice[i][j].yMatrice = i;
<<<<<<< HEAD

=======
>>>>>>> d7d04689bf5e7163932c09825a09ddc25c7ad70c
			x += 61;
		}
		y += 61;
		x = 0;
	}
	
	for (int i = 0; i < 50; i++)
	{
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
<<<<<<< HEAD

			else if (plateau.position[i][j].valeurJ == 2)
			{
				plateau.position[i][j].pirates[1].x=0;
				plateau.position[i][j].pirates[1].y=0;
				plateau.position[i][j].pirates[1].h= plateau.position[i][j].HAUTEUR_PIRATE;
				plateau.position[i][j].pirates[1].w= plateau.position[i][j].LARGEUR_PIRATE;
				appliquerClip(plateau.matrice[i][j].x, plateau.matrice[i][j].y, plateau.position[i][j].pirate,
				jeu.ecran, &plateau.position[i][j].pirates[1]);
			}
=======
>>>>>>> d7d04689bf5e7163932c09825a09ddc25c7ad70c
		}
	}
}
