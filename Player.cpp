#include "Player.h"

Player* Player::PlayerPointer = NULL;

Player::Player(bool isCont) {
	speedMove = 5;
	maxBombs = 1;
	lives = 3;
	punts = 0;
	radiBomba = 1;
	isController = isCont;
	if (!isCont) {
		ImageID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/Player1.png");
	}
	else {
		ImageID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/Player2.png");
	}
	ResourceManager::getInstance()->printLoadedGraphics();
	SetSpriteSize();
	AnimRow = 0;
	AnimTimer = 0;
	ImgFrame = 0;
	Player_State = IDLE;
	colorFont = { 255, 255, 255 };
	scoreTXT = std::to_string(punts);
	livesTXT = std::to_string(lives);
}

void Player::ChangeAnimationFrame()
{
	switch (Player_State) {
	case IDLE:
		AnimRow = 0;
		ImgFrame = 0;
		break;
	case MOVE_LEFT:
		AnimRow = 1;
		break;
	case MOVE_RIGHT:
		AnimRow = 2;
		break;
	case MOVE_UP:
		AnimRow = 3;
		break;
	case MOVE_DOWN:
		AnimRow = 4;
		break;
	case DIE:
		AnimRow = 5;
		break;
	}

	ProjectRect.x = ProjectRect.w * ImgFrame;
	ProjectRect.y = ProjectRect.h * AnimRow;
}

void Player::ResetPlayer()
{
	speedMove = 5;
	maxBombs = 1;
	lives = 3;
	punts = 0;
	radiBomba = 1;
}

void Player::SetSpriteSize()
{
	Size.x = 65;
	Size.y = 10;
	Size.w = 32;
	Size.h = 48;

	setCol({Size.x + 8, Size.y + 24, 16, 12});

	ProjectRect.x = 65;
	ProjectRect.y = 10;
	ProjectRect.w = 16;
	ProjectRect.h = 24;
}

void Player::Render()
{
	Video::getInstace()->renderGraphic(ImageID, Size, ProjectRect, 0, NULL, SDL_FLIP_NONE);

	for (int nBombs = 0; nBombs < ActualBombs.size(); nBombs++) {
		ActualBombs.at(nBombs)->render();
	}

	Video::getInstace()->renderText(scoreTXT, colorFont, { 105, 417, 300, 100 });
	Video::getInstace()->renderText(livesTXT, colorFont, { 50, 417, 200, 50 });
}

void Player::Update()
{
	AnimTimer += Video::getInstace()->GetDeltaTime();
	if (AnimTimer >= 100)
	{
		scoreTXT = std::to_string(punts);
		livesTXT = std::to_string(lives);
		ImgFrame++;
		if (ImgFrame == 4)//Frames per animation
		{
			if (Player_State != DIE) {
				ImgFrame = 0;
			}
			else
			{
				Dying = false;
			}
		}
		AnimTimer = 0;
		if (Player_State != DIE) {
			if (!isController) {
				Size.x += (int)(InputManager::getInstance()->getDirectionsP1()->isLeft * speedMove);
				Size.y += (int)(InputManager::getInstance()->getDirectionsP1()->isUp * speedMove);
			}
			else {
				Size.x += (int)(InputManager::getInstance()->getDirectionsP2()->isLeft * speedMove);
				Size.y += (int)(InputManager::getInstance()->getDirectionsP2()->isUp * speedMove);
			}
		}

		setCol({ Size.x + 8, Size.y + 24, 16, 12 });

		//Detect colision Player-Enemy
		for (int nEnemies = 0; nEnemies < MyWorld->getEnemiesInLevel(); nEnemies++) {
			SobreRect EnemyRect = MyWorld->getEnemy(nEnemies)->getCollision();

			if (Video::getInstace()->rectIntersaction(EnemyRect, Collision)) {
				AudioManager::getInstance()->playFX("Audio/Death.mp3");
				lives--;
				ImgFrame = 0;
				Dying = true;
				if (lives > 0) {
					Size.x = 65;
					Size.y = 10;
					setCol({ Size.x + 8, Size.y + 24, 16, 12 });
				}
				else {
					//End screen
					for (int nBombas = 0; nBombas < ActualBombs.size(); nBombas++) {
						ActualBombs.at(nBombas)->setEnded();
					}
					MyWorld->init();
					SceneManager::getInstance()->changeScene(LOSE, true);
				}
			}
		}

		//Detect colision Player-PowerUps
		for (int nPowers = 0; nPowers < MyWorld->getPowerUpsInLevel(); nPowers++) {
			SobreRect PowerRect = MyWorld->getPowerUp(nPowers)->getCollision();

			if (Video::getInstace()->rectIntersaction(PowerRect, Collision)) {
				int PowerType = MyWorld->getPowerUp(nPowers)->getType();
				
				switch (PowerType) {
				case 0:
					radiBomba++;
					punts += 10;
					MyWorld->getPowerUp(nPowers)->setEnded();
					break;
				case 1:
					maxBombs++;
					punts += 10;
					MyWorld->getPowerUp(nPowers)->setEnded();
					break;
				case 2:
					speedMove++;
					punts += 10;
					MyWorld->getPowerUp(nPowers)->setEnded();
					break;
				case 3:
					lives++;
					punts += 10;
					MyWorld->getPowerUp(nPowers)->setEnded();
					break;
				case 4:
					MyWorld->nextLevel();
					punts += 500;
					SetSpriteSize();
				default:
					break;
				}
			}
		}

		//Detect collisions explosions
		for (int nBombs = 0; nBombs < ActualBombs.size(); nBombs++) {
			//Check collisions for each direction
			for (int direction = 0; direction < 4; direction++) {
				for (int nExplosions = 0; nExplosions < ActualBombs.at(nBombs)->ExplosionSize(direction); nExplosions++) {
					SobreRect explosionRect = ActualBombs.at(nBombs)->ExplosionRect(direction, nExplosions);
					if (Video::getInstace()->rectIntersaction(explosionRect, Collision)) {
						AudioManager::getInstance()->playFX("Audio/Death.mp3");
						lives--;
						ImgFrame = 0;
						Dying = true;
						if (lives > 0) {
							Size.x = 65;
							Size.y = 10;
							setCol({ Size.x + 8, Size.y + 24, 16, 12 });
						}
						else {
							//End screen
							for (int nBombas = 0; nBombas < ActualBombs.size(); nBombas++) {
								ActualBombs.at(nBombas)->setEnded();
							}
							MyWorld->init();
							SceneManager::getInstance()->changeScene(LOSE, true);
						}
					}
				}
			}
		}
	}
	updateState(isController);

	//Destroy non active bombs and update the alive ones
	for (int nBombs = 0; nBombs < ActualBombs.size(); nBombs++) {
		ActualBombs.at(nBombs)->update();
		if (ActualBombs.at(nBombs)->hasEnded()) {
			punts += ActualBombs.at(nBombs)->getPoints();
			ActualBombs.erase(ActualBombs.begin() + nBombs);
			nBombs--;
		}
	}

	ChangeAnimationFrame();
	CheckCollisions();
	LimitScreen();
}

int Player::LimitScreen()
{
	if (Size.x < 0) {
		Size.x = 0;
	}
	else if (Size.x + Size.w > SCREEN_WIDTH) {
		Size.x = (SCREEN_WIDTH - Size.w);
	}

	if (Size.y < 0) {
		Size.y = 0;
	}
	else if (Size.y + Size.h > SCREEN_HEIGHT) {
		Size.y = (SCREEN_HEIGHT - Size.h);
	}
	return 0;
}

void Player::updateState(bool isController)
{
	int x, y;
	if (!isController) {
		x = InputManager::getInstance()->getDirectionsP1()->isLeft;
		y = InputManager::getInstance()->getDirectionsP1()->isUp;
	}
	else {
		x = InputManager::getInstance()->getDirectionsP2()->isLeft;
		y = InputManager::getInstance()->getDirectionsP2()->isUp;
	}

	//Action bomb
	if (InputManager::getInstance()->HasBomb()) {
		if (ActualBombs.size() < maxBombs) {
			PlantBomb();
		}
	}

	if (x > 0) {
		Player_State = MOVE_RIGHT;
	}
	else if (x < 0) {
		Player_State = MOVE_LEFT;
	}
	else if (y > 0) {
		Player_State = MOVE_DOWN;
	}
	else if (y < 0) {
		Player_State = MOVE_UP;
	}
	else if (Dying) {
		Player_State = DIE;
	}
	else if(x == 0 && y == 0){
		Player_State = IDLE;
	}
}

void Player::SetWorldPointer(BaseScene* map)
{
	MyWorld = map;
	_WorldSizeW = MyWorld->getWidth() * MyWorld->getTileWidth();
	_WorldSizeH = MyWorld->getHeight() * MyWorld->getTileHeight();
}

void Player::CheckCollisions()
{
	switch (Player_State) {
	case MOVE_RIGHT:
		Point1X = Collision.x + Collision.w;
		Point1Y = Collision.y;

		Point2X = Collision.x + Collision.w;
		Point2Y = Collision.y + Collision.h;

		Point3X = Point1X;
		Point3Y = ((Point1Y + Point2Y) / 2);

		CollisionInt += MyWorld->getIDfromLayer(0, Point1X, Point1Y);
		CollisionInt += MyWorld->getIDfromLayer(0, Point2X, Point2Y);
		CollisionInt += MyWorld->getIDfromLayer(0, Point3X, Point3Y);

		CollisionInt += MyWorld->getIDfromLayer(1, Point1X, Point1Y);
		CollisionInt += MyWorld->getIDfromLayer(1, Point2X, Point2Y);
		CollisionInt += MyWorld->getIDfromLayer(1, Point3X, Point3Y);

		if (CollisionInt > 0) {
			while (CollisionInt > 0) {
				CollisionInt = 0;
				Size.x--;
				setCol({ Size.x, Size.y + 24, 16, 12 });

				Point1X = Collision.x + Collision.w;
				Point1Y = Collision.y;

				Point2X = Collision.x + Collision.w;
				Point2Y = Collision.y + Collision.h;

				Point3X = Point1X;
				Point3Y = ((Point1Y + Point2Y) / 2);

				CollisionInt += MyWorld->getIDfromLayer(0, Point1X, Point1Y);
				CollisionInt += MyWorld->getIDfromLayer(0, Point2X, Point2Y);
				CollisionInt += MyWorld->getIDfromLayer(0, Point3X, Point3Y);

				CollisionInt += MyWorld->getIDfromLayer(1, Point1X, Point1Y);
				CollisionInt += MyWorld->getIDfromLayer(1, Point2X, Point2Y);
				CollisionInt += MyWorld->getIDfromLayer(1, Point3X, Point3Y);
			}
		}

		break;
	case MOVE_LEFT:
		Point1X = Collision.x + Collision.w;
		Point1Y = Collision.y;

		Point2X = Collision.x + Collision.w;
		Point2Y = Collision.y + Collision.h;

		Point3X = Point2X;
		Point3Y = ((Point1Y + Point2Y) / 2);

		CollisionInt += MyWorld->getIDfromLayer(0, Point1X, Point1Y);
		CollisionInt += MyWorld->getIDfromLayer(0, Point2X, Point2Y);
		CollisionInt += MyWorld->getIDfromLayer(0, Point3X, Point3Y);

		CollisionInt += MyWorld->getIDfromLayer(1, Point1X, Point1Y);
		CollisionInt += MyWorld->getIDfromLayer(1, Point2X, Point2Y);
		CollisionInt += MyWorld->getIDfromLayer(1, Point3X, Point3Y);

		if (CollisionInt > 0) {
			while (CollisionInt > 0) {
				CollisionInt = 0;
				Size.x++;
				setCol({ Size.x, Size.y + 24, 16, 12 });

				Point1X = Collision.x + Collision.w;
				Point1Y = Collision.y;

				Point2X = Collision.x + Collision.w;
				Point2Y = Collision.y + Collision.h;

				Point3X = Point2X;
				Point3Y = ((Point1Y + Point2Y) / 2);

				CollisionInt += MyWorld->getIDfromLayer(0, Point1X, Point1Y);
				CollisionInt += MyWorld->getIDfromLayer(0, Point2X, Point2Y);
				CollisionInt += MyWorld->getIDfromLayer(0, Point3X, Point3Y);

				CollisionInt += MyWorld->getIDfromLayer(1, Point1X, Point1Y);
				CollisionInt += MyWorld->getIDfromLayer(1, Point2X, Point2Y);
				CollisionInt += MyWorld->getIDfromLayer(1, Point3X, Point3Y);

			}
		}

		break;
	case MOVE_UP:
		Point1X = Collision.x;
		Point1Y = Collision.y;

		Point2X = Collision.x + Collision.w;
		Point2Y = Collision.y;

		Point3X = ((Point1X + Point2X) / 2);
		Point3Y = Point1Y;

		CollisionInt += MyWorld->getIDfromLayer(0, Point1X, Point1Y);
		CollisionInt += MyWorld->getIDfromLayer(0, Point2X, Point2Y);
		CollisionInt += MyWorld->getIDfromLayer(0, Point3X, Point3Y);

		CollisionInt += MyWorld->getIDfromLayer(1, Point1X, Point1Y);
		CollisionInt += MyWorld->getIDfromLayer(1, Point2X, Point2Y);
		CollisionInt += MyWorld->getIDfromLayer(1, Point3X, Point3Y);


		if (CollisionInt > 0) {
			while (CollisionInt > 0) {
				CollisionInt = 0;
				Size.y++;
				setCol({ Size.x, Size.y + 24, 16, 12 });

				Point1X = Collision.x;
				Point1Y = Collision.y;

				Point2X = Collision.x + Collision.w;
				Point2Y = Collision.y;

				Point3X = ((Point1X + Point2X) / 2);
				Point3Y = Point1Y;

				CollisionInt += MyWorld->getIDfromLayer(0, Point1X, Point1Y);
				CollisionInt += MyWorld->getIDfromLayer(0, Point2X, Point2Y);
				CollisionInt += MyWorld->getIDfromLayer(0, Point3X, Point3Y);

				CollisionInt += MyWorld->getIDfromLayer(1, Point1X, Point1Y);
				CollisionInt += MyWorld->getIDfromLayer(1, Point2X, Point2Y);
				CollisionInt += MyWorld->getIDfromLayer(1, Point3X, Point3Y);

			}
		}

		break;

	case MOVE_DOWN:
		Point1X = Collision.x;
		Point1Y = Collision.y + Collision.h;

		Point2X = Collision.x + Collision.w;
		Point2Y = Collision.y + Collision.h;

		Point3X = ((Point1X + Point2X) / 2);
		Point3Y = Point1Y;

		CollisionInt += MyWorld->getIDfromLayer(0, Point1X, Point1Y);
		CollisionInt += MyWorld->getIDfromLayer(0, Point2X, Point2Y);
		CollisionInt += MyWorld->getIDfromLayer(0, Point3X, Point3Y);

		CollisionInt += MyWorld->getIDfromLayer(1, Point1X, Point1Y);
		CollisionInt += MyWorld->getIDfromLayer(1, Point2X, Point2Y);
		CollisionInt += MyWorld->getIDfromLayer(1, Point3X, Point3Y);


		if (CollisionInt > 0) {
			while (CollisionInt > 0) {
				CollisionInt = 0;
				Size.y--;
				setCol({ Size.x, Size.y + 24, 16, 12 });

				Point1X = Collision.x;
				Point1Y = Collision.y + Collision.h;

				Point2X = Collision.x + Collision.w;
				Point2Y = Collision.y + Collision.h;

				Point3X = ((Point1X + Point2X) / 2);
				Point3Y = Point1Y;

				CollisionInt += MyWorld->getIDfromLayer(0, Point1X, Point1Y);
				CollisionInt += MyWorld->getIDfromLayer(0, Point2X, Point2Y);
				CollisionInt += MyWorld->getIDfromLayer(0, Point3X, Point3Y);

				CollisionInt += MyWorld->getIDfromLayer(1, Point1X, Point1Y);
				CollisionInt += MyWorld->getIDfromLayer(1, Point2X, Point2Y);
				CollisionInt += MyWorld->getIDfromLayer(1, Point3X, Point3Y);

			}
		}

		break;

	case IDLE:
		Point1X = Collision.x + Collision.w;
		Point1Y = Collision.y;

		Point2X = Collision.x + Collision.w;
		Point2Y = Collision.y + Collision.h;

		Point3X = Point1X;
		Point3Y = ((Point1Y + Point2Y) / 2);


		break;

	default:
		break;
	}
}

void Player::PlantBomb()
{
	int X = MyWorld->getGridPosX(Collision.x) * MyWorld->getTileWidth();
	int Y = MyWorld->getGridPosY(Collision.y) * MyWorld->getTileHeight();

	Bomba* newBomb = new Bomba(X, Y, radiBomba);
	newBomb->setWorldPointer(MyWorld);

	ActualBombs.push_back(newBomb);
}

Player* Player::PlayerInstance()
{
	if (PlayerPointer == NULL)
		PlayerPointer = new Player(false);

	return PlayerPointer;
}
