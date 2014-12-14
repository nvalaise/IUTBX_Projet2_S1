#include "piece.h"

using namespace std;

void cleanPiece(Piece &unePiece)
{
    //fonction SDL qui permet de libérec une surface
	SDL_FreeSurface(unePiece.sprite);
}
