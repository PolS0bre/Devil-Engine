#include "FireUp.h"

FireUp::FireUp(int X, int Y)
{
	PowerUp_ID = 0;
	ImageID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/PowersSheet.png");
	beenPicked = false;
	States = NOT_PICKED;
	ProjectRect = { X, Y, 32, 32 };
	Collision = ProjectRect;
	Size = { PowerUp_ID * 32, 0, 32, 32 };
}

FireUp::~FireUp()
{
}

void FireUp::update()
{
}

void FireUp::render()
{
	Video::getInstace()->renderGraphic(ImageID, ProjectRect, Size, 0, NULL, SDL_FLIP_NONE);
}

void FireUp::changeAnimFrame()
{
}

void FireUp::setPosition(int X, int Y)
{
}

void FireUp::changeDirection()
{
}

bool FireUp::compareID(int ID1, int ID2)
{
	return false;
}

void FireUp::setID(int ID1, int ID2)
{
}

void FireUp::GetHit()
{
}

