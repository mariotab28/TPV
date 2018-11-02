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

double Block::getX() {
	return pos.getX();
}

double Block::getY() {
	return pos.getY();
}

uint Block::getW() {
	return w;
}

uint Block::getH() {
	return h;
}

uint Block::getRow() {	//Devuelve la fila
	return row;
}

uint Block::getCol() {	//Devuelve la columna
	return col;
}