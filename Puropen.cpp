#include "Puropen.h"

Puropen::Puropen()
{
	vidas = 1;
	punts = 100;
	speed = 3;
	ImageID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/Puropen.png");
	Enemy_States = MOVING;
	x = 0;
	y = 0;
	Size = { x, y, 32, 49 };
	ProjectRect = { 0, 0, 32, 49 };
	Collision = { x + 5, y + 16, 23, 23 };
	AnimTimer = 0;
	isDead = false;
}

Puropen::~Puropen()
{
}

void Puropen::update()
{
	AnimTimer += Video::getInstace()->GetDeltaTime();
	if (AnimTimer >= 100)
	{
		switch (Enemy_States) {
		case MOVING:
			Size.x += speed;
			Collision.x = Size.x + 5;
			AnimTimer = 0;
			break;
		case DAMAGED:
			if(vidas == 0) {
				isDead = true;
			}
			AnimTimer += Video::getInstace()->GetDeltaTime();
			if (AnimTimer >= 3000)
			{
				Enemy_States = MOVING;
			}

			break;
		case DEAD:
			isDead = true;
			break;
		default:
			break;
		}
		
	}
}

void Puropen::render()
{
	Video::getInstace()->renderGraphic(ImageID, Size, ProjectRect, 0, 0, SDL_FLIP_NONE);
}

void Puropen::changeAnimFrame()
{
}

void Puropen::setPosition(int X, int Y)
{
	x = X;
	y = Y;
	Size = { x, y, 32, 49 };
	Collision = { x + 5, y + 16, 23, 23 };
}

void Puropen::changeDirection()
{
	speed = -speed;
}

bool Puropen::compareID(int ID1, int ID2)
{
	if (ID1 == ID_1) {
		return false;
	}

	if (ID2 == ID_2) {
		return false;
	}
	setID(ID1, ID2);
	return true;
}

void Puropen::setID(int ID1, int ID2)
{
	ID_1 = ID1;
	ID_2 = ID2;
}

void Puropen::GetHit()
{
	if (Enemy_States != DAMAGED) {
		vidas--;
		Enemy_States = DAMAGED;
	}
}
