#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Music.h"

enum { WIDTH, HEIGHT, BPP };

class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);
	static int DrawTitle(void);
	static int InitGame(void);
	static void CleanUp(void);

	static SDL_Surface *load_image(string filename);
	static void Draw(int x, int y, SDL_Surface* source, SDL_Surface* destination);
	static void DrawText(SDL_Surface* screen, string text, Sint16 x, Sint16 y, Uint8 red, Uint8 green, Uint8 blue, bool center);

	static SDL_Surface* screen;
	static TTF_Font *font;

	//Variables
	int playing;
	static int ScreenHeight, ScreenWidth;
	
};
