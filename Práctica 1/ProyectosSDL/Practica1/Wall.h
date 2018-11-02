#pragma once

#include "Texture.h"
#include "Vector2D.h"

typedef unsigned int uint;

class Wall {
private:
	Vector2D pos;// = Vector2D(0, 0); //Vector de posición x,y
	uint w = 0; uint h = 0;	//ancho y alto
	Texture* texture = nullptr;
	
public:
	//Constructora
	Wall() {}
	Wall(double x, double y, uint w, uint h, Texture* t) :
		pos(x,y), w(w), h(h), texture(t) {}

	//Destructora
	~Wall() {}

	//Métodos
	void render(); //render
	bool collides(const SDL_Rect& ballRect);
	SDL_Rect getRect();
};