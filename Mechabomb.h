#pragma once
#include "BaseEnemy.h"
#include "Player.h"
#include "Bomba.h"
#include "BaseObject.h"
#include "SceneManager.h"
#include "Video.h"
using namespace std;
class Mechabomb : public BaseEnemy
{
public:
	Mechabomb();
	~Mechabomb();

	void update();
	void render();
	void changeAnimFrame();
	void setPosition(int X, int Y);
	void changeDirection();
	bool compareID(int ID1, int ID2);
	bool hasEnded() { return isDead; };
	void setID(int ID1, int ID2);

	void GetHit();
	int getPunts() { return punts; };

private:
	int vidas, punts, ImageID, speed, AnimTimer, BombTimer;
	int x, y;
	bool isDead;
	Bomba* itselfBomb;
	BaseScene* myWorld;
	EnemyActions Enemy_States;
	SobreRect ProjectRect;
	Player* Player;
};

