#include "NutsStar.h"

NutsStar::NutsStar()
{
	vidas = 1;
	punts = 200;
	speed = 3;
	ImageID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/NutsStar.png");
	Enemy_States = MOVING;
	x = 0;
	y = 0;
	Size = { x, y, 32, 49 };
	ProjectRect = { 0, 0, 32, 49 };
	Collision = { x + 5, y + 16, 23, 23 };
	AnimTimer = 0;
	isDead = false;
}

NutsStar::~NutsStar()
{
}

void NutsStar::update()
{
	AnimTimer += Video::getInstace()->GetDeltaTime();
	if (AnimTimer >= 100)
	{
		switch (Enemy_States) {
		case MOVING:
			Size.y += speed;
			Collision.y = Size.y + 5;
			AnimTimer = 0;
			break;
		case DAMAGED:
			if (vidas == 0) {
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

void NutsStar::render()
{
	Video::getInstace()->renderGraphic(ImageID, Size, ProjectRect, 0, 0, SDL_FLIP_NONE);
}

void NutsStar::changeAnimFrame()
{
}

void NutsStar::setPosition(int X, int Y)
{
	x = X;
	y = Y;
	Size = { x, y, 32, 49 };
	Collision = { x + 5, y + 16, 23, 23 };
}

void NutsStar::changeDirection()
{
	speed = -speed;
}

bool NutsStar::compareID(int ID1, int ID2)
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

void NutsStar::setID(int ID1, int ID2)
{
	ID_1 = ID1;
	ID_2 = ID2;
}

void NutsStar::GetHit()
{
	if (Enemy_States != DAMAGED) {
		vidas--;
		Enemy_States = DAMAGED;
	}
}
