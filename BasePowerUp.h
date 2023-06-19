#pragma once
#include "BaseObject.h"
#include "ResourceManager.h"
class BasePowerUp :public BaseObject
{
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void changeAnimFrame() = 0;
	virtual void setPosition(int X, int Y) = 0;
	virtual void changeDirection() = 0;
	virtual void GetHit() = 0;
	virtual void setEnded() = 0;
	virtual bool compareID(int ID1, int ID2) = 0;
	virtual void setID(int ID1, int ID2) = 0;
	virtual int getType() = 0;
	virtual bool hasEnded() = 0;
};

