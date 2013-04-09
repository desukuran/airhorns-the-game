#pragma once

#include <string>

#define MENU_MAX 5

class CGameMenu
{
public:
	CGameMenu(std::string menu[]);
	~CGameMenu(void);

	static std::string choice[32][MENU_MAX];
};
