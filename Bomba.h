#pragma once
#include "BaseObject.h"
#include "BaseScene.h"
#include "Video.h"
#include "AudioManager.h"
enum BombStates {
	LOADING,
	EXPLODING,
	END
};

class Bomba : public BaseObject
{
public:
    Bomba(int X, int Y, int RadiSize);
    Bomba(int X, int Y, int RadiSize, BaseScene* thisWorld);
    ~Bomba();

    void update();
    void render();
    void changeAnimFrame();
    void setExplodeCol();
    void updateExplosion();
    void renderExplosions();
    void setWorldPointer(BaseScene* thisWorld) { MyWorld = thisWorld; };
    int ExplosionSize(int index) { return ExplosionDirections[index].size(); };
    SobreRect ExplosionRect(int index, int position) { return ExplosionDirections[index].at(position); }
    void setEnded() { ended = true; };
    bool hasEnded() { return ended; };
    int getPoints() { return Points; };

private:

    int ImageID, ExplodeID;
    int PointX, PointY;
    int Points;
    int x, y;
    int radiSize;
    int ImgFrame;
    int AnimRow;
    bool ended;
    float timerLoad, timerExplode; // Countdown timer in frames
    BaseScene* MyWorld;
    BombStates Phases;
    SobreRect ProjectRect;
    vector<SobreRect> ExplosionDirections[4];

};

