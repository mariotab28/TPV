#pragma once

#include "Texture.h"
#include "Vector2D.h"
//#include "Game.h"

typedef unsigned int uint;

class Game; //Evita problemas de dependencia circular

class Ball {
private:
	Vector2D pos = Vector2D(0, 0);
	uint w = 0; uint h = 0;
	Vector2D dir = Vector2D(0, 0);
	double speed = 0;
	Texture* texture;
	Game* game;

public:
	//Constructora
	Ball() {}
	Ball(double x, double y, uint w, uint h, double dirX, double dirY, uint spd, Texture* t, Game* g) :
		pos(x, y), w(w), h(h), dir(dirX, dirY), speed(spd), texture(t), game(g) {}

	//Destructora
	~Ball() {}

	//Métodos
	void render() const; //render
	void update();
	void handleEvents(SDL_Event& event);
};