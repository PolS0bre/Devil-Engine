#include <cstdlib>
#include <ctime>
#include <iostream>

#include "sdl.h"
#include "ResourceManager.h"
#include "Video.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "FileManager.h"
#include "Player.h"

using namespace std;

int main(int argc, char* args[]) {

	srand(NULL);
	ResourceManager::getInstance();
	Video::getInstace();
	AudioManager::getInstance();
	InputManager::getInstance();
	SceneManager::getInstance();
	Player::PlayerInstance();

	bool isOpen = true;	

	while (isOpen) {
		//Reinit o no
		if (SceneManager::getInstance()->getCurrentScene()->mustReInit()) {
			SceneManager::getInstance()->getCurrentScene()->init();
			Player::PlayerInstance()->SetWorldPointer(SceneManager::getInstance()->getCurrentScene());
		}

		// Control de Gamepad
		isOpen = InputManager::getInstance()->HasExited();
		InputManager::getInstance()->PlayerControls();

		// Control de moviment
		if (SceneManager::getInstance()->getCurrSceneEnum() > 0 && SceneManager::getInstance()->getCurrSceneEnum() < 6) {
			Player::PlayerInstance()->Update();
		}

		//UPDATE
		SceneManager::getInstance()->getCurrentScene()->update();

		//UPDATE MUSIC
		if (SceneManager::getInstance()->getCurrSceneEnum() > 0 && SceneManager::getInstance()->getCurrSceneEnum() < 6) {
			AudioManager::getInstance()->playMusic("Audio/GameMusic.mp3");
		}
		else {
			AudioManager::getInstance()->playMusic("Audio/MenusMusic.mp3");
		}


		// RENDER
		if (!SceneManager::getInstance()->getCurrentScene()->mustReInit()) {
			SceneManager::getInstance()->getCurrentScene()->render();
		}
		if (SceneManager::getInstance()->getCurrSceneEnum() > 0 && SceneManager::getInstance()->getCurrSceneEnum() < 6) {
			Player::PlayerInstance()->Render();
		}

		// Control del frame
		Video::getInstace()->FPS_Check();
	}

	return 0;
}