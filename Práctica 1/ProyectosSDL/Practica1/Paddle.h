#pragma once

#include "Texture.h"
#include "Vector2D.h"

typedef unsigned int uint;

enum Movement {
	MovingLeft, MovingRight
};

class Paddle {
private:
	Vector2D pos = Vector2D(0, 0);
	uint w = 0; uint h = 0;
	Vector2D velocity = Vector2D(0, 0);
	Texture* texture;

	bool keyboard[2] = { false,false };

public:
	//Constructora
	Paddle() {}
	Paddle(double x, double y, uint w, uint h, Texture* t) :
		pos(x, y), w(w), h(h), texture(t) {}

	//Destructora
	~Paddle() {}

	//Métodos
	SDL_Rect getRect();
	void render(); //render
	void update();
	void handleEvents(SDL_Event& event);
	bool collides(SDL_Rect ballRect, const Vector2D& ballVel, Vector2D& collVector);
};