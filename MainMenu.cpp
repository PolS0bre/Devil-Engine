#include "MainMenu.h"

void MainMenu::init()
{
	MainMenuID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/MainMenuBG.jpg");
	ScreenRect.x = 0;
	ScreenRect.y = 0;
	ScreenRect.w = SCREEN_WIDTH;
	ScreenRect.h = SCREEN_HEIGHT;
	colorText = { 0, 0, 0 };
	mReinit = false;
}

void MainMenu::update()
{
	MenuButtons* MB = InputManager::getInstance()->getMenuInput();
	if (MB->Options) {
		SceneManager::getInstance()->changeScene(SCORE, true);
	}
	else if (MB->Enter) {
		SceneManager::getInstance()->changeScene(GAME, true);
	}
	Video::getInstace()->updateScreen();
}

void MainMenu::render()
{
	Video::getInstace()->renderGraphic(MainMenuID, ScreenRect, ScreenRect, 0, NULL, SDL_FLIP_NONE);

	Video::getInstace()->renderText("P:   Play", colorText, { 115, 350, 200, 50 });
	Video::getInstace()->renderText("0:   Scoreboard", colorText, { 115, 375, 200, 50 });
}

void MainMenu::DestroyWall(int Y, int X)
{
}

int MainMenu::getTileHeight()
{
	return 0;
}

int MainMenu::getTileWidth()
{
	return 0;
}

int MainMenu::getHeight()
{
	return 0;
}

int MainMenu::getWidth()
{
	return 0;
}

int MainMenu::getGridPosX(int PosX)
{
	return 0;
}

int MainMenu::getGridPosY(int PosY)
{
	return 0;
}

BaseEnemy* MainMenu::getEnemy(int ID)
{
	return nullptr;
}

BasePowerUp* MainMenu::getPowerUp(int ID)
{
	return nullptr;
}

int MainMenu::getIDfromLayer(int layer, int PosX, int PosY)
{
	return 0;
}
