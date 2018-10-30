#include "Block.h"

void Block::render() const {
	SDL_Rect destRect;
	destRect.x = (int)pos.getX();
	destRect.y = (int)pos.getY();
	destRect.w = w;
	destRect.h = h;

	//fila y columna del frame
	uint row = color / texture->getNumCols();
	uint col = color % texture->getNumCols();
	texture->renderFrame(destRect, row, col);
}