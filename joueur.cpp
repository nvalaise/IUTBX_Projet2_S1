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
void afficherPirate(Joueur &premier, Joueur &deuxieme, Gestion &jeu, int numeroPirate)
{
	if (numeroPirate == 0){
		appliquerClip(premier.x, premier.y, premier.sprite, jeu.ecran, &premier.image[0]);
	}
	else if (numeroPirate == 1){
		appliquerClip(deuxieme.x, deuxieme.y, deuxieme.sprite, jeu.ecran, &deuxieme.image[1]);
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
void deplacerPirate(Joueur &premier, Joueur &deuxieme, Plateau &plateau ,Gestion &jeu, int &numeroPirate, Piece &unePiece)
{
	int xSourisMatrice = jeu.xSouris / 61;
	int ySourisMatrice = jeu.ySouris / 61;

	const int VITESSE = 3;

	SDL_Surface *dessinPirate = NULL;
	SDL_Rect unDessinPirate[2];
	dessinPirate = chargerImageCleCouleur("pirates.png", 0, 255, 255);
	unDessinPirate[0].x = 0;
	unDessinPirate[0].y = 0;
	unDessinPirate[0].h = premier.HAUTEUR_IMAGE;
	unDessinPirate[0].w = premier.LARGEUR_IMAGE;
	unDessinPirate[1].x = premier.HAUTEUR_IMAGE;;
	unDessinPirate[1].y = 0;
	unDessinPirate[1].h = premier.HAUTEUR_IMAGE;
	unDessinPirate[1].w = premier.LARGEUR_IMAGE;

	if (jeu.xSouris >= 0 && jeu.xSouris <= 427 && jeu.ySouris >= 0 && jeu.ySouris <= 427)
	{
		if (numeroPirate == 0)
		{
			premier.bas = false;
			premier.haut = false;
			premier.gauche = false;
			premier.droite = false;
			direction(premier, deuxieme, jeu, numeroPirate);
			if (premier.bas)
			{
				while (premier.y <= ySourisMatrice * 61)
				{
					premier.y += VITESSE;
					SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
					afficherPiecePlateau(plateau, jeu);

					appliquerClip(535, 30, dessinPirate, jeu.ecran, &unDessinPirate[0]);
					appliquerClip(735, 30, dessinPirate, jeu.ecran, &unDessinPirate[1]);

					afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
					afficherScore(premier, jeu, 550, 100);

					afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
					afficherScore(deuxieme, jeu, 750, 100);
					afficherPirate(premier, deuxieme, jeu, numeroPirate);
					SDL_Flip(jeu.ecran);
					deuxieme.x = premier.x;
					deuxieme.y = premier.y;
				}
				numeroPirate = 1;
			}
			else if (premier.haut)
			{
				while (premier.y >= ySourisMatrice * 61)
				{
					premier.y -= VITESSE;
					SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
					afficherPiecePlateau(plateau, jeu);

					appliquerClip(535, 30, dessinPirate, jeu.ecran, &unDessinPirate[0]);
					appliquerClip(735, 30, dessinPirate, jeu.ecran, &unDessinPirate[1]);

					afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
					afficherScore(premier, jeu, 550, 100);

					afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
					afficherScore(deuxieme, jeu, 750, 100);
					afficherPirate(premier, deuxieme, jeu, numeroPirate);
					SDL_Flip(jeu.ecran);
					deuxieme.x = premier.x;
					deuxieme.y = premier.y;
				}
				numeroPirate = 1;
			}
			if (premier.droite)
			{
				while (premier.x <= xSourisMatrice * 61)
				{
					premier.x += VITESSE;
					SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
					afficherPiecePlateau(plateau, jeu);

					appliquerClip(535, 30, dessinPirate, jeu.ecran, &unDessinPirate[0]);
					appliquerClip(735, 30, dessinPirate, jeu.ecran, &unDessinPirate[1]);

					afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
					afficherScore(premier, jeu, 550, 100);

					afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
					afficherScore(deuxieme, jeu, 750, 100);
					afficherPirate(premier, deuxieme, jeu, numeroPirate);
					SDL_Flip(jeu.ecran);
					deuxieme.x = premier.x;
					deuxieme.y = premier.y;
				}
				numeroPirate = 1;
			}
			else if (premier.gauche)
			{
				while (premier.x >= xSourisMatrice * 61)
				{
					premier.x -= VITESSE;
					SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
					afficherPiecePlateau(plateau, jeu);

					appliquerClip(535, 30, dessinPirate, jeu.ecran, &unDessinPirate[0]);
					appliquerClip(735, 30, dessinPirate, jeu.ecran, &unDessinPirate[1]);

					afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
					afficherScore(premier, jeu, 550, 100);

					afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
					afficherScore(deuxieme, jeu, 750, 100);
					afficherPirate(premier, deuxieme, jeu, numeroPirate);
					SDL_Flip(jeu.ecran);
					deuxieme.x = premier.x;
					deuxieme.y = premier.y;
				}
				numeroPirate = 1;
			}
		}

		else if (numeroPirate == 1)
		{
			deuxieme.bas = false;
			deuxieme.haut = false;
			deuxieme.gauche = false;
			deuxieme.droite = false;
			direction(premier, deuxieme, jeu, numeroPirate);
			if (deuxieme.bas)
			{
				while (deuxieme.y <= ySourisMatrice * 61)
				{
					deuxieme.y += VITESSE;
					SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
					afficherPiecePlateau(plateau, jeu);

					appliquerClip(535, 30, dessinPirate, jeu.ecran, &unDessinPirate[0]);
					appliquerClip(735, 30, dessinPirate, jeu.ecran, &unDessinPirate[1]);

					afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
					afficherScore(premier, jeu, 550, 100);

					afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
					afficherScore(deuxieme, jeu, 750, 100);
					afficherPirate(premier, deuxieme, jeu, numeroPirate);
					SDL_Flip(jeu.ecran);
					premier.x = deuxieme.x;
					premier.y = deuxieme.y;
				}
				numeroPirate = 0;
			}
			else if (deuxieme.haut)
			{
				while (deuxieme.y >= ySourisMatrice * 61)
				{
					deuxieme.y -= VITESSE;
					SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
					afficherPiecePlateau(plateau, jeu);

					appliquerClip(535, 30, dessinPirate, jeu.ecran, &unDessinPirate[0]);
					appliquerClip(735, 30, dessinPirate, jeu.ecran, &unDessinPirate[1]);

					afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
					afficherScore(premier, jeu, 550, 100);

					afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
					afficherScore(deuxieme, jeu, 750, 100);
					afficherPirate(premier, deuxieme, jeu, numeroPirate);
					SDL_Flip(jeu.ecran);
					premier.x = deuxieme.x;
					premier.y = deuxieme.y;
				}
				numeroPirate = 0;
			}
			if (deuxieme.droite)
			{
				while (deuxieme.x <= xSourisMatrice * 61)
				{
					deuxieme.x += VITESSE;
					SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
					afficherPiecePlateau(plateau, jeu);

					appliquerClip(535, 30, dessinPirate, jeu.ecran, &unDessinPirate[0]);
					appliquerClip(735, 30, dessinPirate, jeu.ecran, &unDessinPirate[1]);

					afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
					afficherScore(premier, jeu, 550, 100);

					afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
					afficherScore(deuxieme, jeu, 750, 100);
					afficherPirate(premier, deuxieme, jeu, numeroPirate);
					SDL_Flip(jeu.ecran);
					premier.x = deuxieme.x;
					premier.y = deuxieme.y;
				}
				numeroPirate = 0;
			}
			else if (deuxieme.gauche)
			{
				while (deuxieme.x >= xSourisMatrice * 61)
				{
					deuxieme.x -= VITESSE;
					SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
					afficherPiecePlateau(plateau, jeu);

					appliquerClip(535, 30, dessinPirate, jeu.ecran, &unDessinPirate[0]);
					appliquerClip(735, 30, dessinPirate, jeu.ecran, &unDessinPirate[1]);

					afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
					afficherScore(premier, jeu, 550, 100);

					afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
					afficherScore(deuxieme, jeu, 750, 100);
					afficherPirate(premier, deuxieme, jeu, numeroPirate);
					SDL_Flip(jeu.ecran);
					premier.x = deuxieme.x;
					premier.y = deuxieme.y;
				}
				numeroPirate = 0;
			}
		}
	}
}

void marcher(Joueur &premier, Joueur &deuxieme, int &x1, int &x2, int &y1, int &y2, Plateau &plateau, int numeroPirate)
{
    
}

void score(Joueur &premier, Joueur &deuxieme, Gestion &jeu, Plateau &plateau, int numJoueur, Piece &unePiece)
{

    int x, y;
    //gestion des scores en fonction du joueur en cours
    switch(numJoueur)
    {
    case 0:
        x = premier.x / 61;
        y = premier.x / 61;
        //son score = score précédent + valeur de la pièce
        premier.score += plateau.matrice[y][x].valeur;

        //si la case cliqué precédemment est la même que la case cliqué par la suite
        //et ceci 4 fois maximum
        //le bonus est multiplié par 2
        if((premier.last == plateau.matrice[y][x].valeur) && (premier.nbBonus < 4))
        {
            premier.score += premier.bonus;
            premier.bonus=2*premier.bonus;
            premier.nbBonus++;
        }
        else
        {
            premier.nbBonus = 0;
            premier.bonus = 10;
        }

        //si le max est atteint, on réinitialise le bonus

        if(premier.nbBonus > 4)
        {
            premier.nbBonus=0;
            premier.bonus=10;
        }

        //la case est enregistré pour la traiter p
        premier.last = plateau.matrice[y][x].valeur;

        //on regarde si une des conditions de victoire est validé
        victoire(premier, deuxieme,  jeu, plateau, numJoueur, unePiece);
        break;

    //on reprend le même code si on joue à deux
    case 1:

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
    }
}

void victoire(Joueur &premier, Joueur &deuxieme, Gestion &jeu, Plateau &plateau, int &numJoueur, Piece &unePiece)
{
    int nbZero = 0;
    int x = jeu.xSouris / premier.LARGEUR_IMAGE;
    int y = jeu.ySouris / premier.HAUTEUR_IMAGE;

    //on test les position verticales
    for(int i = 0 ; i<7 ; i ++)
    {
        //si on voit un 0
        if(plateau.matrice[i][x].valeur == 0)
            //on incrémente son nombre
            nbZero++;
    }

    //on test les position horizontales
    for(int j = 0 ; j<7 ; j++)
    {
        //si on voit un 0
        if(plateau.matrice[y][j].valeur == 0)
            //on incrémente encore ce nombre
            nbZero++;
    }

    //pour le joueur 1, si son score est supérieur à 500 ou que le joueur 2 ne peut plus bouger
    if((numJoueur==0) && ((premier.score>=500) || (nbZero==12)))
    {
        //encore pleins de fonction à appliquer
        SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
        afficheGagnant(premier, jeu, 240, 13, 0);
        SDL_Flip(jeu.ecran);
        SDL_Delay(2000);
        numJoueur = 0;
        initPirate(premier, deuxieme);
        placementPiecesTableau(plateau, unePiece);
        jeu.solo = false;
        jeu.duo = false;
        jeu.menu = true;
    }

    //pour le joueur 2, si son score est supérieur à 500 ou que le joueur 1 ne peut plus bouger
    if((numJoueur==1) && ((deuxieme.score>=500) || (nbZero==12)))
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

void direction(Joueur &premier, Joueur &deuxieme, Gestion &jeu, int numeroPirate)
{
	if (numeroPirate == 0)
	{
		if (premier.y / 61 < jeu.ySouris / 61 && premier.x / 61 == jeu.xSouris / 61)
		{
			premier.bas = true;
			premier.haut = false;
			premier.gauche = false;
			premier.droite = false;
		}
		else if (premier.y / 61 > jeu.ySouris / 61 && premier.x / 61 == jeu.xSouris / 61)
		{
			premier.bas = false;
			premier.haut = true;
			premier.gauche = false;
			premier.droite = false;
		}
		else if (premier.x / 61 < jeu.xSouris / 61 && premier.y / 61 == jeu.ySouris / 61)
		{
			premier.bas = false;
			premier.haut = false;
			premier.droite = true;
			premier.gauche = false;
		}
		else if (premier.x / 61 > jeu.xSouris / 61 && premier.y / 61 == jeu.ySouris / 61)
		{
			premier.bas = false;
			premier.haut = false;
			premier.droite = false;
			premier.gauche = true;
		}
	}

	else if (numeroPirate == 1)
	{
		if (deuxieme.y / 61 < jeu.ySouris / 61 && deuxieme.x / 61 == jeu.xSouris / 61)
		{
			deuxieme.bas = true;
			deuxieme.haut = false;
			deuxieme.gauche = false;
			deuxieme.droite = false;
		}
		else if (deuxieme.y / 61 > jeu.ySouris / 61 && deuxieme.x / 61 == jeu.xSouris / 61)
		{
			deuxieme.bas = false;
			deuxieme.haut = true;
			deuxieme.gauche = false;
			deuxieme.droite = false;
		}
		else if (deuxieme.x / 61 < jeu.xSouris / 61 && deuxieme.y / 61 == jeu.ySouris / 61)
		{
			deuxieme.bas = false;
			deuxieme.haut = false;
			deuxieme.droite = true;
			deuxieme.gauche = false;
		}
		else if (deuxieme.x / 61 > jeu.xSouris / 61 && deuxieme.y / 61 == jeu.ySouris / 61)
		{
			deuxieme.bas = false;
			deuxieme.haut = false;
			deuxieme.droite = false;
			deuxieme.gauche = true;
		}
	}
}