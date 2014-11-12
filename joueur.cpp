#include "joueur.h"

using namespace std;

/******FONCTION D'INITIALISATION DU PIRATE******
  Prend en entrée
  -les deux joueurs
***********************************************/

void initPirate(Joueur &premier, Joueur &deuxieme)
{
    //initialisation des coordonnées du premier joueur
    premier.xMatrice = 3;
    premier.yMatrice = 3;

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
    switch(numeroPirate)
    {
    //si on doit afficher le joueur 1
    case 0:
        //position réelle à l'écran
        premier.x = premier.xMatrice * premier.LARGEUR_IMAGE;
        premier.y = premier.yMatrice * premier.HAUTEUR_IMAGE;

        //on applique tout ça à l'écran
        appliquerClip(premier.x, premier.y, premier.sprite, jeu.ecran, &premier.image[0]);
        break;

    //idem pour le joueur 2
    case 1:
        //position réelle à l'écran
        deuxieme.x = premier.xMatrice * premier.LARGEUR_IMAGE;
        deuxieme.y = premier.yMatrice * premier.HAUTEUR_IMAGE;
        appliquerClip(deuxieme.x, deuxieme.y, deuxieme.sprite, jeu.ecran, &deuxieme.image[1]);
        break;
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

        //on met à jour le score
        score(premier, deuxieme, jeu, plateau, numeroPirate);

        //on enlève la case
        plateau.matrice[y1][x1].valeur = 0;

        //on veut que l'autre joueur démarre d'où le joueur précédent à cliqué
        deuxieme.xMatrice = premier.xMatrice;
        deuxieme.yMatrice = premier.yMatrice;

        //on prévoit de changer de personnage
        numeroPirate = 1;

        //cout << "j1:" << premier.score << " j2:"<< deuxieme.score << endl ;
    }
    //si le joueur 2 clique sur une case non vide horizontale ou verticale à sa position, on le déplace
    else if(((x2 == deuxieme.xMatrice) || (y2 == deuxieme.yMatrice)) && (numeroPirate == 1) && (plateau.matrice[y2][x2].valeur != 0))
    {
        //pareil que précédemment
        deuxieme.xMatrice = x2;
        deuxieme.yMatrice = y2;

        score(premier, deuxieme, jeu, plateau, numeroPirate);

        plateau.matrice[y2][x2].valeur = 0;


        premier.xMatrice = deuxieme.xMatrice;
        premier.yMatrice = deuxieme.yMatrice;

        numeroPirate = 0;

        //cout << "j1:" << premier.score << " j2:"<< deuxieme.score << endl ;
    }
}

void score(Joueur &premier, Joueur &deuxieme, Gestion &jeu, Plateau &plateau, int numJoueur)
{

    int x = jeu.xSouris / premier.LARGEUR_IMAGE;
    int y = jeu.ySouris / premier.HAUTEUR_IMAGE;

    //gestion des scores en fonction du joueur en cours
    switch(numJoueur)
    {
    case 0:
        //son score = score précédent + valeur de la pièce
        premier.score += plateau.matrice[y][x].valeur;

        //si la case cliqué precédemment est la même que la case cliqué par la suite
        //et ceci 4 fois maximum
        //le bonus est multiplié par 2
        if((premier.last == plateau.matrice[y][x].valeur) && (premier.nbBonus < 4))
        {
            //cout << "le bonus est de " << premier.bonus << endl ;
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
        victoire(premier, deuxieme,  jeu, plateau, numJoueur);
        break;

    //on reprend le même code
    case 1:
        deuxieme.score += plateau.matrice[y][x].valeur;

        if((deuxieme.last == plateau.matrice[y][x].valeur ) && (deuxieme.nbBonus < 4))
        {
            //cout << "le bonus est de " << deuxieme.bonus << endl ;
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

        victoire(premier, deuxieme,  jeu, plateau, numJoueur);
        break;
    }
}

void victoire(Joueur &premier, Joueur &deuxieme, Gestion &jeu, Plateau &plateau, int numJoueur)
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
    if((numJoueur==0) && ((premier.score>500) || (nbZero==12)))
    {
        //encore pleins de fonction à appliquer
        cout << "Le joueur 1 a gagné ... " << endl ;
        jeu.quit = true ;
    }

    //pour le joueur 2, si son score est supérieur à 500 ou que le joueur 1 ne peut plus bouger
    if((numJoueur==1) && ((deuxieme.score>500) || (nbZero==12)))
    {
        cout << "Le joueur 2 a gagné ... " << endl ;
        jeu.quit = true ;
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
