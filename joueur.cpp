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


    int x2 = jeu.xSouris / deuxieme.LARGEUR_IMAGE;
    int y2 = jeu.ySouris / deuxieme.HAUTEUR_IMAGE;

    int maximum = 10;
    int xia = 3 ;
    int yia = 3 ;

    int xmax = 3 ;
    int ymax= 3 ;

    int alternative = 5;
    int xaltern1 =3;
    int yaltern1 =3;
    int xaltern2 =3;
    int yaltern2 =3;

    /*****
    Un exemple :
    si la souris a cliqué en 287, x1vaudra 287/61 = 4

    De plus, que l'on mette premier.LARG... ou deuxieme.LARG,
    cela revient au même car ces constances sont contenu
    dans la structure Joueur
    *****/

    //si on clique sur la zone de la grille
    if (jeu.xSouris >= 0 && jeu.xSouris <= 427 && jeu.ySouris >= 0 && jeu.ySouris <= 427)
    {
        //si le joueur 1 clique sur une case non vide horizontale ou verticale à sa position, on le déplace
        if (((x1 == premier.xMatrice) || (y1 == premier.yMatrice)) && (numeroPirate == 0) && (plateau.matrice[y1][x1].valeur != 0))
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
            if (jeu.duo)
            {
                //on envoie sur le joueur 2 si on a choisit de jouer contre lui
                numeroPirate = 1;
            }
            else if (jeu.solo)
            {
                //sinon on envoie sur l'ia
                numeroPirate = 2;
            }
        }

        //si le joueur 2 clique sur une case non vide horizontale ou verticale à sa position, on le déplace
        else if (((x2 == deuxieme.xMatrice) || (y2 == deuxieme.yMatrice)) && (numeroPirate == 1) && (plateau.matrice[y2][x2].valeur != 0))
        {
            //pareil que précédemment
            deuxieme.xMatrice = x2;
            deuxieme.yMatrice = y2;

            score(premier, deuxieme, jeu, plateau, numeroPirate);

            plateau.matrice[y2][x2].valeur = 0;


            premier.xMatrice = deuxieme.xMatrice;
            premier.yMatrice = deuxieme.yMatrice;

            numeroPirate = 0;
        }


        //déplacement de l'ia
        else if (numeroPirate == 2)
        {
            //on teste la ligne sur laquelle est arrivé le joueur 1
            for(int i=0; i<7; i++)
            {
                //on cherche la valeur max de la ligne
                if(plateau.matrice[i][deuxieme.xMatrice].valeur>maximum)
                {
                    //et si elle existe on prend sa valeur et ses coordonnées
                    maximum = plateau.matrice[i][deuxieme.xMatrice].valeur;
                    ymax = i;
                    xmax = deuxieme.xMatrice;
                }

                //et si la case précedente st plus grand on prend ses caractéristiques
                else if(((plateau.matrice[i][deuxieme.xMatrice].valeur == deuxieme.last) || (plateau.matrice[i][deuxieme.xMatrice].valeur >= alternative))
                        && (xia!=xaltern1) && (yia != yaltern1) && (xia!=xaltern2) && (yia != yaltern2))
                {
                    if(plateau.matrice[i][deuxieme.xMatrice].valeur>alternative)
                    {
                        plateau.matrice[i][deuxieme.xMatrice].valeur = alternative;
                        yaltern1 = i;
                        xaltern1 = deuxieme.xMatrice;
                    }
                    if(plateau.matrice[i][deuxieme.xMatrice].valeur == deuxieme.last)
                    {
                        yaltern2 = i;
                        xaltern2 = deuxieme.xMatrice;
                    }
                }
            }

            //maintenant on test la colonne sur laquelle le joueur 1 est arrivé
            for(int i=0; i<7; i++)
            {
                //les tests sont les mêmes que précédemment
                if(plateau.matrice[deuxieme.yMatrice][i].valeur>maximum)
                {
                    maximum=plateau.matrice[deuxieme.yMatrice][i].valeur;
                    xmax = i;
                    ymax = deuxieme.yMatrice;
                    //au dessus on dit que le le maximum est présent sur la colonne
                }

                else if(((plateau.matrice[deuxieme.yMatrice][i].valeur == deuxieme.last) || (plateau.matrice[deuxieme.yMatrice][i].valeur>=alternative))
                        && (xia!=xaltern1) && (yia != yaltern1) && (xia!=xaltern2) && (yia != yaltern2) )
                {
                    if (plateau.matrice[deuxieme.yMatrice][i].valeur > alternative)
                    {
                        alternative = plateau.matrice[deuxieme.yMatrice][i].valeur;
                        xaltern1 = i;
                        yaltern1 = deuxieme.yMatrice;
                    }
                    if (plateau.matrice[deuxieme.yMatrice][i].valeur == deuxieme.last)
                    {
                        xaltern2 = i;
                        yaltern2 = deuxieme.yMatrice;
                    }
                }
            }

            if(plateau.matrice[ymax][xmax].valeur >= maximum)
            {
                //on a fait les mêmes vérifications qu'avant
                yia=yaltern1;
                xia=xaltern1;
            }

            if(plateau.matrice[yaltern1][yaltern1].valeur >= maximum)
            {
                //on a fait les mêmes vérifications qu'avant
                yia=yaltern2;
                xia=xaltern2;
            }

            else
            {
                yia = ymax;
                xia = xmax;
            }


            //on donne les coordonnées finlaes à l'ia
            deuxieme.xMatrice = xia;
            deuxieme.yMatrice = yia;

            score(premier, deuxieme, jeu, plateau, numeroPirate);

            plateau.matrice[yia][xia].valeur = 0;

            premier.xMatrice = deuxieme.xMatrice;
            premier.yMatrice = deuxieme.yMatrice;

            numeroPirate = 0;
        }
    }
}


void score(Joueur &premier, Joueur &deuxieme, Gestion &jeu, Plateau &plateau, int numJoueur)
{

    int x, y;

    //gestion des scores en fonction du joueur en cours
    switch(numJoueur)
    {
    case 0:
        x = premier.xMatrice;
        y = premier.yMatrice;
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
        victoire(premier, deuxieme,  jeu, plateau, numJoueur);
        break;

    //on reprend le même code si on joue à deux
    case 1:

        x = deuxieme.xMatrice;
        y = deuxieme.yMatrice;

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

        victoire(premier, deuxieme,  jeu, plateau, numJoueur);
        break;

    //si on joue contre l'ia
    case 2:

        x = deuxieme.xMatrice;
        y = deuxieme.yMatrice;

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
    if((numJoueur==0) && ((premier.score>=500) || (nbZero==12)))
    {
        //encore pleins de fonction à appliquer
        SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
        afficheGagnant(premier, jeu, 240, 13, 0);
        SDL_Flip(jeu.ecran);
        SDL_Delay(2000);
        jeu.quit = true;
        //jeu.menu = true;
    }

    //pour le joueur 2, si son score est supérieur à 500 ou que le joueur 1 ne peut plus bouger
    if((numJoueur==1) && ((deuxieme.score>=500) || (nbZero==12)))
    {
        SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
        afficheGagnant(deuxieme, jeu, 240, 13, 1);
        SDL_Flip(jeu.ecran);
        SDL_Delay(2000);
        jeu.quit = true;
        //jeu.menu = true;
    }

    //pour l'ia, si son score est supérieur à 500 ou que le joueur 1 ne peut plus bouger
    if((numJoueur==2) && ((deuxieme.score>=500) || (nbZero==12)))
    {
        SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
        afficheGagnant(deuxieme, jeu, 240, 13, 1);
        SDL_Flip(jeu.ecran);
        SDL_Delay(2000);
        jeu.quit = true;
        //jeu.menu = true;
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
