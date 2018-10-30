#include "Wall.h"

void Wall::render() const {
	SDL_Rect destRect;
	destRect.x = (int) pos.getX();
	destRect.y = (int) pos.getY();
	destRect.w = w;
	destRect.h = h;

	texture->render(destRect);
}

