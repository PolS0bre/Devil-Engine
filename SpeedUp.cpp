#include "SpeedUp.h"

SpeedUp::SpeedUp(int X, int Y)
{
	PowerUp_ID = 2;
	ImageID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/PowersSheet.png");
	beenPicked = false;
	States = NOT_PICKED;
	ProjectRect = { X, Y, 32, 32 };
	Collision = ProjectRect;
	Size = { PowerUp_ID * 32, 0, 32, 32 };
}

SpeedUp::~SpeedUp()
{
}

void SpeedUp::update()
{
}

void SpeedUp::render()
{
	Video::getInstace()->renderGraphic(ImageID, ProjectRect, Size, 0, NULL, SDL_FLIP_NONE);
}

void SpeedUp::changeAnimFrame()
{
}

void SpeedUp::setPosition(int X, int Y)
{
}

void SpeedUp::changeDirection()
{
}

bool SpeedUp::compareID(int ID1, int ID2)
{
	return false;
}

void SpeedUp::setID(int ID1, int ID2)
{
}

void SpeedUp::GetHit()
{
}
