#pragma once
#include "SDL.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Definicions.h"

class InputManager
{
public:
	~InputManager(void);
	void GetControllers();
	bool HasController(bool State);
	bool HasExited() { return hasExit; };
	bool HasDied() { return hasDead; };
	bool HasBomb() { return hasBomb; };
	void PlayerControls();
	PlayerDirections* getDirectionsP1() { return &P1_Directions; }
	PlayerDirections* getDirectionsP2() { return &P2_Directions; }
	MenuButtons* getMenuInput() { return &MenuButs; }
	static InputManager* getInstance();
private:
	InputManager(void);

	static InputManager* InputInstance;
	bool hasExit, hasDead, hasBomb;
	SDL_GameController* GamePad;
	PlayerDirections P1_Directions, P2_Directions;
	MenuButtons MenuButs;
};