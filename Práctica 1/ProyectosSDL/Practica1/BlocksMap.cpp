#include "BlocksMap.h"
#include "Game.h" //TEMPORAL
#include <fstream>

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
	if (!file.is_open())	throw "Error al abrir el archivo " + filename + ".";

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
			else
				cells[r][c] = new Block((double)cellW * c + WALL_WIDTH + WALL_OFFSET, (double)cellH * r + WALL_WIDTH + WALL_OFFSET, cellW, cellH, r, c, color - 1, texture);
			numBlocks++;
		}
	}
}

int BlocksMap::getNumBlocks() {
	return numBlocks;
}

Block* BlocksMap::getBlock(uint r, uint c) {
	return cells[r][c];
}