#include "main.h"
#include "gestion.h"

using namespace std;

int main(int argc, char* argv[])
{

	Gestion jeu;

	//initialise la sdl et creer l'encran plus le titre de la fenetre en parametre
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	jeu.ecran = SDL_SetVideoMode(jeu.LARGEUR_ECRAN, jeu.HAUTEUR_ECRAN, jeu.BPP_ECRAN, SDL_HWSURFACE | SDL_DOUBLEBUF);

	//creation du titre de la fenetre
	SDL_WM_SetCaption("SDL application", NULL);

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
		}
		//si on appuie sur une touche
		appuiTouche(jeu);

		maj(jeu);

		SDL_Delay(10);
	}

	//on supprime toutes les images
	SDL_FreeSurface(jeu.ecran);

	TTF_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}