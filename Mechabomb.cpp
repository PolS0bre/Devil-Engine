#include "Mechabomb.h"

Mechabomb::Mechabomb()
{
	vidas = 1;
	punts = 800;
	speed = 3;
	ImageID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/Mechabomb.png");
	Enemy_States = MOVING;
	x = 0;
	y = 0;
	Size = { x, y, 32, 49 };
	ProjectRect = { 0, 0, 32, 49 };
	Collision = { x + 5, y + 16, 23, 23 };
	AnimTimer = 0;
	BombTimer = 0;
	isDead = false;
}

Mechabomb::~Mechabomb()
{
}

void Mechabomb::update()
{
	AnimTimer += Video::getInstace()->GetDeltaTime();
	BombTimer += Video::getInstace()->GetDeltaTime();
	if (AnimTimer >= 100)
	{
		switch (Enemy_States) {
		case MOVING:
			Size.x += speed;
			Collision.x = Size.x + 5;
			AnimTimer = 0;
			if (BombTimer >= 4000) {
				BombTimer = 0;
				int X = (Collision.x / 32) * 32;
				int Y = (Collision.y / 32) * 32;
				myWorld = SceneManager::getInstance()->getCurrentScene();
				itselfBomb = new Bomba(X, Y, 3, myWorld);
				Enemy_States = ATTACK_ACTION;
			}
			break;
		case ATTACK_ACTION:
			itselfBomb->update();
			if (itselfBomb->hasEnded()) {
				BombTimer = 0;
				Enemy_States = MOVING;
			}
			break;
		case DAMAGED:
			if (vidas == 0) {
				isDead = true;
			}
			AnimTimer += Video::getInstace()->GetDeltaTime();
			if (AnimTimer >= 3000)
			{
				BombTimer = 0;
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

void Mechabomb::render()
{
	if (Enemy_States != ATTACK_ACTION) {
		Video::getInstace()->renderGraphic(ImageID, Size, ProjectRect, 0, 0, SDL_FLIP_NONE);
	}
	else {
		itselfBomb->render();
	}
}

void Mechabomb::changeAnimFrame()
{
}

void Mechabomb::setPosition(int X, int Y)
{
	x = X;
	y = Y;
	Size = { x, y, 32, 49 };
	Collision = { x + 5, y + 16, 23, 23 };
}

void Mechabomb::changeDirection()
{
	speed = -speed;
}

bool Mechabomb::compareID(int ID1, int ID2)
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

void Mechabomb::setID(int ID1, int ID2)
{
	ID_1 = ID1;
	ID_2 = ID2;
}

void Mechabomb::GetHit()
{
	if (Enemy_States != DAMAGED && Enemy_States != ATTACK_ACTION) {
		vidas--;
		Enemy_States = DAMAGED;
	}
}
