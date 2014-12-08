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

    SDL_Surface* menu = chargerImage("menu.png");
    SDL_Surface* score = chargerImage("score.jpg");
    SDL_Surface* bouton = chargerImageCleCouleur("bouton.png", 0, 255, 255);
    SDL_Rect imageBouton[8];

	for (int i = 0; i < 8; i++)
	{
		imageBouton[i].x = jeu.LARGEUR_BOUTON * i;
		imageBouton[i].y = 0;
		imageBouton[i].h = jeu.HAUTEUR_BOUTON;
		imageBouton[i].w = jeu.LARGEUR_BOUTON;
	}

	jeu.sonOn = chargerImage("haut_parleur_on.png");
	jeu.sonOff = chargerImage("haut_parleur_off.png");

    //initialise la sdl et creer l'encran plus le titre de la fenetre en parametre
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    jeu.ecran = SDL_SetVideoMode(jeu.LARGEUR_ECRAN, jeu.HAUTEUR_ECRAN, jeu.BPP_ECRAN, SDL_HWSURFACE | SDL_DOUBLEBUF);

    //creation du titre de la fenetre
    SDL_WM_SetCaption("Treasure Hunt", NULL);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
	{
		cout <<Mix_GetError() << endl;
	}
	Mix_AllocateChannels(10);

	jeu.sonPiece = Mix_LoadWAV("piece.wav");
	jeu.sonNiveauTermine = Mix_LoadWAV("niveau-termine.wav");
	jeu.sonPieceCent = Mix_LoadWAV("power-up.wav");
	jeu.sonResteCinquante = Mix_LoadWAV("hurry-up.wav");
	jeu.sonPerdu = Mix_LoadWAV("game-over.wav");

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
            appliquerClip(700, 100, bouton, jeu.ecran, &imageBouton[0]);
            appliquerClip(700, 150, bouton, jeu.ecran, &imageBouton[2]);
            appliquerClip(700, 200, bouton, jeu.ecran, &imageBouton[4]);
			appliquerClip(700, 250, bouton, jeu.ecran, &imageBouton[6]);

            if (jeu.event.motion.x > 700 && jeu.event.motion.x < 700 + jeu.LARGEUR_BOUTON && jeu.event.motion.y > 100 && jeu.event.motion.y < 100 + jeu.HAUTEUR_BOUTON)
			{
				appliquerClip(700, 100, bouton, jeu.ecran, &imageBouton[1]);
			}
			else if (jeu.event.motion.x > 700 && jeu.event.motion.x < 700 + jeu.LARGEUR_BOUTON && jeu.event.motion.y > 150 && jeu.event.motion.y < 150 + jeu.HAUTEUR_BOUTON)
			{
				appliquerClip(700, 150, bouton, jeu.ecran, &imageBouton[3]);
			}
			else if (jeu.event.motion.x > 700 && jeu.event.motion.x < 700 + jeu.LARGEUR_BOUTON && jeu.event.motion.y > 200 && jeu.event.motion.y < 200 + jeu.HAUTEUR_BOUTON)
			{
				appliquerClip(700, 200, bouton, jeu.ecran, &imageBouton[5]);
			}
			else if (jeu.event.motion.x > 700 && jeu.event.motion.x < 700 + jeu.LARGEUR_BOUTON && jeu.event.motion.y > 250 && jeu.event.motion.y < 250 + jeu.HAUTEUR_BOUTON)
			{
				appliquerClip(700, 250, bouton, jeu.ecran, &imageBouton[7]);
			}

			if (jeu.xSouris > 700 && jeu.xSouris < 700 + jeu.LARGEUR_BOUTON && jeu.ySouris > 100 && jeu.ySouris < 100 + jeu.HAUTEUR_BOUTON)
            {
				jeu.solo = true;
				jeu.duo = false;
				jeu.menu = false;
				jeu.quit = false;
                jeu.score = false;

            }
			else if (jeu.xSouris > 700 && jeu.xSouris < 700 + jeu.LARGEUR_BOUTON && jeu.ySouris > 150 && jeu.ySouris < 150 + jeu.HAUTEUR_BOUTON)
            {
				jeu.solo = false;
				jeu.duo = true;
				jeu.menu = false;
				jeu.quit = false;
                jeu.score = false;

            }
			else if (jeu.xSouris > 700 && jeu.xSouris < 700 + jeu.LARGEUR_BOUTON && jeu.ySouris > 200 && jeu.ySouris < 200 + jeu.HAUTEUR_BOUTON)
            {
                jeu.solo = false;
                jeu.duo = false;
                jeu.menu = false;
                jeu.quit = false;
                jeu.score = true;
            }
			else if (jeu.xSouris > 700 && jeu.xSouris < 700 + jeu.LARGEUR_BOUTON && jeu.ySouris > 250 && jeu.ySouris < 250 + jeu.HAUTEUR_BOUTON)
			{
				jeu.solo = false;
				jeu.duo = false;
				jeu.menu = false;
				jeu.quit = true;
                jeu.score = false;
			}

        }
        else if(jeu.score)
        {
                Joueur pirates;
                lireDonnes(pirates);

                appliquerImage(0, 0, score, jeu.ecran);
                appliquerClip(700, 25, bouton, jeu.ecran, &imageBouton[6]);
                if (jeu.event.motion.x > 700 && jeu.event.motion.x < 700 + jeu.LARGEUR_BOUTON && jeu.event.motion.y > 25 && jeu.event.motion.y < 25 + jeu.HAUTEUR_BOUTON)
                {
                    appliquerClip(700, 25, bouton, jeu.ecran, &imageBouton[7]);
                }

                else if (jeu.xSouris > 700 && jeu.xSouris < 700 + jeu.LARGEUR_BOUTON && jeu.ySouris > 25 && jeu.ySouris < 25 + jeu.HAUTEUR_BOUTON)
                {
                    jeu.solo = false;
                    jeu.duo = false;
                    jeu.menu = true;
                    jeu.quit = false;
                    jeu.score = false;
                }
                afficheMot("Records", 300, 10, 30, jeu, "police.ttf");
                afficheMot("Tours joue", 55, 75, 15, jeu, "police.ttf");
                afficheMot("Difference score", 255, 75, 15, jeu, "police.ttf");
                afficheMot("Victoire de l'IA :", 520, 125, 15, jeu, "police.ttf");
                afficherScoreFinal(pirates, jeu, 700, 120, 0, 3 );
                afficheMot("Nombre de parties :", 520, 185, 15, jeu, "police.ttf");
                afficherScoreFinal(pirates, jeu, 743, 180, 0, 4 );
                for(int i=0; i<5; i++)
                {
                        afficherScoreFinal(pirates, jeu, 100, i*50 + 125, i , 1);
                        afficherScoreFinal(pirates, jeu, 325, i*50 + 125, i , 2);
                }
        }
		else if (jeu.solo && victoire(premier, jeu, plateau, unePiece, 0) == -1 && victoire(deuxieme, jeu, plateau, unePiece, 1) == -1)
        {
			if (jeu.sonActive)
			{
				Mix_VolumeChunk(jeu.sonPiece, MIX_MAX_VOLUME / 2);
				Mix_VolumeChunk(jeu.sonNiveauTermine, MIX_MAX_VOLUME / 2);
				Mix_VolumeChunk(jeu.sonPieceCent, MIX_MAX_VOLUME / 2);
				Mix_VolumeChunk(jeu.sonResteCinquante, MIX_MAX_VOLUME / 2);
				Mix_VolumeChunk(jeu.sonPerdu, MIX_MAX_VOLUME / 2);
			}
			else
			{
				Mix_VolumeChunk(jeu.sonPiece, 0);
				Mix_VolumeChunk(jeu.sonNiveauTermine, 0);
				Mix_VolumeChunk(jeu.sonPieceCent, 0);
				Mix_VolumeChunk(jeu.sonResteCinquante, 0);
				Mix_VolumeChunk(jeu.sonPerdu, 0);
			}

			if (jeu.xSouris > 820 && jeu.xSouris < 870 && jeu.ySouris > 10 && jeu.ySouris < 60)
			{
				if (jeu.sonActive)
				{
					jeu.sonActive = false;
				}
				else
				{
					jeu.sonActive = true;
				}
				jeu.xSouris = 0;
				jeu.ySouris = 0;
			}
			//affichage de l'ecran en blanc , supprime donc tout l'ecran
			SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 0, 0, 0));

			afficherPiecePlateau(plateau, jeu);
			afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
			afficherScore(premier, jeu, 550, 100, 1);
			afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
			afficherScore(deuxieme, jeu, 750, 100, 1);
			appliquerClip(535, 30, premier.sprite, jeu.ecran, &premier.image[1]);
			appliquerClip(735, 30, deuxieme.sprite, jeu.ecran, &deuxieme.image[5]);
            afficheMot("Last", 537, 350, 15, jeu, "police.ttf");
            afficheMot("Last", 737, 350, 15, jeu, "police.ttf");
            afficherScore(premier, jeu, 550, 380, 2);
            afficherScore(deuxieme, jeu, 750, 380 ,2);


			if (jeu.sonActive)
			{
				appliquerImage(820, 10, jeu.sonOn, jeu.ecran);
			}
			else
			{
				appliquerImage(820, 10, jeu.sonOff, jeu.ecran);
			}


			if (!jeu.finTour)
			{
				if (numeroPirate == 0)
				{
					afficherPirate(premier, jeu, numeroPirate, 1);
					deplacerPirate(premier, numeroPirate, plateau, jeu, unePiece);
					deuxieme.x = jeu.xSouris / 61 * 61;
					deuxieme.y = jeu.ySouris / 61 * 61;
				}

				else if (numeroPirate == 2)
				{
					afficherPirate(deuxieme, jeu, numeroPirate, 5);
					deplacerPirate(deuxieme, numeroPirate, plateau, jeu, unePiece);
					premier.x = deuxieme.x;
					premier.y = deuxieme.y;
					//cout << "coordonnées attribués (au j1), " << premier.x << ":" << premier.y << endl;
				}
			}
			else
			{
				if (numeroPirate == 0)
				{
					numeroPirate = 2;
				}
				else
				{
					numeroPirate = 0;
				}
				jeu.finTour = false;
			}
        }
        else if (jeu.duo && victoire(premier, jeu, plateau, unePiece, 0) == -1 && victoire(deuxieme, jeu, plateau, unePiece, 1) == -1)
        {
			if (jeu.sonActive)
			{
				Mix_VolumeChunk(jeu.sonPiece, MIX_MAX_VOLUME / 2);
				Mix_VolumeChunk(jeu.sonNiveauTermine, MIX_MAX_VOLUME / 2);
				Mix_VolumeChunk(jeu.sonPieceCent, MIX_MAX_VOLUME / 2);
				Mix_VolumeChunk(jeu.sonResteCinquante, MIX_MAX_VOLUME / 2);
				Mix_VolumeChunk(jeu.sonPerdu, MIX_MAX_VOLUME / 2);
			}
			else
			{
				Mix_VolumeChunk(jeu.sonPiece, 0);
				Mix_VolumeChunk(jeu.sonNiveauTermine, 0);
				Mix_VolumeChunk(jeu.sonPieceCent, 0);
				Mix_VolumeChunk(jeu.sonResteCinquante, 0);
				Mix_VolumeChunk(jeu.sonPerdu, 0);
			}
			if (jeu.xSouris > 820 && jeu.xSouris < 870 && jeu.ySouris > 10 && jeu.ySouris < 60)
			{
				if (jeu.sonActive)
				{
					jeu.sonActive = false;
				}
				else
				{
					jeu.sonActive = true;
				}
				jeu.xSouris = 0;
				jeu.ySouris = 0;
			}

			//affichage de l'ecran en blanc , supprime donc tout l'ecran
			SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 0, 0, 0));

			afficherPiecePlateau(plateau, jeu);
			afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
			afficherScore(premier, jeu, 550, 100,1 );
			afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
			afficherScore(deuxieme, jeu, 750, 100, 1);
			appliquerClip(535, 30, premier.sprite, jeu.ecran, &premier.image[1]);
			appliquerClip(735, 30, deuxieme.sprite, jeu.ecran, &deuxieme.image[5]);
            afficheMot("Last", 537, 350, 15, jeu, "police.ttf");
            afficheMot("Last", 737, 350, 15, jeu, "police.ttf");
            afficherScore(premier, jeu, 550, 380, 2);
            afficherScore(deuxieme, jeu, 750, 380 ,2);

			if (jeu.sonActive)
			{
				appliquerImage(820, 10, jeu.sonOn, jeu.ecran);
			}
			else
			{
				appliquerImage(820, 10, jeu.sonOff, jeu.ecran);
			}

			if (!jeu.finTour)
			{
				if (numeroPirate == 0)
				{
					afficherPirate(premier, jeu, numeroPirate, 1);
					deplacerPirate(premier, numeroPirate, plateau, jeu, unePiece);
					deuxieme.x = jeu.xSouris / 61 * 61;
					deuxieme.y = jeu.ySouris / 61 * 61;
				}

				else if (numeroPirate == 1)
				{
					afficherPirate(deuxieme, jeu, numeroPirate, 1);
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
			SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 0, 0, 0));
			afficheGagnant(premier, jeu, 240, 13, 0);

            afficheMot("Difference", 50, 200, 15, jeu, "police.ttf");
            afficheMot("Tours", 750, 200, 15, jeu, "police.ttf");
            afficherScore(premier, jeu, 775, 225, 3);
            afficherScore(deuxieme, jeu, 55, 225, 4);


            sauvegarder(premier, deuxieme, numeroPirate);
			SDL_Flip(jeu.ecran);
			Mix_PlayChannel(1, jeu.sonNiveauTermine, 0);
			SDL_Delay(5000);
			numeroPirate = 0;
			initPirate(premier, deuxieme);
			placementPiecesTableau(plateau, unePiece);
			premier.tour=0;
            deuxieme.tour=0;
			jeu.solo = false;
			jeu.duo = false;
			jeu.menu = true;
			jeu.finTour=false;
			jeu.sonBientotFin = true;
			jeu.nbZero = 0;
		}
		else if (victoire(deuxieme, jeu, plateau, unePiece, numeroPirate) == 1 || victoire(deuxieme, jeu, plateau, unePiece, numeroPirate) == 2)
		{
			SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 0, 0, 0));
			if (numeroPirate == 1)
			{
				afficheGagnant(deuxieme, jeu, 240, 13, 1);

			}
			else if (numeroPirate == 2)
			{
				afficheGagnant(deuxieme, jeu, 240, 13, 2);

			}

            afficheMot("Difference", 50, 200, 15, jeu, "police.ttf");
            afficheMot("Tours", 750, 200, 15, jeu, "police.ttf");
            afficherScore(deuxieme, jeu, 775, 225, 3);
            afficherScore(premier, jeu, 55, 225, 5);



            sauvegarder(premier, deuxieme, numeroPirate);
			SDL_Flip(jeu.ecran);
			if (victoire(deuxieme, jeu, plateau, unePiece, numeroPirate) == 2)
			{
				Mix_PlayChannel(1, jeu.sonPerdu, 0);
				SDL_Delay(3000);
			}
			else
			{
				Mix_PlayChannel(1, jeu.sonNiveauTermine, 0);
				SDL_Delay(5000);
			}
			numeroPirate = 0;
			initPirate(premier, deuxieme);
			placementPiecesTableau(plateau, unePiece);
			jeu.solo = false;
			jeu.duo = false;
			jeu.menu = true;
            jeu.finTour=false;
			jeu.sonBientotFin = true;
			premier.tour=0;
            deuxieme.tour=0;
			jeu.nbZero = 0;
		}
		SDL_Flip(jeu.ecran);

		SDL_Delay(10);
    }

    //on supprime toutes les images
    SDL_FreeSurface(jeu.ecran);
	SDL_FreeSurface(jeu.sonOn);
	SDL_FreeSurface(jeu.sonOff);

    cleanPiece(unePiece);
    cleanPirate(premier);
    cleanPirate(deuxieme);
    cleanBonus(plateau);
    cleanImageGagnant(premier);
    SDL_FreeSurface(menu);
	SDL_FreeSurface(bouton);

	Mix_FreeChunk(jeu.sonPiece);
	Mix_FreeChunk(jeu.sonNiveauTermine);
	Mix_FreeChunk(jeu.sonPieceCent);
	Mix_FreeChunk(jeu.sonResteCinquante);
	Mix_FreeChunk(jeu.sonPerdu);

	Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
