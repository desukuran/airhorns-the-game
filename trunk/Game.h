#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <fstream>
#include <map>

using namespace std;

enum GameState
{
	STATE_LOGO,
	STATE_TITLE,
	STATE_MENU/*,
	STATE_CONTROLS,
	STATE_CREDITS,
	STATE_PLAYING,
	STATE_PAUSED,
	STATE_GAMEOVER,
	STATE_VICTORY*/
};

class CGame
{
public:
	CGame(void);
	~CGame(void);

	//SDL Functions and loading Blips
	static void flip();
	static void AirHornOn();
	static int LoadImages();
	static int FreeImages();

	static void Think();
	static void Render();
	static void RegulateFrameRate();

	static void SetGameState(int state);


	static void DrawLogos();
	static void DrawTitle();

	//Logical Functions, mainly math
	static int IntRand();

	//Variables sit over here.
	static SDL_Event GameEvent;

	static map<string, string> SpriteList;

	static SDL_Surface *airhorn;
	static SDL_Surface *airhorn_off;
	static SDL_Surface *title_logo;

	static SDL_Surface *logo1;
	static SDL_Surface *logo2;

	static SDL_Surface *betatext;


private:
	static int gamestate;
	static int logoframe;
	static int fadeAmount;

	static int logoheight;
};
