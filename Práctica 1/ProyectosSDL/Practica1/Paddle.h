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
	Vector2D dir = Vector2D(0, 0);
	double speed = 0;
	Texture* texture;

	bool keyboard[2] = { false,false };

public:
	//Constructora
	Paddle() {}
	Paddle(double x, double y, uint w, uint h, double dirX, double dirY, uint spd, Texture* t) :
		pos(x, y), w(w), h(h), dir(dirX, dirY), speed(spd), texture(t) {}

	//Destructora
	~Paddle() {}

	//Métodos
	void render() const; //render
	void update();
	void handleEvents(SDL_Event& event);
	//Vector2D collisionVector();
};