#pragma once
#include "BaseEnemy.h"
#include "Player.h"
#include "BaseObject.h"
#include "Video.h"
using namespace std;
class Puropen : public BaseEnemy
{
public:
	Puropen();
	~Puropen();

	void update();
	void render();
	void changeAnimFrame();
	void setPosition(int X, int Y);
	void changeDirection();
	bool compareID(int ID1, int ID2);
	bool hasEnded() { return isDead;};
	void setID(int ID1, int ID2);

	void GetHit();
	int getPunts() { return punts; };

private:
	int vidas, punts, ImageID, speed, AnimTimer;
	int x, y;
	bool isDead;
	EnemyActions Enemy_States;
	SobreRect ProjectRect;
	Player* Player;
};

