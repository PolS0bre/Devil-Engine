#pragma once
#include "BasePowerUp.h"
class FireUp :public BasePowerUp
{
public:
    FireUp(int X, int Y);
    ~FireUp();

    void update();
    void render();
    void changeAnimFrame();

    void setPosition(int X, int Y);
    void changeDirection();
    bool compareID(int ID1, int ID2);
    void setID(int ID1, int ID2);
    void GetHit();
    void setEnded() { beenPicked = true; };
    bool hasEnded() { return beenPicked; };
    int getType() { return PowerUp_ID; };
private:
    int PowerUp_ID, ImageID;
    PowerUpStates States;
    bool beenPicked;
    SobreRect ProjectRect;
};

