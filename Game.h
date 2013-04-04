#pragma once

#include "SDL.h"
#include "SDL_image.h"

class CGame
{
public:
	CGame(void);
	~CGame(void);

	//SDL Functions and loading Blips
	static void flip();
	static void AirHornOn();
	static int LoadAirhorns();

	//Logical Functions, mainly math
	static int IntRand();

	//Variables sit over here.
	SDL_Event GameEvent;

	static SDL_Surface *airhorn;
	static SDL_Surface *airhorn_off;
};
