#pragma once

#include "Texture.h"
#include "Block.h"
#include "Vector2D.h"

typedef unsigned int uint;

const string MAP_PATH = "..\\maps\\";

class BlocksMap {
private:
	Vector2D pos = Vector2D(0, 0);
	uint rows, cols;
	Block*** cells = nullptr; //se crea internamente con el método load()
	string filename;
	//dim. mapa
	uint mapW; uint mapH;
	//dim. blocks
	uint cellW; uint cellH;
	Texture* texture; //textura con los bloques
	uint numBlocks;

public:
	//Constructora
	BlocksMap() {}
	BlocksMap(double x, double y, string filename, uint mapW, uint mapH, Texture* t) :
		pos(Vector2D(x,y)), filename(filename), mapW(mapW), mapH(mapH), texture(t) {
		load(filename);
	}

	//Destructora
	~BlocksMap();

	//Métodos
	void render() const; //render
	void load(const string& filename); //cargarse de fichero
	int getNumBlocks();
	Block* blockAt(const Vector2D& p);
	Block* collides(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D& collVector);
	void ballHitsBlock(Block* block);
};