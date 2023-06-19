#pragma once
#include "BaseScene.h"
#include "BaseEnemy.h"
#include "BasePowerUp.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "FileManager.h"
class ScoreMenu :public BaseScene
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
	int ScoreID;
	Color colorFont, colorTitle;
	std::vector <ScoreUser> vectScores;
	vector<string> TOP10;
};

