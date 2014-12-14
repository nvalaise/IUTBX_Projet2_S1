#include "joueur.h"

using namespace std;

void initPirate(Joueur &premier, Joueur &deuxieme)
{
    //initialisation des coordonnées du premier joueur
    premier.x = 3 * 61;
    premier.y = 3 * 61;
    premier.score = 0;
    premier.bonus = 0;
    premier.nbBonus = 0;
    premier.last = 0;

	deuxieme.x = 3 * 61;
	deuxieme.y = 3 * 61;
    deuxieme.score = 0;
    deuxieme.bonus = 0;
    deuxieme.nbBonus = 0;
    deuxieme.last = 0;

	//chargement des morceau de personnage pour le faire marcher
	int j = 0;
	for (int i = 0; i < 4; i++)
	{
		premier.image[i].x = i * premier.LARGEUR_IMAGE;
		premier.image[i].y = 0;
		premier.image[i].h = premier.HAUTEUR_IMAGE;
		premier.image[i].w = premier.LARGEUR_IMAGE;
	}
	for (int i = 4; i < 8; i++)
	{
		deuxieme.image[i].x = i * deuxieme.LARGEUR_IMAGE;
		deuxieme.image[i].y = 0;
		deuxieme.image[i].h = deuxieme.HAUTEUR_IMAGE;
		deuxieme.image[i].w = deuxieme.LARGEUR_IMAGE;
	}
	for (int i = 8; i < 12; i++)
	{
		premier.image[i].x = j * premier.LARGEUR_IMAGE;
		premier.image[i].y = premier.HAUTEUR_IMAGE;
		premier.image[i].h = premier.HAUTEUR_IMAGE;
		premier.image[i].w = premier.LARGEUR_IMAGE;
		j++;
	}
	for (int i = 12; i < 16; i++)
	{
		deuxieme.image[i].x = j * deuxieme.LARGEUR_IMAGE;
		deuxieme.image[i].y = deuxieme.HAUTEUR_IMAGE;
		deuxieme.image[i].h = deuxieme.HAUTEUR_IMAGE;
		deuxieme.image[i].w = deuxieme.LARGEUR_IMAGE;
		j++;
	}
	j = 0;
	for (int i = 16; i < 20; i++)
	{
		premier.image[i].x = j * premier.LARGEUR_IMAGE;
		premier.image[i].y = 2 * premier.HAUTEUR_IMAGE;
		premier.image[i].h = premier.HAUTEUR_IMAGE;
		premier.image[i].w = premier.LARGEUR_IMAGE;
		j++;
	}
	for (int i = 20; i < 24; i++)
	{
		deuxieme.image[i].x = j * deuxieme.LARGEUR_IMAGE;
		deuxieme.image[i].y = 2 * deuxieme.HAUTEUR_IMAGE;
		deuxieme.image[i].h = deuxieme.HAUTEUR_IMAGE;
		deuxieme.image[i].w = deuxieme.LARGEUR_IMAGE;
		j++;
	}
	j = 0;
	for (int i = 24; i < 28; i++)
	{
		premier.image[i].x = j * premier.LARGEUR_IMAGE;
		premier.image[i].y = 3 * premier.HAUTEUR_IMAGE;
		premier.image[i].h = premier.HAUTEUR_IMAGE;
		premier.image[i].w = premier.LARGEUR_IMAGE;
		j++;
	}
	for (int i = 28; i < 32; i++)
	{
		deuxieme.image[i].x = j * deuxieme.LARGEUR_IMAGE;
		deuxieme.image[i].y = 3 * deuxieme.HAUTEUR_IMAGE;
		deuxieme.image[i].h = deuxieme.HAUTEUR_IMAGE;
		deuxieme.image[i].w = deuxieme.LARGEUR_IMAGE;
		j++;
	}

}

void afficherPirate(Joueur &pirate, Gestion &jeu, int numeroPirate, int numeroSprite)
{
    if (numeroPirate == 0)
    {
		appliquerClip(pirate.x + 11, pirate.y + 1, pirate.sprite, jeu.ecran, &pirate.image[numeroSprite]);
    }
    else if (numeroPirate == 1)
    {
		appliquerClip(pirate.x + 11, pirate.y + 1, pirate.sprite, jeu.ecran, &pirate.image[numeroSprite]);
    }

    else if (numeroPirate == 2)
    {
		appliquerClip(pirate.x + 11, pirate.y + 1, pirate.sprite, jeu.ecran, &pirate.image[numeroSprite]);
    }
}

void deplacerPirate(Joueur &pirate, int &numeroPirate, Plateau &plateau ,Gestion &jeu, Piece &unePiece)
{
    int xSourisMatrice = jeu.xSouris / 61;
    int ySourisMatrice = jeu.ySouris / 61;

    int xDepart = pirate.x/61;
    int yDepart = pirate.y/61;

    int maximum=0;
    int altern=0;

	int delay = 60;

    const int VITESSE = 6;

	//si on est pas sur l'IA
    if((numeroPirate==0) || (numeroPirate==1))
    {
		//le clic est sur la plateau
        if (jeu.xSouris >= 0 && jeu.xSouris <= 427 && jeu.ySouris >= 0 && jeu.ySouris <= 427
                && plateau.matrice[ySourisMatrice][xSourisMatrice].valeur != 0 && ((numeroPirate==0) || (numeroPirate==1)))
        {
            direction(pirate, jeu);
			//bouge le perso en fonction des direction
            if (pirate.bas)
            {
				int a = 0;
                score(pirate, xSourisMatrice, ySourisMatrice, jeu, plateau, unePiece);
                while (pirate.y < ySourisMatrice * 61)
                {
					if (a == 4)
					{
						a = 0;
					}
                    pirate.y += VITESSE;
                    afficherPiecePlateau(plateau, jeu);
                    afficherPirate(pirate, jeu, numeroPirate, a);
					SDL_Delay(delay);
                    SDL_Flip(jeu.ecran);
                    jeu.finTour = false;
					a++;
                }
                plateau.matrice[ySourisMatrice][xSourisMatrice].valeur = 0;
                jeu.finTour = true;
            }
            else if (pirate.haut)
            {
				int a = 16;
                score(pirate, xSourisMatrice, ySourisMatrice, jeu, plateau, unePiece);
                while (pirate.y > ySourisMatrice * 61)
                {
					if (a == 20)
					{
						a = 16;
					}
                    pirate.y -= VITESSE;
                    afficherPiecePlateau(plateau, jeu);
                    afficherPirate(pirate, jeu, numeroPirate, a);
					SDL_Delay(delay);
                    SDL_Flip(jeu.ecran);
                    jeu.finTour = false;
					a++;
                }
                plateau.matrice[ySourisMatrice][xSourisMatrice].valeur = 0;
                jeu.finTour = true;
            }
            else if (pirate.droite)
            {
				int a = 8;
                score(pirate, xSourisMatrice, ySourisMatrice, jeu, plateau, unePiece);
                while (pirate.x < xSourisMatrice * 61)
                {
					if (a == 12)
					{
						a = 8;
					}
                    pirate.x += VITESSE;
                    afficherPiecePlateau(plateau, jeu);
                    afficherPirate(pirate, jeu, numeroPirate, a);
					SDL_Delay(delay);
                    SDL_Flip(jeu.ecran);
                    jeu.finTour = false;
					a++;
                }
                plateau.matrice[ySourisMatrice][xSourisMatrice].valeur = 0;
                jeu.finTour = true;
            }
            else if (pirate.gauche)
            {
				int a = 24;
                score(pirate, xSourisMatrice, ySourisMatrice, jeu, plateau, unePiece);
                while (pirate.x > xSourisMatrice * 61)
                {
					if (a == 28)
					{
						a = 24;
					}
                    pirate.x -= VITESSE;
                    afficherPiecePlateau(plateau, jeu);
                    afficherPirate(pirate, jeu, numeroPirate, a);
					SDL_Delay(delay);
                    SDL_Flip(jeu.ecran);
                    jeu.finTour = false;
					a++;
                }
                plateau.matrice[ySourisMatrice][xSourisMatrice].valeur = 0;
                jeu.finTour = true;
            }
        }
    }
	//on est sur l'ia
    else if(numeroPirate==2)
	{
		
        //les coordonnées de la matrice en entrée
        //initialisation des options
               //les coordonnées de la matrice en entrée
        //initialisation des options
        int ymax, xmax;
        int yaltern, xaltern;

        for(int i = 0; i<7; i++)
        {
            //on rehcerche le maximum...
            //...sur la colonne
            if(plateau.matrice[i][xDepart].valeur > maximum)
            {
                maximum = plateau.matrice[i][xDepart].valeur;
                ymax = i;
                xmax = xDepart;
            }
            //..sur la ligne
            if(plateau.matrice[yDepart][i].valeur > maximum)
            {
                maximum = plateau.matrice[yDepart][i].valeur;
                ymax = yDepart;
                xmax = i;
            }


            //on recherche une valeur aléatoire
            if(plateau.matrice[i][xDepart].valeur > altern && i!=ymax)
            {
                altern = plateau.matrice[i][xDepart].valeur;
                yaltern = i;
                xaltern = xDepart;
            }
            if(plateau.matrice[yDepart][i].valeur > altern && i!=xmax)
            {
                altern = plateau.matrice[yDepart][i].valeur;
                yaltern = yDepart;
                xaltern = i;
            }
        }

        //on vérifie que l'ia ne donne pas de pièces
        //trop élevées au joueur
        for(int i = 0; i<7; i++)
        {
            if(plateau.matrice[ymax][i].valeur > maximum)
            {
                ymax = yaltern ;
                xmax = xaltern ;
            }

            if(plateau.matrice[i][xmax].valeur > maximum)
            {
                ymax = yaltern ;
                xmax = xaltern ;
            }
        }



        //ici, ymax et xmam contienne les coordonnées de la valeur max sur la ligne ou la colonne
        //cout << "départ        : " << pirate.x/61 << ":" << pirate.y/61 << endl ;
        //cout << "fin (maximum) : " << xmax << ":" << ymax << endl ;

        //directionIA(pirate, xDepart, yDepart, xmax, ymax);

        if (pirate.y/61 < ymax  && pirate.x/61 == xmax)
        {
			int a = 4;
            //cout << "vers bas" << endl ;
            score(pirate, xmax , ymax ,jeu,  plateau, unePiece);
            while (pirate.y < ymax * 61)
            {
				if (a == 8)
				{
					a = 4;
				}
                pirate.y += VITESSE;
                afficherPiecePlateau(plateau, jeu);
                afficherPirate(pirate, jeu, numeroPirate, a);
				SDL_Delay(delay);
                SDL_Flip(jeu.ecran);
                jeu.finTour = false;
				a++;
            }
            plateau.matrice[ymax][xmax].valeur = 0;;
            pirate.y = ymax * 61;
            jeu.finTour = true;

        }
        else if (pirate.y/61 > ymax  && pirate.x/61 == xmax )
		{
			int a = 20;
            //cout << "vers haut" << endl ;
            score(pirate, xmax , ymax ,jeu,  plateau, unePiece);
            while (pirate.y > ymax * 61)
            {
				if (a == 24)
				{
					a = 20;
				}
                pirate.y -= VITESSE;
                afficherPiecePlateau(plateau, jeu);
                afficherPirate(pirate, jeu, numeroPirate, a);
				SDL_Delay(delay);
                SDL_Flip(jeu.ecran);
                jeu.finTour = false;
				a++;
            }
            plateau.matrice[ymax][xmax].valeur = 0;;
            pirate.y = ymax * 61;
            jeu.finTour = true;
        }
        else if (pirate.x/61 < xmax  && pirate.y/61 == ymax )
        {
			int a = 12;
            //cout << "vers droite" << endl ;
            score(pirate, xmax , ymax ,jeu,  plateau, unePiece);
            while (pirate.x < xmax * 61)
            {
				if (a == 16)
				{
					a = 12;
				}
                pirate.x += VITESSE;
                afficherPiecePlateau(plateau, jeu);
                afficherPirate(pirate, jeu, numeroPirate, a);
				SDL_Delay(delay);
                SDL_Flip(jeu.ecran);
                jeu.finTour = false;
				a++;
            }
            plateau.matrice[ymax][xmax].valeur = 0;;
            pirate.x = xmax * 61;
            jeu.finTour = true;
        }
        else if (pirate.x/61 > xmax  && pirate.y/61 == ymax )
        {
			int a = 28;
            //cout << "vers gauche" << endl ;
            score(pirate, xmax , ymax ,jeu,  plateau, unePiece);
            while (pirate.x > xmax * 61)
            {
				if (a == 32)
				{
					a = 28;
				}
                pirate.x -= VITESSE;
                afficherPiecePlateau(plateau, jeu);
                afficherPirate(pirate, jeu, numeroPirate, a);
				SDL_Delay(delay);
                SDL_Flip(jeu.ecran);
                jeu.finTour = false;
				a++;
            }
            plateau.matrice[ymax][xmax].valeur = 0;
            pirate.x = xmax * 61;
            jeu.finTour = true;
        }
    }

    if (jeu.finTour)
    {
        pirate.tour++;
        jeu.nbZero = 0;
        for (int i = 0; i < 7; i++)
        {
            if (plateau.matrice[i][pirate.x / 61].valeur == 0)
            {
                jeu.nbZero++;
            }
        }
        for (int i = 0; i < 7; i++)
        {
            if (plateau.matrice[pirate.y / 61][i].valeur == 0)
            {
                jeu.nbZero++;
            }
        }
	}
	
}

void score(Joueur &pirate, int x, int y, Gestion &jeu, Plateau &plateau, Piece &unePiece)
{
    //gestion des scores en fonction du joueur en cours

    //son score = score précédent + valeur de la pièce
    pirate.score += plateau.matrice[y][x].valeur;

    //si la case cliqué precédemment est la même que la case cliqué par la suite
    //et ceci 4 fois maximum
    //le bonus est multiplié par 2
    if (pirate.last == plateau.matrice[y][x].valeur && pirate.nbBonus < 4)
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

	//joue le son
    pirate.last = plateau.matrice[y][x].valeur;
	if (pirate.last == 10 || pirate.last == 20 || pirate.last == 30 || pirate.last == 50)
	{
		///normal
		Mix_PlayChannel(1, jeu.sonPiece, 0);
	}
	else if (pirate.last == 100)
	{
		//piece de 100
		Mix_PlayChannel(1, jeu.sonPieceCent, 0);
	}

	if (pirate.score >= 450 && jeu.sonBientotFin)
	{
		// reste 50
		Mix_PlayChannel(1, jeu.sonResteCinquante, 0);
		jeu.sonBientotFin = false;
	}

}

int victoire(Joueur &pirate, Gestion &jeu, Plateau &plateau, Piece &unePiece, int numeroPirate)
{
    //pour le joueur 1, si son score est supérieur à 500 ou que le joueur 2 ne peut plus bouger

    if (jeu.nbZero == 14)
    {
        return numeroPirate;
    }

    if (pirate.score >= 500)
    {
        return numeroPirate;
    }
    else
    {
        return -1;
    }

}

void cleanPirate(Joueur &pirate)
{
    //on efface les images
    SDL_FreeSurface(pirate.sprite);
}

void afficherScoreFinal(Joueur &pirate, Gestion &jeu, int x, int y, int i , int num)
{
    ostringstream score;
    score.flush();
    switch(num)
    {
    case 1 :
        score << pirate.tabScores[i][1];
        break;

    case 2 :
        score << pirate.tabScores[i][2];
        break;

    case 3 :
        score << pirate.nbVictoireIA;
        break;

    case 4 :
        score << pirate.nbParties;
        break;
    }
    afficheMot(score.str(), x, y, 20, jeu, "police.ttf");


}

void afficherScore(Joueur &pirate, Gestion &jeu, int x, int y, int num)
{
    ostringstream score;
    score.flush();
    switch(num)
    {
    case 1:
        score << pirate.score;
        afficheMot(score.str(), x, y, 30, jeu, "police.ttf");
        break;

    case 2:
        score << pirate.last;
        afficheMot(score.str(), x, y, 30, jeu, "police.ttf");
        break;

    case 3:
        score << pirate.tour;
        afficheMot(score.str(), x, y, 30, jeu, "police.ttf");
        break;

    case 4:
        score << 500-pirate.score;
        afficheMot(score.str(), x, y, 30, jeu, "police.ttf");
        break;
    case 5:
        score << 500-pirate.score;
        afficheMot(score.str(), x, y, 30, jeu, "police.ttf");
        break;
    }

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
	case 2:
		appliquerImage(x, y, pirate.imagePerdant, jeu.ecran);
		break;
    }
    lireDonnes(pirate);
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

	//bas
    if (pirate.y / 61 < jeu.ySouris / 61 && pirate.x / 61 == jeu.xSouris / 61)
    {
        pirate.bas = true;
        pirate.haut = false;
        pirate.gauche = false;
        pirate.droite = false;
    }
	//haut
    else if (pirate.y / 61 > jeu.ySouris / 61 && pirate.x / 61 == jeu.xSouris / 61)
    {
        pirate.bas = false;
        pirate.haut = true;
        pirate.gauche = false;
        pirate.droite = false;
    }
	//droite
    else if (pirate.x / 61 < jeu.xSouris / 61 && pirate.y / 61 == jeu.ySouris / 61)
    {
        pirate.bas = false;
        pirate.haut = false;
        pirate.droite = true;
        pirate.gauche = false;
    }
	//gauche
    else if (pirate.x / 61 > jeu.xSouris / 61 && pirate.y / 61 == jeu.ySouris / 61)
    {
        pirate.bas = false;
        pirate.haut = false;
        pirate.droite = false;
        pirate.gauche = true;
    }
}

void sauvegarder(Joueur &premier, Joueur &deuxieme,  int numeroPirate)
{

    fstream f;
    f.open("scores.txt", ios :: out | ios :: app );
    if( f.fail() )
    {
        cerr << "ouverture en ecriture impossible" << endl;
    }

    switch(numeroPirate)
    {
    case 0:
        f << "1 " << premier.tour << " " << 500-deuxieme.score << " " ;
        break;

    case 1:
        f << "2 " << deuxieme.tour << " " << 500-premier.score << " " ;
        break;

    case 2:
        f << "3 " << deuxieme.tour << " " << 500-premier.score << " " ;
        break;
    }
    f.close();
}

void lireDonnes(Joueur &pirates)
{
    int parties=0;
    int donnes=0;

    int meilleurTour=0;
    int meilleurDiff=0;

    int tmp=0;

    int occurence ;
    int y ;

    fstream f;
    f.open("scores.txt" , ios::in );
    if( f.fail() )
    {
        cerr << "ouverture en lecture impossible" << endl;
    }

    while( !f.eof() )
    {
        f >> pirates.tabScores[parties][donnes];
        donnes++;
        if(donnes==3)
        {
            parties++;
            donnes=0;
        }
    }

    f.close();

    meilleurTour = pirates.tabScores[0][1];
    meilleurDiff = pirates.tabScores[0][2];

    pirates.nbParties = parties ;

    for(int k=0; k<parties; k++)
    {
        if(pirates.tabScores[k][1] < meilleurTour)
        {
            meilleurTour = pirates.tabScores[k][1] ;
        }

        if(pirates.tabScores[k][2] > meilleurDiff)
        {
            meilleurDiff = pirates.tabScores[k][2] ;
        }
        if(pirates.tabScores[k][0] == 3 )
        {
            pirates.nbVictoireIA++;
        }
    }

    //on trie une première fois le tableau
    for(int i=0; i<parties ; i++)
    {
        for(int j=i; j<parties; j++)
        {
            //trie du nombre de tour
            if(pirates.tabScores[j][1]<pirates.tabScores[i][1])
            {
                tmp=pirates.tabScores[i][1];
                pirates.tabScores[i][1]=pirates.tabScores[j][1];
                pirates.tabScores[j][1]=tmp;
            }
        }
    }
    //on remplace les occurences par un nombre suffisament grand : 100
    for (int z = 0; z < parties ; z++)
    {
        occurence = pirates.tabScores[z][1] ;
        y = z+1 ;
        while(pirates.tabScores[z][1]==pirates.tabScores[y][1])
        {
            if(pirates.tabScores[z][1]=pirates.tabScores[z][1])
            {
               pirates.tabScores[y][1] = 100;
               y++;
            }
        }
    }
    //on retrie le tableau
    for(int i=0; i<parties ; i++)
    {
        for(int j=i; j<parties; j++)
        {
            //trie du nombre de tour
            if(pirates.tabScores[j][1]<pirates.tabScores[i][1])
            {
                tmp=pirates.tabScores[i][1];
                pirates.tabScores[i][1]=pirates.tabScores[j][1];
                pirates.tabScores[j][1]=tmp;
            }
        }
    }

    for(int i=0; i<parties; i++)
    {
        for(int j=i+1; j<parties; j++)
        {
            //trie du nombre de tour
            if(pirates.tabScores[j][2]>pirates.tabScores[i][2])
            {
                tmp=pirates.tabScores[j][2];
                pirates.tabScores[j][2]=pirates.tabScores[i][2];
                pirates.tabScores[i][2]=tmp;
            }
        }
    }
    for (int z = 0; z < parties ; z++)
    {
        occurence = pirates.tabScores[z][2] ;
        y = z+1 ;
        while(pirates.tabScores[z][2]==pirates.tabScores[y][2])
        {
            if(pirates.tabScores[z][2]=pirates.tabScores[z][2])
            {
               pirates.tabScores[y][2] = -1;
               y++;
            }
        }
    }
    for(int i=0; i<parties; i++)
    {
        for(int j=i+1; j<parties; j++)
        {
            //trie du nombre de tour
            if(pirates.tabScores[j][2]>pirates.tabScores[i][2])
            {
                tmp=pirates.tabScores[j][2];
                pirates.tabScores[j][2]=pirates.tabScores[i][2];
                pirates.tabScores[i][2]=tmp;
            }
        }
    }
}