#pragma once
#define SCREEN_WIDTH 525
#define SCREEN_HEIGHT 466
#define FPS 60
#include <string>

struct SobreRect {
	int x;
	int y;
	int w;
	int h;
};

struct ScoreUser
{
	int _score;
	std::string _username;
};

struct Color {
	int R;
	int G;
	int B;
};

struct PlayerDirections {
	float isLeft;
	float isUp;
};

struct let {
	std::string letters = "abcdefghijklmnopqrstuvwxyz";
};

struct MenuButtons {
	bool Down;
	bool Up;
	bool Enter;
	bool Options;
};

enum EnemyActions {
	MOVING,
	ATTACK_ACTION,
	DAMAGED,
	DEAD
};
enum PowerUpStates {
	NOT_PICKED,
	PICKED
};