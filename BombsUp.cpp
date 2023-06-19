#include "BombsUp.h"

BombsUp::BombsUp(int X, int Y)
{
	PowerUp_ID = 1;
	ImageID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/PowersSheet.png");
	beenPicked = false;
	States = NOT_PICKED;
	ProjectRect = { X, Y, 32, 32 };
	Collision = ProjectRect;
	Size = { PowerUp_ID * 32, 0, 32, 32 };
}

BombsUp::~BombsUp()
{
}

void BombsUp::update()
{
}

void BombsUp::render()
{
	Video::getInstace()->renderGraphic(ImageID, ProjectRect, Size, 0, NULL, SDL_FLIP_NONE);
}

void BombsUp::changeAnimFrame()
{
}

void BombsUp::setPosition(int X, int Y)
{
}

void BombsUp::changeDirection()
{
}

bool BombsUp::compareID(int ID1, int ID2)
{
	return false;
}

void BombsUp::setID(int ID1, int ID2)
{
}

void BombsUp::GetHit()
{
}
