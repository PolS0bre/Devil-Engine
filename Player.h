#pragma once
#include "BaseObject.h"
#include "Video.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "BaseScene.h"
#include "SceneManager.h"
#include "Bomba.h"

enum PlayerStates {
	IDLE,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	DIE
};

class Player : public BaseObject
{
public: 
	Player(bool isCont);
	void ChangeAnimationFrame();
	void ResetPlayer();
	void SetSpriteSize();
	void Render();
	void Update();
	int LimitScreen();
	void updateState(bool isController);
	void SetWorldPointer(BaseScene* map);
	void CheckCollisions();
	PlayerStates getPlayerState() { return Player_State; };
	int GetWorldX() { return World.x; };
	int GetWorldY() { return World.y; };
	int GetWorldW() { return World.w; };
	int GetWorldH() { return World.h; };
	void setCameraPositionX(int value) { CameraX = value; };
	int getScore() { return punts; };
	void PlantBomb();
	static Player* PlayerInstance();

private:
	//Stats
	int speedMove;
	int maxBombs, lives, punts, radiBomba;
	vector<Bomba*> ActualBombs;

	int ImgFrame;
	int AnimRow;
	int AnimTimer;
	int ImageID;
	bool isController, Dying;
	int Point1X, Point1Y;
	int Point2X, Point2Y;
	int Point3X, Point3Y;
	int _WorldSizeW, _WorldSizeH;
	int CollisionInt;
	int CameraX;
	BaseScene* MyWorld;
	PlayerStates Player_State;
	SobreRect ProjectRect, World;

	Color colorFont;
	string livesTXT, scoreTXT;
	static Player* PlayerPointer;
};