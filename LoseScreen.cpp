#include "LoseScreen.h"

void LoseScreen::init()
{
    LoseID = ResourceManager::getInstance()->loadAndGetGraphicID("Imgs/BackgroundLoseScore.png");
    ScreenRect.x = 0;
    ScreenRect.y = 0;
    ScreenRect.w = SCREEN_WIDTH;
    ScreenRect.h = SCREEN_HEIGHT;
    mReinit = false;
    colorFont = { 255, 255, 255 };
    colorSelect = { 255, 0, 0 };
    char1 = 'A', char2 = 'A', char3 = 'A';
}

void LoseScreen::update()
{
    MenuButtons* MB = InputManager::getInstance()->getMenuInput();
    //Return to menu
    if (MB->Enter) {
        //Passar resultat score amb el username
        userName += char1;
        userName += char2;
        userName += char3;
        FileManager::getInstance()->writeScore(&userName);
        init();
        Player::PlayerInstance()->ResetPlayer();
        SceneManager::getInstance()->changeScene(MAIN, true);
    }
    else if (MB->Down) {
        switch (pos) {
        case 0:
            indx1--;
            if (indx1 < 0) {
                indx1 = Letters.letters.size() - 1;
            }
            char1 = Letters.letters.at(indx1);
            break;
        case 1:
            indx2--;
            if (indx2 < 0) {
                indx2 = Letters.letters.size() - 1;
            }
            char2 = Letters.letters.at(indx2);
            break;
        case 2:
            indx3--;
            if (indx3 < 0) {
                indx3 = Letters.letters.size() - 1;
            }
            char3 = Letters.letters.at(indx3);
            break;
        default:
            break;
        }
    }
    else if (MB->Up) {
        switch (pos) {
        case 0:
            indx1++;
            if (indx1 > Letters.letters.size() - 1) {
                indx1 = 0;
            }
            char1 = Letters.letters.at(indx1);
            break;
        case 1:
            indx2++;
            if (indx2 > Letters.letters.size() - 1) {
                indx2 = 0;
            }
            char2 = Letters.letters.at(indx2);
            break;
        case 2:
            indx3++;
            if (indx3 > Letters.letters.size() - 1) {
                indx3 = 0;
            }
            char3 = Letters.letters.at(indx3);
            break;
        default:
            break;
        }
    }
    else if (MB->Options) {
        pos++;
        if (pos > 2)
            pos = 0;
    }
    Video::getInstace()->updateScreen();

    //Get fletxes up-down-left-right per canviar lletres
}

void LoseScreen::render()
{
    Video::getInstace()->renderGraphic(LoseID, ScreenRect, ScreenRect, 0, NULL, SDL_FLIP_NONE);
    //Text que no cambia
    Video::getInstace()->renderText("SCORE    " + std::to_string(Player::PlayerInstance()->getScore()), colorFont, {190, 140, 300, 100});
    Video::getInstace()->renderText("Press    P    to    return", colorFont, {115, 350, 200, 50});

    //render 3 Letters (username score) text + final score
    switch (pos) {
    case 0:
        Video::getInstace()->renderText(char1, colorSelect, { 200, 250, 70, 80 });
        Video::getInstace()->renderText(char2, colorFont, { 250, 250, 70, 80 });
        Video::getInstace()->renderText(char3, colorFont, { 300, 250, 70, 80 });
        break;
    case 1:
        Video::getInstace()->renderText(char1, colorFont, { 200, 250, 70, 80 });
        Video::getInstace()->renderText(char2, colorSelect, { 250, 250, 70, 80 });
        Video::getInstace()->renderText(char3, colorFont, { 300, 250, 70, 80 });
        break;
    case 2:
        Video::getInstace()->renderText(char1, colorFont, { 200, 250, 70, 80 });
        Video::getInstace()->renderText(char2, colorFont, { 250, 250, 70, 80 });
        Video::getInstace()->renderText(char3, colorSelect, { 300, 250, 70, 80 });
        break;
    default:
        break;
    }
}

void LoseScreen::DestroyWall(int Y, int X)
{
}

int LoseScreen::getTileHeight()
{
    return 0;
}

int LoseScreen::getTileWidth()
{
    return 0;
}

int LoseScreen::getHeight()
{
    return 0;
}

int LoseScreen::getWidth()
{
    return 0;
}

int LoseScreen::getGridPosX(int PosX)
{
    return 0;
}

int LoseScreen::getGridPosY(int PosY)
{
    return 0;
}

BaseEnemy* LoseScreen::getEnemy(int ID)
{
    return nullptr;
}

BasePowerUp* LoseScreen::getPowerUp(int ID)
{
    return nullptr;
}

int LoseScreen::getIDfromLayer(int layer, int PosX, int PosY)
{
    return 0;
}
