#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <fstream>
#include <map>
#include "player.h"

using namespace std;

enum GameState
{
	STATE_LOGO,
	STATE_TITLE,
	STATE_MENU,
	STATE_GAME,
	STATE_CONTROLS,/*
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
	void flip();
	void AirHornOn();
	int LoadImages();
	int FreeImages();

	void Think();
	void Render();
	void RegulateFrameRate();

	void SetGameState(int state);


	void DrawLogos();
	void DrawTitle();

	//Logical Functions, mainly math
	int IntRand();

	//Variables sit over here.
	SDL_Event GameEvent;

	map<string, string> SpriteList;

	SDL_Surface *airhorn;
	SDL_Surface *airhorn_off;
	SDL_Surface *title_logo;

	SDL_Surface *logo1;
	SDL_Surface *logo2;

	SDL_Surface *player_sprite;

	SDL_Surface *betatext;

	//CPlayer playerEnt;


private:
	int gamestate;
	int logoframe;
	int fadeAmount;

	int logoheight;
};
