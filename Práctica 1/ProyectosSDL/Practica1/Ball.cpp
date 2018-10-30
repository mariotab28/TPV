#include "Ball.h"
#include "Game.h"

typedef unsigned int uint;

void Ball::render() const {
	SDL_Rect destRect;
	destRect.x = (int)pos.getX();
	destRect.y = (int)pos.getY();
	destRect.w = w;
	destRect.h = h;

	texture->render(destRect);
}

void Ball::update() {

}

void Ball::handleEvents(SDL_Event& event) {

}