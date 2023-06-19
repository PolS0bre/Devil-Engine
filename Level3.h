#pragma once
#include "BaseScene.h"

#include "BaseEnemy.h"
#include "Puropen.h"
#include "Denkyun.h"
#include "NutsStar.h"
#include "MechaBomb.h"

#include "BasePowerUp.h"
#include "FireUp.h"
#include "BombsUp.h"
#include "SpeedUp.h"
#include "LifeUp.h"
#include "Exit.h"

#include "Video.h"
#include "tinyxml2.h"
#include <vector>
using namespace std;
class Level3 :public BaseScene
{
public:
	void init();
	void update();
	void render();
	void DestroyWall(int Y, int X);
	void SetEnemyPos();
	void DestroyAllEnemies() { EnemiesInLevel.clear(); };

	int getTileHeight();
	int getTileWidth();
	int getHeight();
	int getWidth();
	int getGridPosX(int PosX);
	int getGridPosY(int PosY);
	void nextLevel() { SceneManager::getInstance()->changeScene(LVL4, true); };

	int getIDfromLayer(int layer, int PosX, int PosY);
	int getEnemiesInLevel() { return EnemiesInLevel.size(); };
	int getPowerUpsInLevel() { return PowerUpsInLevel.size(); };

	BaseEnemy* getEnemy(int ID) { return EnemiesInLevel.at(ID); };
	BasePowerUp* getPowerUp(int ID) { return PowerUpsInLevel.at(ID); };
private:
	int LevelID, BreakID, HUD_ID;
	//Variables XML
	SobreRect rectS, rectT;
	int ID, CasellaX, CasellaY;
	int _tileWidth = 32, _tileHeight = 32, _sheetWidth = 17, _sheetHeight = 13, tilemapLength = 4;

	//Capa visual
	int tileMap[13][17];

	//Capa 0 estatica
	int tileStat[13][17];

	//Capa 1 Blocs Destruibles
	int tileDest[13][17];

	int tileSpace = 0;
	int CameraX;
	const char* mapText = NULL;

	vector<BaseEnemy*> EnemiesInLevel;
	vector<BasePowerUp*> PowerUpsInLevel;

	SobreRect OriginHUD, ProjectedHUD;

	size_t pos = 0;
	size_t nextPos = 0;
	bool imageRead = false;
};

