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
    if (numeroPirate == 0)
    {
        appliquerClip(pirate.x, pirate.y, pirate.sprite, jeu.ecran, &pirate.image[0]);
    }
    else if (numeroPirate == 1)
    {
        appliquerClip(pirate.x, pirate.y, pirate.sprite, jeu.ecran, &pirate.image[1]);
    }

    else if (numeroPirate == 2)
    {
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

    int xDepart = pirate.x/61;
    int yDepart = pirate.y/61;

    int maximum=0;

    //cout << "je commence ici : " << endl << xDepart << ":" << yDepart << endl ;

    const int VITESSE = 3;
    if((numeroPirate==0) || (numeroPirate==1))
    {
        if (jeu.xSouris >= 0 && jeu.xSouris <= 427 && jeu.ySouris >= 0 && jeu.ySouris <= 427
                && plateau.matrice[ySourisMatrice][xSourisMatrice].valeur != 0 && ((numeroPirate==0) || (numeroPirate==1)))
        {
            //cout << "test de la direction" << endl ;
            direction(pirate, jeu);
            if (pirate.bas)
            {
                score(pirate, xSourisMatrice, ySourisMatrice, jeu, plateau, unePiece);
                while (pirate.y < ySourisMatrice * 61)
                {
                    pirate.y += VITESSE;
                    afficherPiecePlateau(plateau, jeu);
                    afficherPirate(pirate, jeu, numeroPirate);
                    SDL_Flip(jeu.ecran);
                    jeu.finTour = false;
                }
                plateau.matrice[ySourisMatrice][xSourisMatrice].valeur = 0;
                jeu.finTour = true;
            }
            else if (pirate.haut)
            {
                score(pirate, xSourisMatrice, ySourisMatrice, jeu, plateau, unePiece);
                while (pirate.y > ySourisMatrice * 61)
                {
                    pirate.y -= VITESSE;
                    afficherPiecePlateau(plateau, jeu);
                    afficherPirate(pirate, jeu, numeroPirate);
                    SDL_Flip(jeu.ecran);
                    jeu.finTour = false;
                }
                plateau.matrice[ySourisMatrice][xSourisMatrice].valeur = 0;
                jeu.finTour = true;
            }
            else if (pirate.droite)
            {
                score(pirate, xSourisMatrice, ySourisMatrice, jeu, plateau, unePiece);
                while (pirate.x < xSourisMatrice * 61)
                {
                    pirate.x += VITESSE;
                    afficherPiecePlateau(plateau, jeu);
                    afficherPirate(pirate, jeu, numeroPirate);
                    SDL_Flip(jeu.ecran);
                    jeu.finTour = false;
                }
                plateau.matrice[ySourisMatrice][xSourisMatrice].valeur = 0;
                jeu.finTour = true;
            }
            else if (pirate.gauche)
            {
                score(pirate, xSourisMatrice, ySourisMatrice, jeu, plateau, unePiece);
                while (pirate.x > xSourisMatrice * 61)
                {
                    pirate.x -= VITESSE;
                    afficherPiecePlateau(plateau, jeu);
                    afficherPirate(pirate, jeu, numeroPirate);
                    SDL_Flip(jeu.ecran);
                    jeu.finTour = false;
                }
                plateau.matrice[ySourisMatrice][xSourisMatrice].valeur = 0;
                jeu.finTour = true;
            }
        }
    }
    else if(numeroPirate==2)
    {
        //les coordonnées de la matrice en entrée
        //initialisation des options
        int ymax, xmax;

        for(int i = 0; i<7; i++)
        {
            //on rehcerche le maximum
            if(plateau.matrice[i][xDepart].valeur > maximum)
            {
                maximum = plateau.matrice[xDepart][i].valeur;
                ymax = i;
                xmax = xDepart;
            }
            if(plateau.matrice[yDepart][i].valeur > maximum)
            {
                maximum = plateau.matrice[yDepart][i].valeur;
                ymax = yDepart;
                xmax = i;
            }
        }

        //ici, ymax et xmam contienne les coordonnées de la valeur max sur la ligne ou la colonne
        //cout << "départ        : " << pirate.x/61 << ":" << pirate.y/61 << endl ;
        //cout << "fin (maximum) : " << xmax << ":" << ymax << endl ;

        //directionIA(pirate, xDepart, yDepart, xmax, ymax);

        if (pirate.y/61 < ymax  && pirate.x/61 == xmax )
        {
            //cout << "vers bas" << endl ;
            score(pirate, xmax , ymax ,jeu,  plateau, unePiece);
            while (pirate.y < ymax * 61)
            {
                pirate.y += VITESSE;
                afficherPiecePlateau(plateau, jeu);
                afficherPirate(pirate, jeu, numeroPirate);
                SDL_Flip(jeu.ecran);
                jeu.finTour = false;
            }
            plateau.matrice[ymax][xmax].valeur = 0;;
            pirate.y = ymax * 61;
            jeu.finTour = true;
        }
        else if (pirate.y/61 > ymax  && pirate.x/61 == xmax )
        {
            //cout << "vers haut" << endl ;
            score(pirate, xmax , ymax ,jeu,  plateau, unePiece);
            while (pirate.y > ymax * 61)
            {
                pirate.y -= VITESSE;
                afficherPiecePlateau(plateau, jeu);
                afficherPirate(pirate, jeu, numeroPirate);
                SDL_Flip(jeu.ecran);
                jeu.finTour = false;
            }
            plateau.matrice[ymax][xmax].valeur = 0;;
            pirate.y = ymax * 61;
            jeu.finTour = true;
        }
        else if (pirate.x/61 < xmax  && pirate.y/61 == ymax )
        {
            //cout << "vers droite" << endl ;

            score(pirate, xmax , ymax ,jeu,  plateau, unePiece);
            while (pirate.x < xmax * 61)
            {
                pirate.x += VITESSE;
                afficherPiecePlateau(plateau, jeu);
                afficherPirate(pirate, jeu, numeroPirate);
                SDL_Flip(jeu.ecran);
                jeu.finTour = false;
            }
            plateau.matrice[ymax][xmax].valeur = 0;;
            pirate.x = xmax * 61;
            jeu.finTour = true;
        }
        else if (pirate.x/61 > xmax  && pirate.y/61 == ymax )
        {
            //cout << "vers gauche" << endl ;

            score(pirate, xmax , ymax ,jeu,  plateau, unePiece);
            while (pirate.x > xmax * 61)
            {
                pirate.x -= VITESSE;
                afficherPiecePlateau(plateau, jeu);
                afficherPirate(pirate, jeu, numeroPirate);
                SDL_Flip(jeu.ecran);
                jeu.finTour = false;
            }
            plateau.matrice[ymax][xmax].valeur = 0;;
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

    pirate.last = plateau.matrice[y][x].valeur;

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
    int playerOne =0;
    int playerTwo =0;
    int playerIA =0;
    int tmp=0;

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
/*
        if(pirates.tabScores[k][0] == 1 )
        {
            playerOne++;
        }

        if(pirates.tabScores[k][0] == 2 )
        {
            playerTwo++;
        }*/

        if(pirates.tabScores[k][0] == 3 )
        {
            playerIA++;
        }
    }



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


    for(int i=26; i!=0; i--)
    {
        for(int j=0; j<i; j++)
        {
            //trie de la différence
            if(pirates.tabScores[j][2]<pirates.tabScores[i+1][2])
            {
                tmp=pirates.tabScores[j][2];
                pirates.tabScores[j][2]=pirates.tabScores[j+1][2];
                pirates.tabScores[j+1][2]=tmp;
            }
        }
    }
    cout << "----- BEST SCORES -----" << endl ;
    cout << "Classement des parties les plus courtes" << endl ;
    for(int i=0; i<5; i++)
    {
        if(i<9)
        {
            cout << i+1 << ".  " << pirates.tabScores[i][1] << endl ;
        }
        else
        {
            cout << i+1 << ". " << pirates.tabScores[i][1] << endl ;
        }
    }

    cout << "Classement des plus grandes différences" << endl ;
    for(int i=0; i<5; i++)
    {
        if(i<9)
        {
            cout << i+1 << ".  " << pirates.tabScores[i][2] << endl ;
        }
        else
        {
            cout << i+1 << ". " << pirates.tabScores[i][2] << endl ;
        }
    }
    /*    cout << "Victoires en moins de tours : " << meilleurTour << endl ;
        cout << "Victoires avec le plus gros écart : " << meilleurDiff << endl;
        cout << "Nombre de victoires du joueur 1 : " << playerOne << endl ;
        cout << "Nombre de victoires du joueur 2 : " << playerTwo << endl ;
        cout << "Nombre de victoires de l'IA     : " << playerIA << endl << endl  ;*/
}

