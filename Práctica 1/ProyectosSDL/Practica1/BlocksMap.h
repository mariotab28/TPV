#pragma once

#include "Texture.h"
#include "Block.h"
#include "Vector2D.h"

typedef unsigned int uint;

const string MAP_PATH = "..\\maps\\";

class BlocksMap {
private:

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
	BlocksMap( string filename, uint mapW, uint mapH, Texture* t) :
		 filename(filename), mapW(mapW), mapH(mapH), texture(t) {
		load(filename);
	}

	//Destructora
	~BlocksMap();

	//Métodos
	void render() const; //render
	void load(const string& filename); //cargarse de fichero
	int getNumBlocks();
	Block* getBlock(uint r, uint c);
	//Vector2D colVector();
};