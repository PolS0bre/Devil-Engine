#pragma once
#include "BaseScene.h"
#include "BaseEnemy.h"
#include "BasePowerUp.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "FileManager.h"
#include "InputManager.h"
class LoseScreen :public BaseScene
{
public:
	void init();
	void update();
	void render();
	void DestroyWall(int Y, int X);

	int getTileHeight();
	int getTileWidth();
	int getHeight();
	int getWidth();
	int getGridPosX(int PosX);
	int getGridPosY(int PosY);
	int getEnemiesInLevel() { return 0; }; 
	int getPowerUpsInLevel() { return 0; };
	void nextLevel() { };

	BaseEnemy* getEnemy(int ID);
	BasePowerUp* getPowerUp(int ID);
	int getIDfromLayer(int layer, int PosX, int PosY);
private:
	SobreRect ScreenRect;
	int LoseID;
	Color colorFont, colorSelect;
	char char1, char2, char3;
	int indx1, indx2, indx3;
	int pos;
	string userName;
	let Letters;
	int score;
};

