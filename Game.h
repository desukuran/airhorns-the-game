#pragma once

#include "SDL.h"
#include "SDL_image.h"
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

	static void Render();
	static void RegulateFrameRate();

	static void SetGameState(int state);


	static void DrawLogos();

	//Logical Functions, mainly math
	static int IntRand();

	//Variables sit over here.
	SDL_Event GameEvent;

	static map<string, string> SpriteList;

	static SDL_Surface *airhorn;
	static SDL_Surface *airhorn_off;
	static SDL_Surface *title_logo;

	static SDL_Surface *logo1;
	static SDL_Surface *logo2;


private:
	void DrawTitle();

	static int gamestate;

	static int logonumber;
	static int logoframe;
};
