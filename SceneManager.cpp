#include "SceneManager.h"

/*
//INCLUIR FILLES BASESCENE (1 X ESCENA)
#include "SceneMain.h"
#include "SceneOptions.h"
#include "SceneSaveLoad.h"
#include "SceneIntro.h"
#include "SceneGame.h"
#include "SceneGameOver.h"*/
#include "MainMenu.h"
#include "TestLevel.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "LoseScreen.h"
#include "ScoreMenu.h"

SceneManager* SceneManager::pInstance = NULL;

SceneManager* SceneManager::getInstance() {
	if (!pInstance) {
		pInstance = new SceneManager();
	}
	return pInstance;
}

SceneManager::SceneManager() {
	init();
}

SceneManager::~SceneManager() {
}

void SceneManager::init() {
	mVectorScenes.resize(NUM_SCENES);

	MainMenu* main = new MainMenu();
	TestLevel* test = new TestLevel();
	LoseScreen* lose = new LoseScreen();
	ScoreMenu* score = new ScoreMenu();
	Level2* lvl2 = new Level2();
	Level3* lvl3 = new Level3();
	Level4* lvl4 = new Level4();
	Level5* lvl5 = new Level5();

	mVectorScenes[MAIN] = main;
	mVectorScenes[GAME] = test;
	mVectorScenes[LVL2] = lvl2;
	mVectorScenes[LVL3] = lvl3;
	mVectorScenes[LVL4] = lvl4;
	mVectorScenes[LVL5] = lvl5;
	mVectorScenes[LOSE] = lose;
	mVectorScenes[SCORE] = score;

	main->init();
	test->init();
	lvl2->init();
	lvl3->init();
	lvl4->init();
	lvl5->init();
	lose->init();
	score->init();

	mCurrScene = MAIN;
}

void SceneManager::changeScene(SceneEnum next_scene, bool reinit) {
	mVectorScenes[next_scene]->setReInit(reinit);
	mCurrScene = next_scene;
}
