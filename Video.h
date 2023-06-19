#pragma once
#include "SDL.h"
#include <SDL_image.h>
#include "ResourceManager.h"
#include "Definicions.h"
#include <SDL_ttf.h>
using namespace std;
class Video
{
public:
	~Video(void);
	void renderGraphic(int img, SobreRect SourceRect, SobreRect DestRect, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void clearScreen(unsigned int color_key);
	void updateScreen();
	bool rectIntersaction(SobreRect r1, SobreRect r2);
	void waitTime(int ms);
	void close();
	void FPS_Check();
	int GetTicks();
	int GetDeltaTime();
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	SDL_Texture* LoadImage(const char* path);
	int setAlpha(int img, int value);
	void renderText(string text, Color color, SobreRect TexCoord);
	void renderText(char text, Color color, SobreRect TexCoord);

	static Video* getInstace()
	{
		if (VideoInstance == NULL)
			VideoInstance = new Video();

		return VideoInstance;
	}
private:
	Video(void);
	static Video* VideoInstance;

	float lastTime;
	float currentTime;
	float deltaTime;

	TTF_Font* font;
};