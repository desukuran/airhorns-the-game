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

	static SDL_Surface* screen;
	int playing;
	
};
