#include "TestLevel.h"

void TestLevel::init()
{
	LevelID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/Niveles/PeaceTownSheet.png");
	BreakID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/BreakBlock.png");
	HUD_ID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/HUD_Bomberman.png");
	
	OriginHUD = { 0, 0, 525, 66 };
	ProjectedHUD = { 0, 400, 525, 66 };

	//Instance XML Doc	
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile("Imgs/Niveles/LevelTest.tmx") != tinyxml2::XML_SUCCESS) {
		cout << "Error XML: " << doc.ErrorStr();
	}

	//Lectura mapa en consola
	tinyxml2::XMLElement* root = doc.FirstChildElement();

	for (tinyxml2::XMLElement* element = root->FirstChildElement(); element; element = element->NextSiblingElement())
	{
		string Valor = element->Value();
		if (Valor == "layer") {
			tinyxml2::XMLElement* child = element->FirstChildElement();
			mapText = child->GetText();
		}
	}
	string layerTXT(mapText);
	int X = 0, Y = 0;
	//Guardat de dades a array
	while (imageRead == false) {
		nextPos = layerTXT.find(',', pos);
		if (nextPos != std::string::npos)
		{
			int value = std::stoi(layerTXT.substr(pos, nextPos - pos));
			tileMap[Y][X] = value;
			pos = nextPos + 1;
			X++;
			if (X == _sheetWidth) {
				X = 0;
				Y++;
			}
		}
		else {
			// Ultim valor
			int value = std::stoi(layerTXT.substr(pos, layerTXT.size() - pos));
			tileMap[Y][X] = value;
			imageRead = true;
		}
	}

	//Set Static tilemap blocks
	for (int Y = 0; Y < _sheetHeight; Y++) {
		for (int X = 0; X < _sheetWidth; X++) {
			if (tileMap[Y][X] != 8) {
				tileStat[Y][X] = 1;
			}
		}
	}

	//Hand made blocks
	{
		//Breackable fila 1
		tileDest[1][5] = 1;
		tileDest[1][9] = 1;
		tileDest[1][11] = 1;

		//Breackable fila 2
		tileDest[2][12] = 1;

		//Breackable fila 3
		tileDest[3][2] = 1;
		tileDest[3][8] = 1;
		tileDest[3][12] = 1;
		tileDest[3][13] = 1;

		//Breackable fila 4
		tileDest[4][6] = 1;

		//Breackable fila 5
		tileDest[5][2] = 1;
		tileDest[5][5] = 1;
		tileDest[5][6] = 1;

		//Breackable fila 6
		tileDest[6][2] = 1;
		tileDest[6][6] = 1;
		tileDest[6][12] = 1;
		tileDest[6][14] = 1;

		//Breackable fila 7
		tileDest[7][12] = 1;
		tileDest[7][13] = 1;

		//Breackable fila 8
		tileDest[8][2] = 1;
		tileDest[8][10] = 1;
		tileDest[8][12] = 1;

		//Breackable fila 9
		tileDest[9][9] = 1;
		tileDest[9][10] = 1;
		tileDest[9][11] = 1;
		tileDest[9][12] = 1;

		//Breackable fila 10
		tileDest[10][2] = 1;
		tileDest[10][4] = 1;
		tileDest[10][6] = 1;

		//Breackable fila 11
		tileDest[11][4] = 1;
		tileDest[11][8] = 1;
		tileDest[11][13] = 1;
	}


	SetEnemyPos();
	mReinit = false;
}

void TestLevel::update()
{
	Video::getInstace()->updateScreen();

	//Update dels enemics al mapa
	for (int nEnemies = 0; nEnemies < EnemiesInLevel.size(); nEnemies++) {
		if (EnemiesInLevel.at(nEnemies)->hasEnded()) {
			EnemiesInLevel.erase(EnemiesInLevel.begin() + nEnemies);
		}
		else {
			int IDBreak, IDStat;
			IDBreak = getIDfromLayer(1, EnemiesInLevel.at(nEnemies)->getCollision().x + EnemiesInLevel.at(nEnemies)->getCollision().w / 2, EnemiesInLevel.at(nEnemies)->getCollision().y + EnemiesInLevel.at(nEnemies)->getCollision().h / 2);
			IDStat = getIDfromLayer(0, EnemiesInLevel.at(nEnemies)->getCollision().x + EnemiesInLevel.at(nEnemies)->getCollision().w / 2, EnemiesInLevel.at(nEnemies)->getCollision().y + EnemiesInLevel.at(nEnemies)->getCollision().h / 2);

			if (IDBreak == 0 && IDStat == 0) {
				EnemiesInLevel.at(nEnemies)->update();
			}
			else if (EnemiesInLevel.at(nEnemies)->compareID(IDBreak, IDStat)) {
				EnemiesInLevel.at(nEnemies)->update();
			}
			else {
				EnemiesInLevel.at(nEnemies)->changeDirection();
				EnemiesInLevel.at(nEnemies)->update();
			}
		}

	}

	//Update dels power-ups al mapa
	for (int nPowers = 0; nPowers < PowerUpsInLevel.size(); nPowers++) {
		if (PowerUpsInLevel.at(nPowers)->hasEnded()) {
			PowerUpsInLevel.erase(PowerUpsInLevel.begin() + nPowers);
		}
	}

}

void TestLevel::render()
{

	//Bucle de pintat mapa
	for (int Y = 0; Y < _sheetHeight; Y++) {
		for (int X = 0; X < _sheetWidth; X++) {
			rectT.x = X * _tileWidth;
			rectT.y = Y * _tileHeight;
			rectT.w = _tileWidth;
			rectT.h = _tileHeight;
			ID = tileMap[Y][X] - 1;
			if (ID >= 0) {
				CasellaX = ID % tilemapLength;
				CasellaY = ID / tilemapLength;
				rectS.x = CasellaX * _tileWidth + tileSpace * CasellaX;
				rectS.y = CasellaY * _tileHeight + tileSpace * CasellaY;
				rectS.w = _tileWidth;
				rectS.h = _tileHeight;
				Video::getInstace()->renderGraphic(LevelID, rectT, rectS, 0, 0, SDL_FLIP_NONE);
			}
		}
	}

	//Bucle de pintat blocs trencables
	for (int Y = 0; Y < _sheetHeight; Y++) {
		for (int X = 0; X < _sheetWidth; X++) {
			rectT.x = X * _tileWidth;
			rectT.y = Y * _tileHeight;
			rectT.w = _tileWidth;
			rectT.h = _tileHeight;
			int isWall = tileDest[Y][X];
			if (isWall == 1) {
				rectS.x = 0;
				rectS.y = 0;
				rectS.w = _tileWidth;
				rectS.h = _tileHeight;
				Video::getInstace()->renderGraphic(BreakID, rectT, rectS, 0, NULL, SDL_FLIP_NONE);
			}
		}
	}

	//Pintat HUD
	Video::getInstace()->renderGraphic(HUD_ID, ProjectedHUD, OriginHUD, 0, 0, SDL_FLIP_NONE);

	//render Power-ups
	for (int nPowers = 0; nPowers < PowerUpsInLevel.size(); nPowers++) {
		PowerUpsInLevel.at(nPowers)->render();
	}

	//render Enemics
	for (int nEnemies = 0; nEnemies < EnemiesInLevel.size(); nEnemies++) {
		EnemiesInLevel.at(nEnemies)->render();
	}
}

void TestLevel::DestroyWall(int Y, int X)
{
	tileDest[Y][X] = 0;
	//Random % for Power Up (vector of power ups erase random pos)
	int randomPerc = rand() % 100;
	if (randomPerc < 15) {
		int randomType = rand() % 5;
		switch (randomType) {
			//Power up 1 --> Fire up
		case 0:
			{
				FireUp* FireUp_PU = new FireUp(X * 32, Y * 32);
				PowerUpsInLevel.push_back(FireUp_PU);
			}
			break;

			//Power up 2 --> Bombs up
		case 1:
			{
				BombsUp* BombsUp_PU = new BombsUp(X * 32, Y * 32);
				PowerUpsInLevel.push_back(BombsUp_PU);
			}
			break;

			//Power up 3 --> Speed up
		case 2:
			{
				SpeedUp* SpeedUp_PU = new SpeedUp(X * 32, Y * 32);
				PowerUpsInLevel.push_back(SpeedUp_PU);
			}
			break;

			//Power up 4 --> Extra life
		case 3:
			{
				LifeUp* LifeUp_PU = new LifeUp(X * 32, Y * 32);
				PowerUpsInLevel.push_back(LifeUp_PU);
			}
			break;

			//Exit --> Next level
		case 4:
			bool exitExists = false;

			for (int nExits = 0; nExits < PowerUpsInLevel.size(); nExits++) {
				if (PowerUpsInLevel.at(nExits)->getType() == 4) {
					exitExists = true;
				}
			}

			if(!exitExists){
				{
					AudioManager::getInstance()->playFX("Audio/NextLevel.mp3");
					Exit* NextLevel = new Exit(X * 32, Y * 32);
					PowerUpsInLevel.push_back(NextLevel);
				}
			}
			break;
		}

		//Si no queden més blocs, si o si crea sortida
		bool someExit = false, stillPossible = false;
		for (int posY = 0; posY < 13; posY++) {
			for (int posX = 0; posX < 13; posX++) {
				if (tileDest[Y][X] != 0) {
					stillPossible = true;
					break;
				}
			}
		}
		for (int nExits = 0; nExits < PowerUpsInLevel.size(); nExits++) {
			if (PowerUpsInLevel.at(nExits)->getType() == 4) {
				someExit = true;
			}
		}
		if (!stillPossible && !someExit) {
			AudioManager::getInstance()->playFX("Audio/NextLevel.mp3");
			Exit* NextLevel = new Exit(X * 32, Y * 32);
			PowerUpsInLevel.push_back(NextLevel);
		}
	}
}

void TestLevel::SetEnemyPos()
{
	if (EnemiesInLevel.size() > 0) {
		EnemiesInLevel.clear();
	}
	if (PowerUpsInLevel.size() > 0) {
		PowerUpsInLevel.clear();
	}
	Puropen* Puropen_Enemy = new Puropen();
	Puropen_Enemy->setPosition(64, 207);

	Puropen* Puropen_Enemy2 = new Puropen();
	Puropen_Enemy2->setPosition(384, 143);

	Puropen* Puropen_Enemy3 = new Puropen();
	Puropen_Enemy3->setPosition(192, 15);

	EnemiesInLevel.push_back(Puropen_Enemy);
	EnemiesInLevel.push_back(Puropen_Enemy2);
	EnemiesInLevel.push_back(Puropen_Enemy3);
}

int TestLevel::getTileHeight()
{
	return _tileHeight;
}

int TestLevel::getTileWidth()
{
	return _tileWidth;
}

int TestLevel::getHeight()
{
	return _sheetWidth;
}

int TestLevel::getWidth()
{
	return _sheetHeight;
}

int TestLevel::getGridPosX(int PosX)
{
	int TileX = PosX / _tileWidth;
	return TileX;
}

int TestLevel::getGridPosY(int PosY)
{
	int TileY = PosY / _tileHeight;
	return TileY;
}

int TestLevel::getIDfromLayer(int layer, int PosX, int PosY)
{
	int TileX = PosX / _tileWidth;
	int TileY = PosY / _tileHeight;
	if (layer == 0) {
		return tileStat[TileY][TileX];
	}
	else if (layer == 1) {
		return tileDest[TileY][TileX];
	}
}
