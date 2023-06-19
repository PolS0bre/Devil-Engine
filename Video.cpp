#include "Video.h"
using namespace std;

Video* Video::VideoInstance = NULL;

Video::Video() {
	lastTime = 0;
	currentTime = 0;
	deltaTime = 0;
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	font = TTF_OpenFont("Fonts/ARCADECLASSIC.ttf", 30);
	//TTF_CloseFont(font);
	gWindow = SDL_CreateWindow("Super Bomberman SDL", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
	SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

Video::~Video() {
}

void Video::renderGraphic(int img, SobreRect SourceRect, SobreRect DestRect, double angle, SDL_Point* center, SDL_RendererFlip flip) {

	if (angle == NULL)
	{
		angle = 0;
	}
	if (flip != SDL_FLIP_HORIZONTAL && flip != SDL_FLIP_VERTICAL)
	{
		flip = SDL_FLIP_NONE;
	}

	SDL_Rect rect, rectAux;
	rect.x = SourceRect.x;
	rect.y = SourceRect.y;
	rect.h = SourceRect.h;
	rect.w = SourceRect.w;
	rectAux.h = DestRect.h;
	rectAux.w = DestRect.w;
	rectAux.x = DestRect.x;
	rectAux.y = DestRect.y;
	SDL_Texture* origin = ResourceManager::getInstance()->getGraphicByID(img);
	SDL_RenderCopyEx(gRenderer, origin, &rectAux, &rect, angle, center, flip);
}

void Video::clearScreen(unsigned int color_key) {
	SDL_RenderClear(gRenderer);
}

void Video::updateScreen() {
	SDL_RenderPresent(gRenderer);
	clearScreen(0);
}

bool Video::rectIntersaction(SobreRect r1, SobreRect r2)
{
	SDL_Rect rect1, rect2;
	rect1 = { r1.x, r1.y, r1.w, r1.h };
	rect2 = { r2.x, r2.y, r2.w, r2.h };
	
	return SDL_HasIntersection(&rect1, &rect2);
}

void Video::waitTime(int ms) {
	SDL_Delay(ms);
}

void Video::close() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
}

void Video::FPS_Check()
{
	currentTime = GetTicks();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}

SDL_Texture* Video::LoadImage(const char* path)
{
	return IMG_LoadTexture(gRenderer, path);
}
int Video::GetTicks() {
	return SDL_GetTicks();
}

int Video::GetDeltaTime()
{
	return deltaTime;
}

int Video::setAlpha(int img, int value) {

	SDL_Texture* texture = ResourceManager::getInstance()->getGraphicByID(img);


	int value1 = SDL_SetTextureAlphaMod(texture, (Uint8)value);
	int value2 = SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	if (value1 == 0 && value2 == 0) {
		return 0;
	}
	return 1;

}

void Video::renderText(string text, Color color, SobreRect TexCoord)
{
	SDL_Color Color = { color.R, color.G, color.B };
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), Color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);


	SDL_QueryTexture(texture, NULL, NULL, &TexCoord.w, &TexCoord.h);
	SDL_Rect dstrect = { TexCoord.x, TexCoord.y, TexCoord.w, TexCoord.h };

	SDL_RenderCopy(gRenderer, texture, NULL, &dstrect); 

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void Video::renderText(char text, Color color, SobreRect TexCoord)
{
	SDL_Color Color = { color.R, color.G, color.B };
	SDL_Surface* surface = TTF_RenderText_Solid(font, &text, Color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);

	SDL_QueryTexture(texture, NULL, NULL, &TexCoord.w, &TexCoord.h);
	SDL_Rect dstrect = { TexCoord.x, TexCoord.y, TexCoord.w, TexCoord.h };

	SDL_RenderCopy(gRenderer, texture, NULL, &dstrect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
