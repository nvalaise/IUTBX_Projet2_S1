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

    int numeroPirate = 0;

    initPirate(premier, deuxieme);
	//initBonus(plateau);

    //initialise la sdl et creer l'encran plus le titre de la fenetre en parametre
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    jeu.ecran = SDL_SetVideoMode(jeu.LARGEUR_ECRAN, jeu.HAUTEUR_ECRAN, jeu.BPP_ECRAN, SDL_HWSURFACE | SDL_DOUBLEBUF);

    //creation du titre de la fenetre
    SDL_WM_SetCaption("Treasure Hunt", NULL);

    placementPiecesTableau(plateau, unePiece);

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

        //affichage de l'ecran en blanc , supprime donc tout l'ecran
        SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 255, 255, 255));

        afficherPiecePlateau(plateau, jeu);
        afficherPirate(premier, deuxieme, jeu, numeroPirate);
        deplacerPirate(premier, deuxieme , plateau , jeu , numeroPirate);

		appliquerClip(535, 30, dessinPirate, jeu.ecran, &unDessinPirate[0]);
		appliquerClip(735, 30, dessinPirate, jeu.ecran, &unDessinPirate[1]);

		afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
		afficherScore(premier, jeu, 550, 100);
		
		afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
		afficherScore(deuxieme, jeu, 750, 100);
		

        SDL_Flip(jeu.ecran);

        SDL_Delay(10);
    }

    //on supprime toutes les images
    SDL_FreeSurface(jeu.ecran);

    cleanPiece(unePiece);
	cleanPirate(premier);
	cleanPirate(deuxieme);
	cleanBonus(plateau);
	SDL_FreeSurface(dessinPirate);

    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
