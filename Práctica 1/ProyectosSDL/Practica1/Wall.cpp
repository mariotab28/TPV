#include "Wall.h"

void Wall::render() {
	SDL_Rect destRect;

	destRect.x = (int)pos.getX();
	destRect.y = (int)pos.getY();
	destRect.w = w;
	destRect.h = h;

	texture->render(destRect);
}













/*bool Wall::collides(const SDL_Rect& ballRect) {
	SDL_Rect wallRect = getRect();
	//SDL_Rect interRect; //Rect de intersección ball-wall

	if (SDL_IntersectRect(&ballRect, &wallRect, &interRect)) { //Comprueba si hay una intersección entre los dos Rect y la devuelve en interRect
		if (wallRect.y + wallRect.h < ballRect.y + ballRect.h) //Muro de ARRIBA
			collVector = { 0, 1 };
		else if (wallRect.x + wallRect.h / 2 < interRect.x) //Muro de la IZQUIERDA
			collVector = { 1, 0 };
		else //Muro de la DERECHA
			collVector = { -1,0 };

		return true;
	}
	return (SDL_HasIntersection(&ballRect, &wallRect)); //Comprueba si hay una intersección entre los dos Rect
	

}*/
