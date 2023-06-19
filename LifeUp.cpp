#include "LifeUp.h"

LifeUp::LifeUp(int X, int Y)
{
	PowerUp_ID = 3;
	ImageID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/PowersSheet.png");
	beenPicked = false;
	States = NOT_PICKED;
	ProjectRect = { X, Y, 32, 32 };
	Collision = ProjectRect;
	Size = { PowerUp_ID * 32, 0, 32, 32 };
}

LifeUp::~LifeUp()
{
}

void LifeUp::update()
{
}

void LifeUp::render()
{
	Video::getInstace()->renderGraphic(ImageID, ProjectRect, Size, 0, NULL, SDL_FLIP_NONE);
}

void LifeUp::changeAnimFrame()
{
}

void LifeUp::setPosition(int X, int Y)
{
}

void LifeUp::changeDirection()
{
}

bool LifeUp::compareID(int ID1, int ID2)
{
	return false;
}

void LifeUp::setID(int ID1, int ID2)
{
}

void LifeUp::GetHit()
{
}
