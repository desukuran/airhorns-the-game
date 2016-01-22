#pragma once

#include <string>
#include "GameLogic.h"
#include "SDL/SDL.h"

#define MENU_MAX 5

enum { CUR_UP,
CUR_DOWN,
CUR_LEFT,
CUR_RIGHT };

class CGameMenu
{
public:
	CGameMenu();
	~CGameMenu(void);

	void Create(std::string menu[], int choiceCount);

	void Draw();
	void Think();
	void CursorMove(int direction);

	int menuDecision();

	// Gain access to keystate array
	Uint8 *keys;

	//Variables
	SDL_Surface *menuTex;
	SDL_Surface *curTex;

	//Cursor Stuff
	int cursorIndex; //Where the cursor is
	int currentMax; //Current amount of choices

	//The Actual Menu
	std::string choice[MENU_MAX];

	//Movement time
	int nextMoveTime;
};
