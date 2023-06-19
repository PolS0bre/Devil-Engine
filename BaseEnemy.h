#pragma once
#include "BaseObject.h"
class BaseEnemy : public BaseObject
{
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void changeAnimFrame() = 0;
	virtual void setPosition(int X, int Y) = 0;
	virtual void changeDirection() = 0;
	virtual void GetHit() = 0;
	virtual bool compareID(int ID1, int ID2) = 0;
	virtual void setID(int ID1, int ID2) = 0;
	virtual int getPunts() = 0;
	virtual bool hasEnded() = 0;

protected:
	int vidas, punts, ImageID, speed, AnimTimer;
	int ID_1, ID_2;
	int x, y;
	EnemyActions Enemy_States;

};

