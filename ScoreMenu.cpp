#include "ScoreMenu.h"


void ScoreMenu::init()
{
    ScoreID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/BackgroundLoseScore.png");
    ScreenRect.x = 0;
    ScreenRect.y = 0;
    ScreenRect.w = SCREEN_WIDTH;
    ScreenRect.h = SCREEN_HEIGHT;
    mReinit = false;
    colorFont = { 255, 255, 255 };
    colorTitle = { 255, 0, 0 };
    if (TOP10.size() > 0) {
        TOP10.clear();
    }
    if (vectScores.size() > 0) {
        vectScores.clear();
    }
    //Check if can read file
    if (FileManager::getInstance()->scoreComp(&vectScores))
    {
        //Load scores
        for (unsigned int i = 0; i < vectScores.size() && i < 10; i++)
        {
            string username = vectScores.at(i)._username;
            string score = std::to_string(vectScores.at(i)._score);
            username += "   ";
            username += score;

            TOP10.push_back(username);
        }
    }
}

void ScoreMenu::update()
{
    MenuButtons* MB = InputManager::getInstance()->getMenuInput();
    //Return to menu
    if (MB->Enter) {
        SceneManager::getInstance()->changeScene(MAIN, true);
    }
    Video::getInstace()->updateScreen();
}

void ScoreMenu::render()
{
    Video::getInstace()->renderGraphic(ScoreID, ScreenRect, ScreenRect, 0, NULL, SDL_FLIP_NONE);
    Video::getInstace()->renderText("Press    P    to    return", colorFont, { 115, 350, 200, 50 });
    //render scores text
    Video::getInstace()->renderText("SCOREBOARD", colorTitle, { 175, 120, 300, 100 });
    for (int nScores = 0; nScores < TOP10.size(); nScores++) {
        Video::getInstace()->renderText(TOP10.at(nScores), colorFont, { 200, 140 + (nScores * 20), 300, 100 });
    }
}

void ScoreMenu::DestroyWall(int Y, int X)
{
}

int ScoreMenu::getTileHeight()
{
    return 0;
}

int ScoreMenu::getTileWidth()
{
    return 0;
}

int ScoreMenu::getHeight()
{
    return 0;
}

int ScoreMenu::getWidth()
{
    return 0;
}

int ScoreMenu::getGridPosX(int PosX)
{
    return 0;
}

int ScoreMenu::getGridPosY(int PosY)
{
    return 0;
}

BaseEnemy* ScoreMenu::getEnemy(int ID)
{
    return nullptr;
}

BasePowerUp* ScoreMenu::getPowerUp(int ID)
{
    return nullptr;
}

int ScoreMenu::getIDfromLayer(int layer, int PosX, int PosY)
{
    return 0;
}
