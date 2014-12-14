#include "main.h"

#include "gestion.h"
#include "piece.h"
#include "plateau.h"
#include "joueur.h"

using namespace std;

int main(int argc, char* argv[])
{
    //déclaration des variables
    Gestion jeu;
    Piece unePiece;
    Plateau plateau;
    Joueur premier;
    Joueur deuxieme;

    //on pourra différencier les joueurs avec ce numéro
    //si numeroPirate=0 : c'est le joueur 1
    //si numeroPirate=1 : c'est le joueur 2 (lorqu'on joue à 2)
    //si numeroPirate=2 : c'est l'IA (lorsqu'on a choisit de jouer contre elle)
    int numeroPirate = 0;

    //on initialise les deux joueurs
    initPirate(premier, deuxieme);

    //on place les pièces sur la grille
    placementPiecesTableau(plateau, unePiece);

    //on déclare les images de "décor"
    SDL_Surface* menu = chargerImage("menu.png");
    SDL_Surface* score = chargerImage("score.jpg");
    SDL_Surface* bouton = chargerImageCleCouleur("bouton.png", 0, 255, 255);
    SDL_Rect imageBouton[8];

    //on déclare les différents boutons du menu
	for (int i = 0; i < 8; i++)
	{
		imageBouton[i].x = jeu.LARGEUR_BOUTON * i;
		imageBouton[i].y = 0;
		imageBouton[i].h = jeu.HAUTEUR_BOUTON;
		imageBouton[i].w = jeu.LARGEUR_BOUTON;
	}

    //on déclare les imags qui vont permettre d'activer le son ou non
	jeu.sonOn = chargerImage("haut_parleur_on.png");
	jeu.sonOff = chargerImage("haut_parleur_off.png");

    //initialise la sdl et creer l'encran plus le titre de la fenetre en parametre
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    jeu.ecran = SDL_SetVideoMode(jeu.LARGEUR_ECRAN, jeu.HAUTEUR_ECRAN, jeu.BPP_ECRAN, SDL_HWSURFACE | SDL_DOUBLEBUF);

    //creation du titre de la fenetre
    SDL_WM_SetCaption("Treasure Hunt", NULL);

    //Initialisation de l'API Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		cout <<Mix_GetError() << endl;
	}
	Mix_AllocateChannels(10);

    //déclaration des différents sons joués
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

            //si on clic...
            if (jeu.event.type == SDL_MOUSEBUTTONDOWN)
            {
                //...avec le clic gauche
                if (jeu.event.button.button == SDL_BUTTON_LEFT)
                {
                    //on récupère les coordonnées de la souris
                    jeu.xSouris=(jeu.event.motion.x);
                    jeu.ySouris=(jeu.event.motion.y);
                }
            }
        }

        //si on se situe dans le menu
        if (jeu.menu)
        {
            //on affiche l'image de fond
            appliquerImage(0, 0, menu, jeu.ecran);
            //on affiche es boutons du menu
            appliquerClip(700, 100, bouton, jeu.ecran, &imageBouton[0]);
            appliquerClip(700, 150, bouton, jeu.ecran, &imageBouton[2]);
            appliquerClip(700, 200, bouton, jeu.ecran, &imageBouton[4]);
			appliquerClip(700, 250, bouton, jeu.ecran, &imageBouton[6]);

            //suivant l'endroit où se situe la souris on va afficher un autre bouton pour donner un effet
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

            //suivant l'endroit où l(on clique on entre dans une autre partie du jeu
			if (jeu.xSouris > 700 && jeu.xSouris < 700 + jeu.LARGEUR_BOUTON && jeu.ySouris > 100 && jeu.ySouris < 100 + jeu.HAUTEUR_BOUTON)
            {
                //ici pour jouer contre l'IA
				jeu.solo = true;
				jeu.duo = false;
				jeu.menu = false;
				jeu.quit = false;
                jeu.score = false;

            }
			else if (jeu.xSouris > 700 && jeu.xSouris < 700 + jeu.LARGEUR_BOUTON && jeu.ySouris > 150 && jeu.ySouris < 150 + jeu.HAUTEUR_BOUTON)
            {
                //ici pour jouer à deux
				jeu.solo = false;
				jeu.duo = true;
				jeu.menu = false;
				jeu.quit = false;
                jeu.score = false;

            }
			else if (jeu.xSouris > 700 && jeu.xSouris < 700 + jeu.LARGEUR_BOUTON && jeu.ySouris > 200 && jeu.ySouris < 200 + jeu.HAUTEUR_BOUTON)
            {
                //ici pour afficher les score
                jeu.solo = false;
                jeu.duo = false;
                jeu.menu = false;
                jeu.quit = false;
                jeu.score = true;
            }
			else if (jeu.xSouris > 700 && jeu.xSouris < 700 + jeu.LARGEUR_BOUTON && jeu.ySouris > 250 && jeu.ySouris < 250 + jeu.HAUTEUR_BOUTON)
			{
			    //ici pour quitter le jeu
				jeu.solo = false;
				jeu.duo = false;
				jeu.menu = false;
				jeu.quit = true;
                jeu.score = false;
			}

        }

        //si on a choisit de voir les scores
        else if(jeu.score)
        {
                //déclaration d'une variable de type Joueur pour récupérer les scores
                Joueur pirates;
                //on récupère les scores enregistrés dans le fichier
                lireDonnes(pirates);

                //on affiche l'image de fond
                appliquerImage(0, 0, score, jeu.ecran);

                //on affiche un bouton pour revenir au menu
                appliquerClip(700, 25, bouton, jeu.ecran, &imageBouton[6]);

                //si on le survol on affiche le bouton d'une autre couleur
                if (jeu.event.motion.x > 700 && jeu.event.motion.x < 700 + jeu.LARGEUR_BOUTON && jeu.event.motion.y > 25 && jeu.event.motion.y < 25 + jeu.HAUTEUR_BOUTON)
                {
                    appliquerClip(700, 25, bouton, jeu.ecran, &imageBouton[7]);
                }

                //et si on clic dessus on revient au menu
                else if (jeu.xSouris > 700 && jeu.xSouris < 700 + jeu.LARGEUR_BOUTON && jeu.ySouris > 25 && jeu.ySouris < 25 + jeu.HAUTEUR_BOUTON)
                {
                    jeu.solo = false;
                    jeu.duo = false;
                    jeu.menu = true;
                    jeu.quit = false;
                    jeu.score = false;
                }

                //affichage des scores
                afficheMot("Records", 300, 10, 30, jeu, "police.ttf");
                afficheMot("Tours joue", 55, 75, 15, jeu, "police.ttf");
                afficheMot("Difference score", 255, 75, 15, jeu, "police.ttf");
                afficheMot("Victoire de l'IA :", 520, 125, 15, jeu, "police.ttf");
                afficherScoreFinal(pirates, jeu, 700, 120, 0, 3 );
                afficheMot("Nombre de parties :", 520, 185, 15, jeu, "police.ttf");
                afficherScoreFinal(pirates, jeu, 743, 180, 0, 4 );
                //on retient les 5 meilleurs scores
                for(int i=0; i<5; i++)
                {
                        afficherScoreFinal(pirates, jeu, 100, i*50 + 125, i , 1);
                        afficherScoreFinal(pirates, jeu, 325, i*50 + 125, i , 2);
                }
        }

        //si on a choisit de jouer seul et que personne n'a gagné
		else if (jeu.solo && victoire(premier, jeu, plateau, unePiece, 0) == -1 && victoire(deuxieme, jeu, plateau, unePiece, 1) == -1)
        {
            //si on a choisit de mettre du son (vrai par défaut) on joue le son
			if (jeu.sonActive)
			{
				Mix_VolumeChunk(jeu.sonPiece, MIX_MAX_VOLUME / 2);
				Mix_VolumeChunk(jeu.sonNiveauTermine, MIX_MAX_VOLUME / 2);
				Mix_VolumeChunk(jeu.sonPieceCent, MIX_MAX_VOLUME / 2);
				Mix_VolumeChunk(jeu.sonResteCinquante, MIX_MAX_VOLUME / 2);
				Mix_VolumeChunk(jeu.sonPerdu, MIX_MAX_VOLUME / 2);
			}
			//sinon on le coupe
			else
			{
				Mix_VolumeChunk(jeu.sonPiece, 0);
				Mix_VolumeChunk(jeu.sonNiveauTermine, 0);
				Mix_VolumeChunk(jeu.sonPieceCent, 0);
				Mix_VolumeChunk(jeu.sonResteCinquante, 0);
				Mix_VolumeChunk(jeu.sonPerdu, 0);
			}

            //si on clique sur le bouton d'activation du son, on le désactive ou non
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

            //affichage des pièces
			afficherPiecePlateau(plateau, jeu);
			//affichage des bonus du joueur 1
			afficherBonus(jeu, plateau, 500, 150, premier.nbBonus);
			//affichage du score du joueur 1
			afficherScore(premier, jeu, 550, 100, 1);
			//affichage des bonus du joueur 2
			afficherBonus(jeu, plateau, 700, 150, deuxieme.nbBonus);
            //affichage des bonus du joueur 2
			afficherScore(deuxieme, jeu, 750, 100, 1);
			//on affiche les joueurs de face
			appliquerClip(535, 30, premier.sprite, jeu.ecran, &premier.image[1]);
			appliquerClip(735, 30, deuxieme.sprite, jeu.ecran, &deuxieme.image[5]);
			//on affiche la dernière pièce choisit par la joueur
            afficheMot("Last", 537, 350, 15, jeu, "police.ttf");
            afficheMot("Last", 737, 350, 15, jeu, "police.ttf");
            afficherScore(premier, jeu, 550, 380, 2);
            afficherScore(deuxieme, jeu, 750, 380 ,2);

            //si on a choisit de mettre le son on montre qu'il est activé
			if (jeu.sonActive)
			{
				appliquerImage(820, 10, jeu.sonOn, jeu.ecran);
			}
			//sinon on montre qu'il est coupé
			else
			{
				appliquerImage(820, 10, jeu.sonOff, jeu.ecran);
			}

            //tant que le joueur n'a pas fini de jouer
			if (!jeu.finTour)
			{
			    //si c'esst le joueur 1
				if (numeroPirate == 0)
				{
                    //on afiche son image
					afficherPirate(premier, jeu, numeroPirate, 1);
					//et on le déplace
					deplacerPirate(premier, numeroPirate, plateau, jeu, unePiece);
					//puis le joueur 2 prendra comme position les coordonnées de fin de tour
					deuxieme.x = jeu.xSouris / 61 * 61;
					deuxieme.y = jeu.ySouris / 61 * 61;
				}
                //idem pour le joueur 2
				else if (numeroPirate == 2)
				{
					afficherPirate(deuxieme, jeu, numeroPirate, 5);
					deplacerPirate(deuxieme, numeroPirate, plateau, jeu, unePiece);
					premier.x = deuxieme.x;
					premier.y = deuxieme.y;
				}
			}
			//si le tour est finit, on change de joueur avec leur numéro (ici joueur 1 et IA)
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
        //si on a choisit de jouer à deux et que personne n'a gagné
        else if (jeu.duo && victoire(premier, jeu, plateau, unePiece, 0) == -1 && victoire(deuxieme, jeu, plateau, unePiece, 1) == -1)
        {
            //pareil que précédemment pour le son
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

            //on affiche les mêmes images que si on jouer contre l'IA
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

            //affichage des joueurs comme précédemment
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
			//on change de joueur (ici joueur 1 et joueur 2)
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
        //si le joeuur 1 à gagné la boucle ci-dessus est arrêtée pour passer à celle-ci
		else if (victoire(premier, jeu, plateau, unePiece, numeroPirate) == 0)
		{
		    //on affiche un fond noir
			SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 0, 0, 0));
			//on affiche le gagnant
			afficheGagnant(premier, jeu, 240, 13, 0);

            //on affiche les scores de la partie (qui vont être aussi enregistrés)
            afficheMot("Difference", 50, 200, 15, jeu, "police.ttf");
            afficheMot("Tours", 750, 200, 15, jeu, "police.ttf");
            afficherScore(premier, jeu, 775, 225, 3);
            afficherScore(deuxieme, jeu, 55, 225, 4);

            //on sauvegarde les scores de la partie (nombre de point, nombre de tours et numéro du joueur)
            sauvegarder(premier, deuxieme, numeroPirate);

            //on met à jouer l'écran
			SDL_Flip(jeu.ecran);
			//on joue un son différent
			Mix_PlayChannel(1, jeu.sonNiveauTermine, 0);
			//on attend que le son soit finit (5 secondes)
			SDL_Delay(5000);

			//et on réinitialise les données si on veut rejouer une partie
			//joueur 1 qui va débuter
			numeroPirate = 0;
			//initialisation des joueurs
			initPirate(premier, deuxieme);
			//placement de nouvelles pièces
			placementPiecesTableau(plateau, unePiece);
			//nombre de tour à 0
			premier.tour=0;
            deuxieme.tour=0;
            //on revient au menu
			jeu.solo = false;
			jeu.duo = false;
			jeu.menu = true;
			jeu.finTour=false;
			jeu.sonBientotFin = true;
			jeu.nbZero = 0;
		}
        //sinon si le joueur 2 ou l'IA a gagné
		else if (victoire(deuxieme, jeu, plateau, unePiece, numeroPirate) == 1 || victoire(deuxieme, jeu, plateau, unePiece, numeroPirate) == 2)
		{
			SDL_FillRect(jeu.ecran, NULL, SDL_MapRGB(jeu.ecran->format, 0, 0, 0));
			//si c'est le joueur 2 qui a gagné, une affiche une certaine image
			if (numeroPirate == 1)
			{
				afficheGagnant(deuxieme, jeu, 240, 13, 1);

			}
			//sinon si c'est l'IA qui a gagné, on en affiche une autre
			else if (numeroPirate == 2)
			{
				afficheGagnant(deuxieme, jeu, 240, 13, 2);

			}
            //on affiche les scores de la partie
            afficheMot("Difference", 50, 200, 15, jeu, "police.ttf");
            afficheMot("Tours", 750, 200, 15, jeu, "police.ttf");
            afficherScore(deuxieme, jeu, 775, 225, 3);
            afficherScore(premier, jeu, 55, 225, 5);

            //on les sauvegardent
            sauvegarder(premier, deuxieme, numeroPirate);
			SDL_Flip(jeu.ecran);

			//siivant si c'est l'IA ou e joueur 2 qui a gagné, on joue un son différent
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

			//puis on réintialise comme c'est expliqué au-dessus
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
		//on met à jour l'écran
		SDL_Flip(jeu.ecran);

        //temps d'attente entre les actions
		SDL_Delay(10);
    }

    //on sort de la boucle du jeu
    //il faut donc uitter le programme correcetement

    //on supprime toutes les images
    SDL_FreeSurface(jeu.ecran);
	SDL_FreeSurface(jeu.sonOn);
	SDL_FreeSurface(jeu.sonOff);

    //on libère toutes les surfaces
    cleanPiece(unePiece);
    cleanPirate(premier);
    cleanPirate(deuxieme);
    cleanBonus(plateau);
    cleanImageGagnant(premier);
    SDL_FreeSurface(menu);
	SDL_FreeSurface(bouton);

    //on libère les musique
	Mix_FreeChunk(jeu.sonPiece);
	Mix_FreeChunk(jeu.sonNiveauTermine);
	Mix_FreeChunk(jeu.sonPieceCent);
	Mix_FreeChunk(jeu.sonResteCinquante);
	Mix_FreeChunk(jeu.sonPerdu);

    //on ferme la SDL
	Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    //le jeu s'est bien fermé 8
    return EXIT_SUCCESS;
}
