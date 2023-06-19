#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include "BaseScene.h"

//! Enum Scenes.
/*! All the Scenes in the game. */
//Main Menu - Game Over - Character/Level Selection - High Scores
enum SceneEnum {
	MAIN, GAME, LVL2, LVL3, LVL4, LVL5, LOSE, SCORE,
	_LASTSCENE
};

#define NUM_SCENES _LASTSCENE

class SceneManager
{
public:
	~SceneManager();

	void init();

	void changeScene(SceneEnum next_scene, bool reinit = true);

	SceneEnum getCurrSceneEnum() { return mCurrScene; };

	BaseScene* getCurrentScene() { return mVectorScenes[mCurrScene]; };

	//! Gets pointer to instance
	static SceneManager* getInstance();

protected:
	SceneManager();
	static SceneManager* pInstance;	/*!<  pointer instance*/

	std::vector<BaseScene*>	mVectorScenes;
	SceneEnum		mCurrScene;
};

#endif
