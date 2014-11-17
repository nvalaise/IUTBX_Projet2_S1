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

            /****** Prévision si on jeu revenir au menu après ********
            int numeroPirate = 0;
            initPirate(premier, deuxieme);
            placementPiecesTableau(plateau, unePiece);
            premier.score=0;
            premier.nbBonus=0;
            deuxieme.score=0;
            deuxieme.nbBonus=0;
            **********************************************************/

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

            SDL_Flip(jeu.ecran);
            SDL_Delay(10);


        }
        else if(jeu.solo)
        {
            //affichage de l'ecran en blanc , supprime donc tout l'ecran
            SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));

            afficherPiecePlateau(plateau, jeu);
			afficherPirate(premier, deuxieme, jeu, numeroPirate);
            deplacerPirate(premier, deuxieme, plateau, jeu, numeroPirate, unePiece);

			appliquerClip(535, 30, dessinPirate, jeu.ecran, &unDessinPirate[0]);
			appliquerClip(735, 30, dessinPirate, jeu.ecran, &unDessinPirate[1]);

			afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
			afficherScore(premier, jeu, 550, 100);

			afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
			afficherScore(deuxieme, jeu, 750, 100);

            SDL_Flip(jeu.ecran);

            SDL_Delay(10);
        }

        else if(jeu.duo)
        {
            //affichage de l'ecran en blanc , supprime donc tout l'ecran
            SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));

            afficherPiecePlateau(plateau, jeu);
            afficherPirate(premier, deuxieme, jeu, numeroPirate);
            deplacerPirate(premier, deuxieme, plateau, jeu, numeroPirate, unePiece);

            appliquerClip(535, 30, dessinPirate, jeu.ecran, &unDessinPirate[0]);
            appliquerClip(735, 30, dessinPirate, jeu.ecran, &unDessinPirate[1]);

            afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
            afficherScore(premier, jeu, 550, 100);

            afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
            afficherScore(deuxieme, jeu, 750, 100);

            SDL_Flip(jeu.ecran);

            SDL_Delay(10);
        }
    }

    //on supprime toutes les images
    SDL_FreeSurface(jeu.ecran);

    cleanPiece(unePiece);
    cleanPirate(premier);
    cleanPirate(deuxieme);
    cleanBonus(plateau);
    cleanImageGagnant(premier);
    SDL_FreeSurface(dessinPirate);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(bouton);

    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
