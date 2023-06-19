#include "Bomba.h"

Bomba::Bomba(int X, int Y, int RadiSize)
{
    x = X;
    y = Y;
	radiSize = RadiSize;
	ImageID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/Bomb.png");
	ExplodeID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/Explode.png");
	timerLoad = 3000.0f;
    timerExplode = 1500.0f;
    Phases = LOADING;
	AnimRow = 0;
	ImgFrame = 0;
	ProjectRect = { 0, 0, 32, 32 };
	Size = { x, y, 32, 32 };
	for (int Directions = 0; Directions < 4; Directions++) {
		for (int GridExplosions = 0; GridExplosions < radiSize; GridExplosions++) {
			ExplosionDirections[Directions].push_back({0, 0, 32, 32});
		}
	}
	Points = 0;
	ended = false;
}
Bomba::Bomba(int X, int Y, int RadiSize, BaseScene* thisWorld)
{
    x = X;
    y = Y;
	MyWorld = thisWorld;
	radiSize = RadiSize;
	ImageID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/Bomb.png");
	ExplodeID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/Explode.png");
	timerLoad = 3000.0f;
    timerExplode = 1500.0f;
    Phases = LOADING;
	AnimRow = 0;
	ImgFrame = 0;
	ProjectRect = { 0, 0, 32, 32 };
	Size = { x, y, 32, 32 };
	for (int Directions = 0; Directions < 4; Directions++) {
		for (int GridExplosions = 0; GridExplosions < radiSize; GridExplosions++) {
			ExplosionDirections[Directions].push_back({0, 0, 32, 32});
		}
	}
	Points = 0;
	ended = false;
}

Bomba::~Bomba()
{
}

void Bomba::changeAnimFrame()
{
}

void Bomba::setExplodeCol()
{
	//Colisons left
	for (int GridExplosions = 0; GridExplosions < ExplosionDirections[0].size(); GridExplosions++) {
		int newX;
		newX = x - (32 * (GridExplosions + 1));
		ExplosionDirections[0].at(GridExplosions) = { newX, y, 32, 32 };
		PointX = newX;
		PointY = y;

		if (MyWorld->getIDfromLayer(0, PointX, PointY) > 0) {
			ExplosionDirections[0].erase(ExplosionDirections[0].begin() + GridExplosions);
			GridExplosions--;
		}
		else if (MyWorld->getIDfromLayer(1, PointX, PointY) > 0) {
			ExplosionDirections[0].erase(ExplosionDirections[0].begin() + GridExplosions);
			MyWorld->DestroyWall(MyWorld->getGridPosY(PointY), MyWorld->getGridPosX(PointX));
			GridExplosions--;
		}
	}
	//Colisons right
	for (int GridExplosions = 0; GridExplosions < ExplosionDirections[1].size(); GridExplosions++) {
		int newX;
		newX = x + (32 * (GridExplosions + 1));
		ExplosionDirections[1].at(GridExplosions) = { newX, y, 32, 32 };
		PointX = newX;
		PointY = y;

		if (MyWorld->getIDfromLayer(0, PointX, PointY) > 0) {
			ExplosionDirections[1].erase(ExplosionDirections[1].begin() + GridExplosions);
			GridExplosions--;
		}
		else if (MyWorld->getIDfromLayer(1, PointX, PointY) > 0) {
			ExplosionDirections[1].erase(ExplosionDirections[1].begin() + GridExplosions);
			MyWorld->DestroyWall(MyWorld->getGridPosY(PointY), MyWorld->getGridPosX(PointX));
			GridExplosions--;
		}
	}

	//Colisons up
	for (int GridExplosions = 0; GridExplosions < ExplosionDirections[2].size(); GridExplosions++) {
		int newY;
		newY = y - (32 * (GridExplosions + 1));
		ExplosionDirections[2].at(GridExplosions) = { x, newY, 32, 32 };
		PointX = x;
		PointY = newY;

		if (MyWorld->getIDfromLayer(0, PointX, PointY) > 0) {
			ExplosionDirections[2].erase(ExplosionDirections[2].begin() + GridExplosions);
			GridExplosions--;
		}
		else if (MyWorld->getIDfromLayer(1, PointX, PointY) > 0) {
			ExplosionDirections[2].erase(ExplosionDirections[2].begin() + GridExplosions);
			MyWorld->DestroyWall(MyWorld->getGridPosY(PointY), MyWorld->getGridPosX(PointX));
			GridExplosions--;
		}
	}
	//Colisons down
	for (int GridExplosions = 0; GridExplosions < ExplosionDirections[3].size(); GridExplosions++) {
		int newY;
		newY = y + (32 * (GridExplosions + 1));
		ExplosionDirections[3].at(GridExplosions) = { x, newY, 32, 32 };
		PointX = x;
		PointY = newY;

		if (MyWorld->getIDfromLayer(0, PointX, PointY) > 0) {
			ExplosionDirections[3].erase(ExplosionDirections[3].begin() + GridExplosions);
			GridExplosions--;
		}
		else if (MyWorld->getIDfromLayer(1, PointX, PointY) > 0) {
			ExplosionDirections[3].erase(ExplosionDirections[3].begin() + GridExplosions);
			MyWorld->DestroyWall(MyWorld->getGridPosY(PointY), MyWorld->getGridPosX(PointX));
			GridExplosions--;
		}
	}
}

void Bomba::updateExplosion()
{
	//Left explosions
	for (int GridExplosions = 0; GridExplosions < ExplosionDirections[0].size(); GridExplosions++) {
		for (int nEnemies = 0; nEnemies < MyWorld->getEnemiesInLevel(); nEnemies++) {
			SobreRect EnemyRect = MyWorld->getEnemy(nEnemies)->getCollision();
			SobreRect BombRect = ExplosionDirections[0].at(GridExplosions);

			if (Video::getInstace()->rectIntersaction(EnemyRect, BombRect)) {
				MyWorld->getEnemy(nEnemies)->GetHit();

				if (MyWorld->getEnemy(nEnemies)->hasEnded())
					Points += MyWorld->getEnemy(nEnemies)->getPunts();
			}
		}
	}

	//Right explosions
	for (int GridExplosions = 0; GridExplosions < ExplosionDirections[1].size(); GridExplosions++) {
		for (int nEnemies = 0; nEnemies < MyWorld->getEnemiesInLevel(); nEnemies++) {
			SobreRect EnemyRect = MyWorld->getEnemy(nEnemies)->getCollision();
			SobreRect BombRect = ExplosionDirections[1].at(GridExplosions);

			SDL_Rect rect1, rect2;
			rect1 = { EnemyRect.x, EnemyRect.y, EnemyRect.w, EnemyRect.h };
			rect2 = { BombRect.x, BombRect.y, BombRect.w, BombRect.h };

			if (Video::getInstace()->rectIntersaction(EnemyRect, BombRect)) {
				MyWorld->getEnemy(nEnemies)->GetHit();

				if (MyWorld->getEnemy(nEnemies)->hasEnded())
					Points += MyWorld->getEnemy(nEnemies)->getPunts();
			}
		}
	}

	//Up explosions
	for (int GridExplosions = 0; GridExplosions < ExplosionDirections[2].size(); GridExplosions++) {
		for (int nEnemies = 0; nEnemies < MyWorld->getEnemiesInLevel(); nEnemies++) {
			SobreRect EnemyRect = MyWorld->getEnemy(nEnemies)->getCollision();
			SobreRect BombRect = ExplosionDirections[2].at(GridExplosions);

			SDL_Rect rect1, rect2;
			rect1 = { EnemyRect.x, EnemyRect.y, EnemyRect.w, EnemyRect.h };
			rect2 = { BombRect.x, BombRect.y, BombRect.w, BombRect.h };

			if (Video::getInstace()->rectIntersaction(EnemyRect, BombRect)) {
				MyWorld->getEnemy(nEnemies)->GetHit();

				if (MyWorld->getEnemy(nEnemies)->hasEnded())
					Points += MyWorld->getEnemy(nEnemies)->getPunts();
			}
		}
	}

	//Down explosions
	for (int GridExplosions = 0; GridExplosions < ExplosionDirections[3].size(); GridExplosions++) {
		for (int nEnemies = 0; nEnemies < MyWorld->getEnemiesInLevel(); nEnemies++) {
			SobreRect EnemyRect = MyWorld->getEnemy(nEnemies)->getCollision();
			SobreRect BombRect = ExplosionDirections[3].at(GridExplosions);

			SDL_Rect rect1, rect2;
			rect1 = { EnemyRect.x, EnemyRect.y, EnemyRect.w, EnemyRect.h };
			rect2 = { BombRect.x, BombRect.y, BombRect.w, BombRect.h };

			if (Video::getInstace()->rectIntersaction(EnemyRect, BombRect)) {
				MyWorld->getEnemy(nEnemies)->GetHit();

				if (MyWorld->getEnemy(nEnemies)->hasEnded())
					Points += MyWorld->getEnemy(nEnemies)->getPunts();
			}
		}
	}
}

void Bomba::renderExplosions()
{
	//Explosions left
	for (int GridExplosions = 0; GridExplosions < radiSize && GridExplosions < ExplosionDirections[0].size(); GridExplosions++) {
		Video::getInstace()->renderGraphic(ExplodeID, ExplosionDirections[0].at(GridExplosions), ProjectRect, 0, NULL, SDL_FLIP_NONE);
	}
	//Explosions right
	for (int GridExplosions = 0; GridExplosions < radiSize && GridExplosions < ExplosionDirections[1].size(); GridExplosions++) {
		Video::getInstace()->renderGraphic(ExplodeID, ExplosionDirections[1].at(GridExplosions), ProjectRect, 0, NULL, SDL_FLIP_NONE);
	}

	//Explosions up
	for (int GridExplosions = 0; GridExplosions < radiSize && GridExplosions < ExplosionDirections[2].size(); GridExplosions++) {
			Video::getInstace()->renderGraphic(ExplodeID, ExplosionDirections[2].at(GridExplosions), ProjectRect, 0, NULL, SDL_FLIP_NONE);
	}
	//Explosions down
	for (int GridExplosions = 0; GridExplosions < radiSize && GridExplosions < ExplosionDirections[3].size(); GridExplosions++) {
		Video::getInstace()->renderGraphic(ExplodeID, ExplosionDirections[3].at(GridExplosions), ProjectRect, 0, NULL, SDL_FLIP_NONE);
	}
}

void Bomba::update()
{
	switch (Phases) {
	case LOADING:
		timerLoad -= Video::getInstace()->GetDeltaTime();
		if (timerLoad <= 0) {
			setExplodeCol();
			//Play explosion FX
			AudioManager::getInstance()->playFX("Audio/Explosion.mp3");
			Phases = EXPLODING;
		}
		break;

	case EXPLODING:
		timerExplode -= Video::getInstace()->GetDeltaTime(); 
		updateExplosion();
		if (timerExplode <= 0) {
			Phases = END;
		}
		break;

	case END:
		ended = true;
		break;
	default:
		break;
	}
}

void Bomba::render()
{
	switch (Phases) {
	case LOADING:
		Video::getInstace()->renderGraphic(ImageID, Size, ProjectRect, 0, NULL, SDL_FLIP_NONE);
		break;

	case EXPLODING:
		renderExplosions();
		break;

	case END:
		break;
	default:
		break;
	}
}
