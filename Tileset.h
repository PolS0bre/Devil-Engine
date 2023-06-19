#pragma once

#include <string>
#include <SDL.h>
#include "Video.h"

class Tileset
{
	int _firstID;	// primerID (firstgrid)
	int _tileWidth;	// tilewidth, tileheight
	int _tileHeight;

	//  Si tenim un Resource Manager això aniria allí
	std::string _filename; // nom del fitxer grafic associat
	SDL_Texture* _gfxTexture;

public:
	Tileset();
	~Tileset();
	int loadTileset(const char* filename);
	void setFirstID(int value) { _firstID = value; };
	void setTileWidth(int value) { _tileWidth = value; };
	void setTileHeight(int value) { _tileHeight = value; };

	int getTileWidth() { return _tileWidth; };
	int getTileHeight() { return _tileHeight; };

	//  Si tenim un Resource Manager això aniria allí
	SDL_Texture* getIMG() { return _gfxTexture; };
};
