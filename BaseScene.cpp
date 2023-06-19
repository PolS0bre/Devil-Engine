#include "BaseScene.h"

BaseScene::BaseScene() {
	mReinit = true;
}

BaseScene::~BaseScene() {
}

void BaseScene::init() {
	mReinit = false;
}

void BaseScene::reinit() {
	mReinit = false;
}
