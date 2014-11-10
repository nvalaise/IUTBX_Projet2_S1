#include "gestion.h"

using namespace std;

SDL_Surface* chargerImage(string nomFichier)
{
	//image charger non optimiser
	SDL_Surface* imageCharger = NULL;

	imageCharger = IMG_Load(nomFichier.c_str());

	if (imageCharger == NULL)
	{
		cout << "Can't open this file : " << nomFichier << endl;
	}
	
	return imageCharger;
}

SDL_Surface* chargerImageCleCouleur(string nomFichier, int rouge, int vert, int bleu)
{
	//image charger non optimiser
	SDL_Surface* imageCharger = NULL;

	imageCharger = IMG_Load(nomFichier.c_str());

	if (imageCharger != NULL)
	{
		//on optimise l'image charger
		Uint32 cleCouleur = SDL_MapRGB(imageCharger->format, rouge, vert, bleu);

		//charge l'image avec une cle couleur
		SDL_SetColorKey(imageCharger, SDL_RLEACCEL | SDL_SRCCOLORKEY, cleCouleur);
	}
	else
	{
		cout << "Can't open this file : " << nomFichier << endl;
	}

	return imageCharger;
}

void appliquerImage(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void appliquerClip(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
}

void afficheMot(string message, int x, int y, int taillePolice, Gestion &jeu, string nomPolice)
{
	SDL_Surface* mes = NULL;
	TTF_Font* police = NULL;
	SDL_Color couleurTexte = { 255, 255, 255 };
	police = TTF_OpenFont(nomPolice.c_str(), taillePolice);
	if (police != NULL)
	{
		mes = TTF_RenderText_Solid(police, message.c_str(), couleurTexte);
		appliquerImage(x, y, mes, jeu.ecran);
		SDL_FreeSurface(mes);
		TTF_CloseFont(police);
	}
	else
	{
		cout << "Can't open this file : " << nomPolice << endl;
	}
}

void appuiTouche(Gestion &jeu)
{
	if (jeu.kestates[SDLK_UP])
	{
		//si on appui sur la fleche du haut
	}
	if (jeu.kestates[SDLK_DOWN])
	{
		//si on appui sur la fleche du bas
	}
}