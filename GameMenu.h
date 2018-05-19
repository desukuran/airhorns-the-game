#pragma once

#include <string>
#include "GameLogic.h"
#include "SDL.h"

#define MENU_MAX 5

enum { CUR_UP,
CUR_DOWN,
CUR_LEFT,
CUR_RIGHT };

class CGameMenu
{
public:
	CGameMenu(std::string menu[], int choiceCount);
	~CGameMenu(void);

	static void Draw();
	static void Think();
	static void CursorMove(int direction);

	static int menuDecision();

	// Gain access to keystate array
	static Uint8 *keys;

	//Variables
	static SDL_Surface *menuTex;
	static SDL_Surface *curTex;

	//Cursor Stuff
	static int cursorIndex; //Where the cursor is
	static int currentMax; //Current amount of choices

	//The Actual Menu
	static std::string choice[MENU_MAX];
};
