#include "piece.h"

using namespace std;

void cleanPiece(Piece &unePiece)
{
	SDL_FreeSurface(unePiece.sprite);
}