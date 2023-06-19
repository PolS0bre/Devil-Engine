#include "Tileset.h"

#include <iostream>


extern SDL_Renderer* gRenderer;

Tileset::Tileset()
{
	_firstID = 0;
	_tileWidth = 0;
	_tileHeight = 0;

	//  Si tenim un Resource Manager aix� aniria all�
	_filename = "";
	_gfxTexture = nullptr;
}

Tileset::~Tileset()
{
}

int Tileset::loadTileset(const char* filename)
{
	// Aix� ho hauria de fer el Reosurce Manager
	_filename = filename;
	_gfxTexture = Video::getInstace()->LoadImage(filename);
	if (_gfxTexture == NULL) {
		std::cout << "Error loading Tileset: " << IMG_GetError();
		return 1;
	}
	return 0;
}
