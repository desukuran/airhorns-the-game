#pragma once

#include <string>
#include "GameLogic.h"

#define MENU_MAX 5

class CGameMenu
{
public:
	CGameMenu(std::string menu[]);
	~CGameMenu(void);

	static void Draw();

	//Variables
	static SDL_Surface *menuTex;
	static SDL_Surface *curTex;
	static int cursorIndex;
	static std::string choice[MENU_MAX];
};
