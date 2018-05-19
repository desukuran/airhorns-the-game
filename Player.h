#pragma once

#include "SDL.h"
#include "SDL_image.h"

class CPlayer
{
public:
	CPlayer(void);
	~CPlayer(void);

	void Think();
	void Spawn();
	void Draw();
	void ProcessInput();

	static SDL_Surface *player_sprite;

	bool movingUp;
	bool movingDown;
	bool movingLeft;
	bool movingRight;

	static int x,y;

private:
	double playerx, playery;
};
