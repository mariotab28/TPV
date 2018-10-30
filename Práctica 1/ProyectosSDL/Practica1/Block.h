#pragma once

#include "Texture.h"
#include "Vector2D.h"

typedef unsigned int uint;

class Block {
private:
	Vector2D pos = Vector2D(0, 0); //Vector de posición x,y
	uint w = 0; uint h = 0;	//ancho y alto
	uint color = 0; //frame de la textura (int) 0-5
	uint row = 0; uint col = 0; //fila y columna en BlocksMap
	Texture* texture = nullptr;

public:
	//Constructora
	Block() {}
	Block(double x, double y, uint w, uint h, uint row, uint col, uint color, Texture* t) :
		pos(x, y), w(w), h(h), row(row), col(col), color(color), texture(t) {}

	//Destructora
	~Block() {}

	//Métodos
	void render() const; //render
};