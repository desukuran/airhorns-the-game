#include "GameMenu.h"

int CGameMenu::cursorIndex;
SDL_Surface *CGameMenu::curTex;
SDL_Surface *CGameMenu::menuTex;
std::string CGameMenu::choice[MENU_MAX];

CGameMenu::CGameMenu(std::string choices [])
{

	curTex = CGameLogic::load_image("Cursor");
	menuTex = CGameLogic::load_image("Menu");
	int max;

	if (choices->size() < MENU_MAX)
		max = choices->size();
	else
		max = MENU_MAX;
	for (int i=0;i<max;i++)
		choice[i].swap(choices[i]);
}

CGameMenu::~CGameMenu(void)
{
}

void CGameMenu::Draw()
{
	//Draw Menu Background
	CGameLogic::Draw((CGameLogic::ScreenWidth/2)-(menuTex->w/2), (CGameLogic::ScreenHeight)-(menuTex->h)-(menuTex->h/8), menuTex, CGameLogic::screen);

	//Draw Text
	for (int i=0;i<MENU_MAX;i++)
		CGameLogic::DrawText(CGameLogic::screen, choice[i], (CGameLogic::ScreenWidth/2)-(menuTex->w/2)+(menuTex->w/16), (CGameLogic::ScreenHeight)-(menuTex->h)-(menuTex->h/8)+(menuTex->h/16)+(i*32), 255,255,255, false);
	
	//Draw Cursor
	CGameLogic::Draw((CGameLogic::ScreenWidth/2)-(menuTex->w/2), (CGameLogic::ScreenHeight)-(menuTex->h)-(menuTex->h/8)+(menuTex->h/16)+(cursorIndex*32), curTex, CGameLogic::screen);
}

/*void CGameMenu::Think()
{
	//TODO: Cursor logic.
}*/