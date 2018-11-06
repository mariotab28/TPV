#include "Paddle.h"
#include "Texture.h"
#include "Game.h"

typedef unsigned int uint;

SDL_Rect Paddle::getRect() {
	SDL_Rect destRect;

	destRect.x = (int)pos.getX();
	destRect.y = (int)pos.getY();
	destRect.w = w;
	destRect.h = h;

	return destRect;
}

void Paddle::render() {
	SDL_Rect destRect = getRect();

	texture->render(destRect);
}

void Paddle::update() {
	Vector2D mov = pos + velocity; //cálculo de la posición tras el movimiento

	//comprueba que hay movimiento y que no se sale de los límites
	if ((keyboard[MovingLeft] || keyboard[MovingRight]) && (mov.getX() > (WALL_WIDTH - WALL_OFFSET) && mov.getX() + w < WIN_WIDTH - (WALL_WIDTH - WALL_OFFSET)))
		pos = mov; //aplica el movimiento
}

void Paddle::handleEvents(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			keyboard[MovingLeft] = true;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT)
		{
			keyboard[MovingRight] = true;
		}
	}
	else if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_LEFT)
			keyboard[MovingLeft] = false;
		else if (event.key.keysym.sym == SDLK_RIGHT)
			keyboard[MovingRight] = false;
	}

	if(keyboard[MovingLeft])
		velocity = Vector2D(-PADDLE_SPEED, 0);

	if(keyboard[MovingRight])
		velocity = Vector2D(PADDLE_SPEED, 0);

	if((keyboard[MovingLeft] && keyboard[MovingRight]))
		velocity = Vector2D(0, 0);
}

bool Paddle::collides(SDL_Rect ballRect, const Vector2D& ballVel, Vector2D& collVector) {
	SDL_Rect paddleRect = getRect();
	SDL_Rect interRect;

	if (SDL_IntersectRect(&ballRect, &paddleRect, &interRect)) {
		//if (ballRect.y < paddleRect.y)
		Vector2D collVectorLeft = { -PERTURBATION, -PERTURBATION };
		Vector2D collVectorCenter = { 0, -1 };
		Vector2D collVectorRight = { PERTURBATION, -PERTURBATION };

		if (ballRect.y > paddleRect.y) {
			if (ballRect.x < paddleRect.x)
				collVector = { -1, 0 };
			else
				collVector = { 1, 0 };
		}
		else if (ballRect.x <= paddleRect.x + paddleRect.w / 3)	//Tercio izquierdo
			collVector = collVectorLeft;
		else if (ballRect.x > paddleRect.x + paddleRect.w / 3 && ballRect.x < paddleRect.x + paddleRect.w - paddleRect.w / 3) //centro
			collVector = { 0, -1 };
		else if(ballRect.x >= paddleRect.x + paddleRect.w - paddleRect.w / 3) //Tercio derecho
			collVector = collVectorRight;

		return true;
	}
	else
		return false;
	
	
	//return SDL_HasIntersection(&ballRect, &paddleRect);
}