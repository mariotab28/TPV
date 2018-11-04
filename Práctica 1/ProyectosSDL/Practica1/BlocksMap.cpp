#include "BlocksMap.h"
#include <fstream>
#include <algorithm>

BlocksMap::~BlocksMap() {
	if (cells != nullptr) {
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				delete cells[r][c];
			}
			delete[] cells[r];
		}
		delete[] cells;
		cells = nullptr;
	}
}

void BlocksMap::render() const {
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (cells[r][c] != nullptr)
				cells[r][c]->render();
		}
	}
}


void BlocksMap::load(const string& filename) {
	ifstream file;

	file.open(MAP_PATH + filename);
	if (!file.is_open())	throw "Error al abrir el archivo " + filename + "\n";

	file >> rows >> cols; //lee el num. de filas y columnas desde el archivo
	cellW = mapW / cols; cellH = mapH / rows; //Calcula las dimensiones de cada celda según las del mapa y el número de fils/cols

	cells = new Block**[rows];
	uint color;
	for (int r = 0; r < rows; r++)
	{
		cells[r] = new Block*[cols];
		for (int c = 0; c < cols; c++)
		{
			file >> color;

			if (color == 0) //celda vacía
				cells[r][c] = nullptr;
			else {
				cells[r][c] = new Block((double)cellW * c + pos.getX(), (double)cellH * r + pos.getY(), cellW, cellH, r, c, color - 1, texture);
				numBlocks++;
			}
		}
	}
}

int BlocksMap::getNumBlocks() {
	return numBlocks;
}

/*Block* BlocksMap::getBlock(uint r, uint c) {
	return cells[r][c];
}*/

/* Dados el rectángulo y vector de dirección de la pelota, devuelve un puntero al
   bloque con el que ésta colisiona (nullptr si no colisiona con nadie) y el
   vector normal perpendicular a la superficie de colisión.
*/
Block* BlocksMap::collides(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D& collVector) {
	Vector2D p0 = { (double) ballRect.x, (double) ballRect.y }; // top-left
	Vector2D p1 = { (double) ballRect.x + (double) ballRect.w, (double) ballRect.y }; // top-right
	Vector2D p2 = { (double) ballRect.x,(double) ballRect.y + (double) ballRect.h }; // bottom-left
	Vector2D p3 = { (double) ballRect.x + (double) ballRect.w,(double) ballRect.y + (double) ballRect.h }; // bottom-right
	Block* b = nullptr;
	if (ballVel.getX() < 0 && ballVel.getY() < 0) {
		if ((b = blockAt(p0))) {
			if ((b->getY() + b->getH() - p0.getY()) <= (b->getX() + b->getW() - p0.getX()))
				collVector = { 0,1 }; // Borde inferior mas cerca de p0
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = blockAt(p1))) {
			collVector = { 0,1 };
		}
		else if ((b = blockAt(p2))) collVector = { 1,0 };
	}
	else if (ballVel.getX() >= 0 && ballVel.getY() < 0) {
		if ((b = blockAt(p1))) {
			if (((b->getY() + b->getH() - p1.getY()) <= (p1.getX() - b->getX())) || ballVel.getX() == 0)
				collVector = { 0,1 }; // Borde inferior mas cerca de p1
			else
				collVector = { -1,0 }; // Borde izqdo mas cerca de p1
		}
		else if ((b = blockAt(p0))) {
			collVector = { 0,1 };
		}
		else if ((b = blockAt(p3))) collVector = { -1,0 };
	}
	else if (ballVel.getX() > 0 && ballVel.getY() > 0) {
		if ((b = blockAt(p3))) {
			if (((p3.getY() - b->getY()) <= (p3.getX() - b->getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p3
			else
				collVector = { -1,0 }; // Borde dcho mas cerca de p3
		}
		else if ((b = blockAt(p2))) {
			collVector = { 0,-1 };
		}
		else if ((b = blockAt(p1))) collVector = { -1,0 };
	}
	else if (ballVel.getX() < 0 && ballVel.getY() > 0) {
		if ((b = blockAt(p2))) {
			if (((p2.getY() - b->getY()) <= (b->getX() + b->getW() - p2.getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p2
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = blockAt(p3))) {
			collVector = { 0,-1 };
		}
		else if ((b = blockAt(p0))) collVector = { 1,0 };
	}
	return b;
}


/*  Devuelve el puntero al bloque del mapa de bloques al que pertenece el punto p.
	En caso de no haber bloque en ese punto (incluido el caso de que p esté fuera
	del espacio del mapa) devuelve nullptr.
*/
Block* BlocksMap::blockAt(const Vector2D& p) {
	Block* block = nullptr;

	if (p.getY() <= pos.getY() + mapH && p.getY() >= pos.getY()) { //Comprueba que la pelota está dentro del espacio del mapa
		//Encuentra la columna y la fila del bloque
		uint row = p.getY() / cellH - 2;
		uint col = p.getX() / cellW;// -1;

		if (col >= cols)
			std::cout << "ups";
		block = cells[std::min(row, rows - 1)][std::min(col,cols - 1)];
	}
	return block;
}


/*
	bX = p.x - (p.x % (c*cellW));
	c = bX / cellW;
*/


//Recibe el bloque con el que ha colisionado la pelota y lo destruye en el mapa
void BlocksMap::ballHitsBlock(Block* block) {
	cells[block->getRow()][block->getCol()] = nullptr;
	numBlocks--;
}