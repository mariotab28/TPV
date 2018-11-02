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
	Vector2D velocity = Vector2D(0, 0);
	Texture* texture;
	Game* game;

public:
	//Constructora
	Ball() {}
	Ball(double x, double y, uint w, uint h, Texture* t, Game* g) :
		pos(x, y), w(w), h(h), texture(t), game(g) {
		applySpeed();
	}

	//Destructora
	~Ball() {}

	//Métodos
	void render(); //render
	void update();
	SDL_Rect getDestRect(); //devuelve el Rectángulo de destino
	void applySpeed();
};