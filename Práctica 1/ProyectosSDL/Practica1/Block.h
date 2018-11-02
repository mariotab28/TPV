#pragma once

#include "Texture.h"
#include "Vector2D.h"

typedef unsigned int uint;

class Block {
private:
	Vector2D pos = Vector2D(0, 0); //Vector de posici�n x,y
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

	//M�todos
	void render() const; //render
	double getX();	//Devuelve la componente X de la posici�n
	double getY();	//Devuelve la componente Y de la posici�n
	uint getW();	//Devuelve el ancho
	uint getH();	//Devuelve el alto
	uint getRow();	//Devuelve la fila
	uint getCol();	//Devuelve la columna
};