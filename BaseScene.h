#ifndef BASESCENE_H
#define BASESCENE_H
#include "BaseEnemy.h"
#include "BasePowerUp.h"

//! Scene class
/*!
	Handles the Scenes for all the game.
*/
class BaseScene
{
public:
	//! Constructor of an empty Scene.
	BaseScene();

	//! Destructor
	virtual ~BaseScene();

	//! Initializes the Scene.
	virtual void init();

	//! Function to withdraw anything owned by the class and to call init
	virtual void reinit();

	//! Handles the drawing of the scene
	virtual void render() = 0;

	//! Handles the updating of the scene
	virtual void update() = 0;

	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getTileWidth() = 0;
	virtual int getTileHeight() = 0;
	virtual int getIDfromLayer(int layer, int PosX, int PosY) = 0;
	virtual int getGridPosX(int PosX) = 0;
	virtual int getGridPosY(int PosY) = 0;
	virtual int getEnemiesInLevel() = 0;
	virtual int getPowerUpsInLevel() = 0;
	virtual BaseEnemy* getEnemy(int ID) = 0;
	virtual BasePowerUp* getPowerUp(int ID) = 0;
	virtual void DestroyWall(int Y, int X) = 0;
	virtual void nextLevel() = 0;
	

	void setReInit(bool loaded = true) { mReinit = loaded; };
	bool mustReInit() { return mReinit; };

protected:
	bool		mReinit;			/*!<  Reload when returning to scene*/
};

#endif