#include "Paddle.h"
#include "Texture.h"
#include "Game.h"

typedef unsigned int uint;

void Paddle::render() const {
	SDL_Rect destRect;
	destRect.x = (int)pos.getX();
	destRect.y = (int)pos.getY();
	destRect.w = w;
	destRect.h = h;

	texture->render(destRect);
}

void Paddle::update() {
	Vector2D mov;
	if (keyboard[MovingLeft]) //Movimiento Izquierda
		dir = Vector2D(-1, 0);
	else if (keyboard[MovingRight]) //Movimiento Derecha
		dir = Vector2D(1, 0);
	else if (keyboard[MovingRight] == false || keyboard[MovingLeft] == false)
		//Parar cuando no se mueve
		dir = Vector2D(0, 0);


	mov = pos + (dir * speed);//calcula la posición tras aplicar el movimiento

	//comprueba que no se sale de los límites
	if (mov.getX() > WALL_WIDTH && mov.getX() + w < WIN_WIDTH - WALL_WIDTH)
		pos = mov; //aplica el movimiento
}

void Paddle::handleEvents(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT)
			keyboard[MovingLeft] = true;
		else if (event.key.keysym.sym == SDLK_RIGHT)
			keyboard[MovingRight] = true;
	} else if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_LEFT)
			keyboard[MovingLeft] = false;
		else if (event.key.keysym.sym == SDLK_RIGHT)
			keyboard[MovingRight] = false;
	}
}