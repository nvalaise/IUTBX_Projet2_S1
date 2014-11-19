#include "main.h"

#include "gestion.h"
#include "piece.h"
#include "plateau.h"
#include "joueur.h"

using namespace std;

int main(int argc, char* argv[])
{

    Gestion jeu;
    Piece unePiece;
    Plateau plateau;
    Joueur premier;
    Joueur deuxieme;

    int numeroPirate = 0;
    initPirate(premier, deuxieme);
    placementPiecesTableau(plateau, unePiece);

    SDL_Surface* menu = chargerImage("menu.bmp");
    SDL_Surface* bouton = chargerImageCleCouleur("bouton.png", 0, 255, 255);
    SDL_Rect imageBouton[3];
    imageBouton[0].x = 0;
    imageBouton[0].y = 0;
    imageBouton[0].h = jeu.HAUTEUR_BOUTON;
    imageBouton[0].w = jeu.LARGEUR_BOUTON;

    imageBouton[1].x = jeu.LARGEUR_BOUTON;
    imageBouton[1].y = 0;
    imageBouton[1].h = jeu.HAUTEUR_BOUTON;
    imageBouton[1].w = jeu.LARGEUR_BOUTON;

    imageBouton[2].x = jeu.LARGEUR_BOUTON * 2;
    imageBouton[2].y = 0;
    imageBouton[2].h = jeu.HAUTEUR_BOUTON;
    imageBouton[2].w = jeu.LARGEUR_BOUTON;

    //initialise la sdl et creer l'encran plus le titre de la fenetre en parametre
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    jeu.ecran = SDL_SetVideoMode(jeu.LARGEUR_ECRAN, jeu.HAUTEUR_ECRAN, jeu.BPP_ECRAN, SDL_HWSURFACE | SDL_DOUBLEBUF);

    //creation du titre de la fenetre
    SDL_WM_SetCaption("Treasure Hunt", NULL);

    //tant qu'on est dans le jeu
    while (!jeu.quit)
    {
        //on recupere toutes les entrees
        while (SDL_PollEvent(&jeu.event))
        {
            //si on appuit sur la croix rouge
            if (jeu.event.type == SDL_QUIT)
            {
                //on quitte le jeu
                jeu.quit = true;
            }

            if (jeu.event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (jeu.event.button.button == SDL_BUTTON_LEFT)
                {
                    jeu.xSouris=(jeu.event.motion.x);
                    jeu.ySouris=(jeu.event.motion.y);
                }
            }
        }

        if (jeu.menu)
        {

            appliquerImage(0, 0, menu, jeu.ecran);
            appliquerClip(600, 100, bouton, jeu.ecran, &imageBouton[0]);
            appliquerClip(600, 200, bouton, jeu.ecran, &imageBouton[1]);
            appliquerClip(600, 300, bouton, jeu.ecran, &imageBouton[2]);

            if (jeu.xSouris > 600 && jeu.xSouris < 600 + jeu.LARGEUR_BOUTON && jeu.ySouris > 100 && jeu.ySouris < 100 + jeu.HAUTEUR_BOUTON)
            {
                jeu.menu = false;
                jeu.solo = true;
            }
            else if (jeu.xSouris > 600 && jeu.xSouris < 600 + jeu.LARGEUR_BOUTON && jeu.ySouris > 200 && jeu.ySouris < 200 + jeu.HAUTEUR_BOUTON)
            {

                jeu.menu = false;
                jeu.duo = true;
            }
            else if (jeu.xSouris > 600 && jeu.xSouris < 600 + jeu.LARGEUR_BOUTON && jeu.ySouris > 300 && jeu.ySouris < 300 + jeu.HAUTEUR_BOUTON)
            {
                jeu.solo = false;
                jeu.duo = false;
                jeu.menu = false;
                jeu.quit = true;
            }
        }
		else if (jeu.solo && victoire(premier, jeu, plateau, unePiece, 0) == -1 && victoire(deuxieme, jeu, plateau, unePiece, 1) == -1)
        {

			//affichage de l'ecran en blanc , supprime donc tout l'ecran
			SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));

			afficherPiecePlateau(plateau, jeu);
			afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
			afficherScore(premier, jeu, 550, 100);
			afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
			afficherScore(deuxieme, jeu, 750, 100);
			appliquerClip(535, 30, premier.sprite, jeu.ecran, &premier.image[0]);
			appliquerClip(735, 30, deuxieme.sprite, jeu.ecran, &deuxieme.image[1]);

			if (!jeu.finTour)
			{
				if (numeroPirate == 0)
				{
					afficherPirate(premier, jeu, numeroPirate);
					deplacerPirate(premier, numeroPirate, plateau, jeu, unePiece);
					deuxieme.x = jeu.xSouris / 61 * 61;
					deuxieme.y = jeu.ySouris / 61 * 61;
				}

				else if (numeroPirate == 1)
				{
					afficherPirate(deuxieme, jeu, numeroPirate);
					deplacerPirate(deuxieme, numeroPirate, plateau, jeu, unePiece);
					premier.x = jeu.xSouris / 61 * 61;
					premier.y = jeu.ySouris / 61 * 61;
				}
			}
			else
			{
				if (numeroPirate == 0)
				{
					numeroPirate = 1;
				}
				else
				{
					numeroPirate = 0;
				}
				jeu.finTour = false;
			}
        }

		else if (victoire(premier, jeu, plateau, unePiece, numeroPirate) == 0)
		{
			SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
			afficheGagnant(premier, jeu, 240, 13, 0);
            sauvegarder(premier, deuxieme, numeroPirate);
			SDL_Flip(jeu.ecran);
			SDL_Delay(2000);
			numeroPirate = 0;
			initPirate(premier, deuxieme);
			placementPiecesTableau(plateau, unePiece);
			premier.tour=0;
            deuxieme.tour=0;
			jeu.solo = false;
			jeu.duo = false;
			jeu.menu = true;
			jeu.nbZero = 0;
		}
		else if (victoire(deuxieme, jeu, plateau, unePiece, numeroPirate) == 1)
		{
			SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));
			afficheGagnant(deuxieme, jeu, 240, 13, 1);
            sauvegarder(premier, deuxieme, numeroPirate);
			SDL_Flip(jeu.ecran);
			SDL_Delay(2000);
			numeroPirate = 0;
			initPirate(premier, deuxieme);
			placementPiecesTableau(plateau, unePiece);
			jeu.solo = false;
			jeu.duo = false;
			jeu.menu = true;
			premier.tour=0;
            deuxieme.tour=0;
			jeu.nbZero = 0;
		}
		SDL_Flip(jeu.ecran);

		SDL_Delay(10);
    }

    //on supprime toutes les images
    SDL_FreeSurface(jeu.ecran);

    cleanPiece(unePiece);
    cleanPirate(premier);
    cleanPirate(deuxieme);
    cleanBonus(plateau);
    cleanImageGagnant(premier);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(bouton);

    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
