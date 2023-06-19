#include "InputManager.h"
using namespace std;

InputManager* InputManager::InputInstance = NULL;

InputManager::~InputManager()
{
	SDL_GameControllerClose(GamePad);
}
InputManager::InputManager()
{
	GamePad = NULL;
	hasExit = true;
	hasBomb = false;
	hasDead = false;
	P1_Directions = { 0,0 };
	P2_Directions = { 0,0 };
}
InputManager* InputManager::getInstance()
{
	if (InputInstance == NULL)
		InputInstance = new InputManager();

	return InputInstance;
}
void InputManager::GetControllers()
{
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			GamePad = SDL_GameControllerOpen(i);
			if (!GamePad) {
				cout << "Could not open gamecontroller " << i << ": " << SDL_GetError();
			}
		}
	}
	if (GamePad) {
		HasController(true);
	}
	else {
		HasController(false);
	}
}

bool InputManager::HasController(bool State)
{
	return State;
}

void InputManager::PlayerControls()
{
	hasBomb = false;
	MenuButs.Enter = false;
	MenuButs.Options = false;
	MenuButs.Up = false;
	MenuButs.Down = false;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			hasExit = false;
			break;

			//Player 1 Controls
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_W) {
				P1_Directions.isUp = -1;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
				P1_Directions.isUp = 1;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
				P1_Directions.isLeft = -1;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
				P1_Directions.isLeft = 1;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_P) {
				MenuButs.Enter = true;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_O) {
				MenuButs.Options = true;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
				MenuButs.Up = true;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
				MenuButs.Down = true;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				hasExit = false;
			}
			break;
		
		case SDL_KEYUP:
			if (event.key.keysym.scancode == SDL_SCANCODE_W) {
				P1_Directions.isUp = 0;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
				P1_Directions.isUp = 0;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
				P1_Directions.isLeft = 0;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
				P1_Directions.isLeft = 0;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				hasBomb = true;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_P) {
				MenuButs.Enter = false;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_O) {
				MenuButs.Options = false;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
				MenuButs.Up = false;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
				MenuButs.Down = false;
			}
			break;

			//Player 2 Controls
		case SDL_CONTROLLERAXISMOTION:
			if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
				//MoveCharacterY();
				//MoveY = event.caxis.value;
				//std::cout << MoveY << std::endl;
			}
			if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
				//MoveCharacterX();
				//MoveX = event.caxis.value;
				//std::cout << MoveX << std::endl;
			}
			/*if (Button X pressed == true){
			//hasBomb = true;
			*/
			break;
		default:
			break;
		}
	}
}
