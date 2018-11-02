#include "Ball.h"
#include "Game.h"

typedef unsigned int uint;

void Ball::applySpeed() {
	velocity = Vector2D(-5, -BALL_SPEED);
}

SDL_Rect Ball::getDestRect() {
	SDL_Rect destRect;

	destRect.x = (int)pos.getX();
	destRect.y = (int)pos.getY();
	destRect.w = w;
	destRect.h = h;

	return destRect;
}

void Ball::render() {
	SDL_Rect destRect = getDestRect();

	texture->render(destRect);
}

void Ball::update() {
	Vector2D prevPos = pos;
	pos = pos + velocity;

	SDL_Rect ballRect = getDestRect();
	Vector2D collVector;

	if (game->collides(ballRect, velocity, collVector))
		velocity = velocity - collVector * ((velocity * 2) * collVector);
}

