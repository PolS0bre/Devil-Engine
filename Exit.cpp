#include "Exit.h"

Exit::Exit(int X, int Y)
{
	PowerUp_ID = 4;
	ImageID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/Exit.png");
	beenPicked = false;
	States = NOT_PICKED;
	ProjectRect = { X, Y, 32, 32 };
	Collision = ProjectRect;
	Size = { 0, 0, 32, 32 };
}

Exit::~Exit()
{
}

void Exit::update()
{
}

void Exit::render()
{
	Video::getInstace()->renderGraphic(ImageID, ProjectRect, Size, 0, NULL, SDL_FLIP_NONE);
}

void Exit::changeAnimFrame()
{
}

void Exit::setPosition(int X, int Y)
{
}

void Exit::changeDirection()
{
}

bool Exit::compareID(int ID1, int ID2)
{
	return false;
}

void Exit::setID(int ID1, int ID2)
{
}

void Exit::GetHit()
{
}
