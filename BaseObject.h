#pragma once
#include "sdl.h"
#include "sdl_image.h"
#include "Definicions.h"	
#include <string>
using namespace std;
class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	void setSize(SobreRect rectSize) { Size = rectSize; };
	void setCol(SobreRect colSize) { Collision = colSize; };

	SobreRect getSize() { return Size; };
	SobreRect getCollision() { return Collision; };

protected:
	SobreRect Size, Collision;
};

